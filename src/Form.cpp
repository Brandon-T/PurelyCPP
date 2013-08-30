#include "Form.hpp"

namespace cxx
{
    void Form::SubClassWindow(HWND Window, WNDPROC SubClassProc)
    {
        SetWindowLongPtr(Window, GWLP_USERDATA, static_cast<LONG_PTR>(SetWindowLongPtr(Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(SubClassProc))));
    }

    void Form::UnSubClassWindow(HWND Window)
    {
        SetWindowLongPtr(Window, GWLP_WNDPROC, GetWindowLongPtr(Window, GWLP_USERDATA));
    }

    int Form::MessageLoop()
    {
        if (!Message)
        {
            Message = true;
            while(GetMessage(&Messages, nullptr, 0, 0))
            {
                TranslateMessage(&Messages);
                DispatchMessage(&Messages);
            }
            return Messages.wParam;
        }
        return 0;
    }

    Form::~Form() {}

    Form::Form(tstring Title, tstring Class, WNDPROC WindowProcedure, WNDCLASSEX WndClass, DWORD dwStyleEx, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HMENU Menu)
    {
        if (WindowProcedure == nullptr)
        {
            WindowProcedure = Form::WindowProcedure;
        }

        if (!WndClass.cbSize)
        {
            WndClass =
            {
                sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
                0, 0, GetModuleHandle(nullptr), LoadIcon(nullptr, IDI_APPLICATION),
                LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_BACKGROUND),
                nullptr, Class.c_str(), LoadIcon(nullptr, IDI_APPLICATION)
            };
        }

        if(RegisterClassEx(&WndClass))
        {
            WindowHandle = CreateWindowEx(dwStyleEx, Class.c_str(), Title.c_str(), dwStyle, Location.X, Location.Y, Width, Height, Parent, Menu, GetModuleHandle(nullptr), this);
        }
    }

    LRESULT __stdcall Form::WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        switch(Msg)
        {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProc(Hwnd, Msg, wParam, lParam);
        }
        return 0;
    }
}
