#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#define LineError(ErrorString) tcerr << __FILE__ << _T(": ") << __PRETTY_FUNCTION__ << _T(": ") << __LINE__ << _T("\tMsg: ") << ErrorString << nl

#include "Platforms.hpp"
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <system_error>

namespace cxx
{
    class Debug
    {
        private:
            HWND WindowHandle;
            std::thread Thread;
            bool ConsoleActive;
            std::atomic<bool> DetachedThread;
            tstreambuf *CinBuffer, *CoutBuffer, *CerrBuffer;
            tfstream ConsoleInput, ConsoleOutput, ConsoleError;
            void Swap(Debug& D);
            static LRESULT __stdcall WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        public:
            template<typename Function, typename... Args>
            explicit Debug(Function && FunctionToPass, Args && ... args);
            explicit Debug(std::function<void()>& FunctionToPass);
            explicit Debug(bool CreateDebugConsole = false, bool CreateDebugWindow = false);

            Debug(const Debug& D) = delete;
            Debug(Debug && D);
            ~Debug();

            void DestroyThreadInfo(bool JoinThread);

            Debug& operator = (const Debug& D) = delete;

            Debug& operator = (Debug D);

            template<class Function, class... Args>
            Debug& operator ()(Function && FunctionToPass, Args && ... args);

            Debug& operator ()(std::function<void()>& FunctionToPass);

            Debug& operator ()(bool CreateDebugConsole, bool CreateDebugWindow);

            void DebugWindow(tstring ClassName, tstring Title, int Width = CW_USEDEFAULT, int Height = CW_USEDEFAULT, WNDPROC WindowProcedure = nullptr, WNDCLASSEX WndClass = {0});

            bool DebugConsole();

            bool DestroyConsole();

            HWND GetWindowHandle();

            template<class Function, class... Args>
            void StartThread(Function && FunctionToPass, Args && ... args); //Debug(&Debug::DebugWindow, &Instance, "one", "two", 500, 500);

            void StartThread(std::function<void()>& FunctionToPass);

            void StopThread();
    };

    template<typename Function, typename... Args>
    Debug::Debug(Function && FunctionToPass, Args && ... args) : WindowHandle(nullptr), Thread(std::thread(FunctionToPass, args...)), ConsoleActive(false), DetachedThread(false), CinBuffer(nullptr), CoutBuffer(nullptr), CerrBuffer(nullptr), ConsoleInput(nullptr), ConsoleOutput(nullptr), ConsoleError(nullptr) {}

    template<class Function, class... Args>
    Debug& Debug::operator ()(Function && FunctionToPass, Args && ... args)
    {
        StopThread();
        Thread = StartThread(FunctionToPass, args...);
        return *this;
    }

    template<class Function, class... Args>
    void Debug::StartThread(Function && FunctionToPass, Args && ... args)
    {
        StopThread();
        Thread = std::thread(FunctionToPass, args...);
    }
}

#endif // DEBUG_HPP_INCLUDED
