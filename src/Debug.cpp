// *** ADDED BY HEADER FIXUP ***
#include <algorithm>
// *** END ***
#include "Debug.hpp"

namespace cxx
{
    Debug::~Debug()
    {
        StopThread();
        DestroyConsole();
    }

    void Debug::Swap(Debug& D)
    {
        std::swap(Thread, D.Thread);
        std::swap(ConsoleActive, D.ConsoleActive);
        std::swap(CinBuffer, D.CinBuffer);
        std::swap(CoutBuffer, D.CoutBuffer);
        std::swap(CerrBuffer, D.CerrBuffer);
    }

    LRESULT __stdcall Debug::WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        switch(Msg)
        {
            case WM_PAINT:
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProc(Hwnd, Msg, wParam, lParam);
        }
        return 0;
    };

    void Debug::DestroyThreadInfo(bool JoinThread)
    {
        DetachedThread = !JoinThread;
    }

    Debug::Debug(std::function<void()>& FunctionToPass) : WindowHandle(nullptr), Thread(std::thread(FunctionToPass)), ConsoleActive(false), DetachedThread(false), CinBuffer(nullptr), CoutBuffer(nullptr), CerrBuffer(nullptr), ConsoleInput(nullptr), ConsoleOutput(nullptr), ConsoleError(nullptr) {}

    Debug::Debug(bool CreateDebugConsole, bool CreateDebugWindow) : WindowHandle(nullptr), Thread(), ConsoleActive(false), DetachedThread(false), CinBuffer(nullptr), CoutBuffer(nullptr), CerrBuffer(nullptr), ConsoleInput(nullptr), ConsoleOutput(nullptr), ConsoleError(nullptr)
    {
        if(CreateDebugWindow)
            DebugWindow(_T("Debugging"), _T("Debug"), CW_USEDEFAULT, CW_USEDEFAULT, nullptr, {0});

        if (CreateDebugConsole)
            DebugConsole();
    }

    Debug::Debug(Debug && D) : WindowHandle(nullptr), Thread(), ConsoleActive(false), DetachedThread(false), CinBuffer(nullptr), CoutBuffer(nullptr), CerrBuffer(nullptr), ConsoleInput(nullptr), ConsoleOutput(nullptr), ConsoleError(nullptr)
    {
        D.Swap(*this);
    }

    Debug& Debug::operator = (Debug D)
    {
        D.Swap(*this);
        return *this;
    }

    Debug& Debug::operator ()(std::function<void()>& FunctionToPass)
    {
        StopThread();
        StartThread(FunctionToPass);
        return *this;
    }

    Debug& Debug::operator ()(bool CreateDebugConsole, bool CreateDebugWindow)
    {
        if(CreateDebugWindow)
            DebugWindow(_T("Debugging"), _T("Debug"), CW_USEDEFAULT, CW_USEDEFAULT, nullptr, {0});

        ConsoleActive = (CreateDebugConsole == true) ? DebugConsole() : DestroyConsole();
        return *this;
    }

    bool Debug::DebugConsole()
    {
        if(!ConsoleActive)
        {
            ConsoleActive = AllocConsole();
            if (ConsoleActive)
            {
                CinBuffer = tcin.rdbuf();
                CoutBuffer = tcout.rdbuf();
                CerrBuffer = tcerr.rdbuf();
                ConsoleInput.open("CONIN$", std::ios::in);
                ConsoleOutput.open("CONOUT$", std::ios::out);
                ConsoleError.open("CONOUT$", std::ios::out);
                tcin.rdbuf(ConsoleInput.rdbuf());
                tcout.rdbuf(ConsoleOutput.rdbuf());
                tcerr.rdbuf(ConsoleError.rdbuf());
            }
        }

        return ConsoleActive;
    }

    bool Debug::DestroyConsole()
    {
        if (ConsoleActive)
        {
            ConsoleInput.close();
            ConsoleOutput.close();
            ConsoleError.close();
            tcin.rdbuf(CinBuffer);
            tcout.rdbuf(CoutBuffer);
            tcerr.rdbuf(CerrBuffer);
            CinBuffer = nullptr;
            CoutBuffer = nullptr;
            CerrBuffer = nullptr;
        }
        ConsoleActive = !FreeConsole();

        return ConsoleActive;
    }

    HWND Debug::GetWindowHandle()
    {
        return WindowHandle;
    }

    void Debug::StartThread(std::function<void()>& FunctionToPass)
    {
        StopThread();
        Thread = std::thread(FunctionToPass);
    }

    void Debug::StopThread()
    {
        try
        {
            if (DetachedThread)
            {
                this->Thread.detach();
            }
            else
            {
                this->Thread.join();
            }
        }
        catch (...) {}
    }

    void Debug::DebugWindow(tstring ClassName, tstring Title, int Width, int Height, WNDPROC WindowProcedure, WNDCLASSEX WndClass)
    {
        if (WindowProcedure == nullptr)
        {
            WindowProcedure = Debug::WindowProcedure;
        }

        if (WndClass.cbSize == 0)
        {
            WndClass =
            {
                sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                0, 0, GetModuleHandle(nullptr), LoadIcon(nullptr, IDI_APPLICATION),
                LoadCursor(nullptr, IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
                nullptr, ClassName.c_str(), LoadIcon (nullptr, IDI_APPLICATION)
            };
        }

        if(RegisterClassEx(&WndClass))
        {
            WindowHandle = CreateWindowEx(0, ClassName.c_str(), Title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, Width, Height, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
            if(WindowHandle)
            {
                MSG msg = {nullptr};
                ShowWindow(WindowHandle, SW_SHOWDEFAULT);
                while(GetMessage(&msg, nullptr, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
    }
}
