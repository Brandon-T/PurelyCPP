#ifndef BASEFORM_HPP_INCLUDED
#define BASEFORM_HPP_INCLUDED

#include <windows.h>
#include <iostream>
#include "Types.hpp"

namespace cxx
{
    template<typename T>
    class BaseForm
    {
        public:
            BaseForm() : WindowHandle(nullptr) {}
            BaseForm(BaseForm &Base) = delete;
            BaseForm(BaseForm &&Base) = delete;
            BaseForm& operator = (BaseForm &Base) = delete;
            virtual ~BaseForm() {}
            bool Create(tstring Title, tstring Class, DWORD dwStyleEx = 0, DWORD dwStyle = WS_OVERLAPPEDWINDOW, Point Location = {CW_USEDEFAULT, CW_USEDEFAULT}, int Width = CW_USEDEFAULT, int Height = CW_USEDEFAULT, HWND Parent = HWND_DESKTOP, HMENU Menu = nullptr);

        private:
            HWND WindowHandle = nullptr;
            void GetData(HWND hwnd, T** Data);
            void StoreData(T** Data, HWND hwnd, LPARAM lParam);
            static LRESULT __stdcall WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);

        protected:
            MSG Messages = {nullptr};
            virtual int MessageLoop();
            virtual HWND Handle() const
            {
                return WindowHandle;
            }
            virtual LRESULT HandleMessages(UINT Msg, WPARAM wParam, LPARAM lParam) = 0;
    };

    template<typename T>
    int BaseForm<T>::MessageLoop()
    {
        while(GetMessage(&Messages, nullptr, 0, 0))
        {
            TranslateMessage(&Messages);
            DispatchMessage(&Messages);
        }
        return Messages.wParam;
    }

    template<typename T>
    bool BaseForm<T>::Create(tstring Title, tstring Class, DWORD dwStyleEx, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HMENU Menu)
    {
        WNDCLASSEX WndClass =
        {
            sizeof(WNDCLASSEX), CS_DBLCLKS, T::WindowProcedure,
            0, 0, GetModuleHandle(nullptr), LoadIcon(nullptr, IDI_APPLICATION),
            LoadCursor(nullptr, IDC_ARROW), HBRUSH(COLOR_BACKGROUND),
            nullptr, Class.c_str(), LoadIcon(nullptr, IDI_APPLICATION)
        };

        if(RegisterClassEx(&WndClass))
        {
            WindowHandle = CreateWindowEx(dwStyleEx, Class.c_str(), Title.c_str(), dwStyle, Location.X, Location.Y, Width, Height, Parent, Menu, GetModuleHandle(nullptr), this);
            return WindowHandle;
        }

        return false;
    }

    template<typename T>
    LRESULT __stdcall BaseForm<T>::WindowProcedure(HWND Hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        T* Data = nullptr;

        switch(Msg)
        {
            case WM_NCCREATE:
                {
                    CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
                    Data = reinterpret_cast<T*>(pCreate->lpCreateParams);
                    SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Data));
                    Data->WindowHandle = Hwnd;
                    break;
                }

            default:
                {
                    Data = reinterpret_cast<T*>(GetWindowLongPtr(Hwnd, GWLP_USERDATA));
                    break;
                }
        }

        return Data ? Data->HandleMessages(Msg, wParam, lParam) : DefWindowProc(Hwnd, Msg, wParam, lParam);
    }

    template<typename T>
    void BaseForm<T>::GetData(HWND hwnd, T** Data)
    {
        *Data = reinterpret_cast<T*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    template<typename T>
    void BaseForm<T>::StoreData(T** Data, HWND hwnd, LPARAM lParam)
    {
        CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        *Data = reinterpret_cast<T*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)*Data);
    }
}

#endif // BASEFORM_HPP_INCLUDED
