#ifndef FORM_HPP_INCLUDED
#define FORM_HPP_INCLUDED

#include "Platforms.hpp"
#include <iostream>
#include "Types.hpp"

namespace cxx
{
    class Form
    {
        public:
            Form(tstring Title, tstring Class, WNDPROC WindowProcedure = nullptr, WNDCLASSEX WndClass = {0}, DWORD dwStyleEx = 0, DWORD dwStyle = WS_OVERLAPPEDWINDOW, Point Location = {CW_USEDEFAULT, CW_USEDEFAULT}, int Width = CW_USEDEFAULT, int Height = CW_USEDEFAULT, HWND Parent = HWND_DESKTOP, HMENU Menu = nullptr);
            Form(const Form &F) = delete;
            Form(Form && F) = delete;
            virtual ~Form();

        private:
            bool Message = false;
            HWND WindowHandle = nullptr;
            Form& operator = (const Form &F) = delete;
            Form& operator = (Form && F) = delete;
            static LRESULT __stdcall WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        protected:
            MSG Messages = {nullptr};
            virtual int Show() = 0;
            virtual int MessageLoop();
            virtual HWND Handle() const
            {
                return WindowHandle;
            }
            virtual void SubClassWindow(HWND Window, WNDPROC SubClassProc);
            virtual void UnSubClassWindow(HWND Window);
    };
}


#endif // FORM_HPP_INCLUDED
