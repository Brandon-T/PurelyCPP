#ifndef CONTROL_HPP_INCLUDED
#define CONTROL_HPP_INCLUDED

#include "Unicode.hpp"
#include "Platforms.hpp"
#include <tchar.h>
#include <Commctrl.h>
#include <Richedit.h>
#include <array>
#include <iostream>
#include <functional>
#include <stdexcept>
#include "Types.hpp"
#include "Images.hpp"

namespace cxx
{
    class Control
    {
        private:
            HMENU ID;
            HWND Handle, Parent;
            tstring Class, Title;
            DWORD dwExStyle, dwStyle;
            Point Location;
            int Width, Height;
            void Swap(Control &C);
            std::array<std::function<void(HWND, UINT, WPARAM, LPARAM)>, 6> Functions;

        public:
            Control(const Control &C) = delete;
            Control(Control && C);
            Control(DWORD dwExStyle, tstring Class, tstring Title, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HINSTANCE Instance, void* LParam);
            Control(DWORD dwExStyle, tstring Class, tstring Title, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HMENU ID, HINSTANCE Instance, void* LParam);
            virtual ~Control();

            virtual HMENU GetID() const;
            virtual HWND GetHandle() const;
            virtual HWND GetParent() const;
            virtual tstring GetClass() const;
            virtual int GetWidth() const;
            virtual int GetHeight() const;
            virtual Point GetLocation() const;
            virtual bool IsEnabled() const;
            virtual bool IsVisible() const;
            virtual bool GetTabStop() const;
            virtual tstring GetText() const;

            virtual void SetTabStop(bool Enabled);
            virtual void SetEnabled(bool Enabled);
            virtual void SetVisibility(bool Visible);
            virtual void SetBounds(Box Bounds);
            virtual void SetText(const tstring &Text);
            virtual void SetParent(HWND Parent);
            virtual void SetLocation(Point Location);
            virtual void SetSize(int Width, int Height);
            virtual void SetStyle(DWORD Style, bool RemoveStyle = false);

            virtual void Dispose();
            Control& operator = (const Control &C) = delete;
            Control& operator = (Control && C);

        protected:
            Control();
            bool Initialized;
            void UnInitialized();
            static std::size_t IDs;
            void SetParentHandle(HWND Parent);
            static LRESULT __stdcall SubClass(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
    };

    class Button : public Control
    {
        public:
            Button();
            Button(const Button &B) = delete;
            Button(Button && B);
            Button(tstring Title, Point Location, int Width, int Height, HWND Parent);
            virtual ~Button();

            Button& operator = (const Button &B) = delete;
            virtual Button& operator = (Button && B);
    };

    class CheckBox : public Control //BS_PUSHLIKE
    {
        public:
            CheckBox();
            CheckBox(const CheckBox &C) = delete;
            CheckBox(CheckBox && C);
            CheckBox(tstring Title, Point Location, int Width, int Height, HWND Parent, bool Checked = false);
            virtual ~CheckBox();

            virtual bool IsChecked();
            virtual void SetChecked(bool Checked);

            CheckBox& operator = (const CheckBox &C) = delete;
            virtual CheckBox& operator = (CheckBox && C);
    };

    class RadioButton : public Control
    {
            //BS_AUTORADIOBUTTON
    };

    class GroupBox : public Control
    {
            //BS_GROUPBOX
    };

    class TextBox : public Control
    {
        public:
            TextBox();
            TextBox(const TextBox &T) = delete;
            TextBox(TextBox && T);
            TextBox(tstring Text, Point Location, int Width, int Height, HWND Parent, bool MultiLine = false);
            virtual ~TextBox();

            virtual void SetReadOnly(bool ReadOnly);
            virtual void SetPassword(bool Enabled, char PasswordChar = '*');
            virtual std::uint32_t GetTextLength() const;
            virtual void AppendText(const tstring &Text) const;
            virtual void ShowScrollBar(bool Show, int wBar = SB_VERT);

            TextBox& operator = (const TextBox &T) = delete;
            virtual TextBox& operator = (TextBox && T);
    };

    class ListBox : public Control
    {
        public:
            ListBox();
            ListBox(const ListBox &L) = delete;
            ListBox(ListBox && L);
            ListBox(Point Location, int Width, int Height, HWND Parent);
            virtual ~ListBox();

            virtual tstring GetText() = delete;
            virtual int GetItemCount() const;
            virtual int GetSelectedIndex() const;
            virtual void SetSelectedIndex(int Index);
            virtual void AddItem(const tstring &Item, int Index = -1);
            virtual void RemoveItem(int Index);
            virtual void Clear();
            virtual int GetIndexOf(const tstring &Item);
            virtual int GetIndexPartial(const tstring &Item);
            virtual void SetColumnWidth(int Width);
            virtual tstring GetItem(int Index) const;

            ListBox& operator = (const ListBox &L) = delete;
            virtual ListBox& operator = (ListBox && L);
    };

    class ComboBox : public Control
    {
        public:
            enum DropDownStyle {STYLE_SIMPLE, STYLE_DROPDOWN, STYLE_DROPDOWN_LIST};

            ComboBox();
            ComboBox(const ComboBox &C) = delete;
            ComboBox(ComboBox && C);
            ComboBox(DropDownStyle Style, Point Location, int Width, int Height, HWND Parent);
            virtual ~ComboBox();

            virtual tstring GetText() = delete;
            virtual int GetItemCount() const;
            virtual int GetSelectedIndex() const;
            virtual void SetSelectedIndex(int Index);
            virtual void AddItem(const tstring &Item, int Index = -1);
            virtual void RemoveItem(int Index);
            virtual void Clear();
            virtual int GetIndexOf(const tstring &Item);
            virtual int GetIndexPartial(const tstring &Item);
            virtual void SetDropDownWidth(int Width);
            virtual void SetDropDownStyle(DropDownStyle Style);
            virtual tstring GetItem(int Index) const;

            ComboBox& operator = (const ComboBox &C) = delete;
            virtual ComboBox& operator = (ComboBox && C);
    };

    class PictureBox: public Control
    {
        public:
            PictureBox();
            PictureBox(const PictureBox &P) = delete;
            PictureBox(PictureBox && P);
            PictureBox(Point Location, int Width, int Height, HWND Parent);
            virtual ~PictureBox();

            virtual tstring GetText() = delete;
            virtual void SetImage(HBITMAP Img);
            virtual void SetImage(Image Img);

            PictureBox& operator = (const PictureBox &P) = delete;
            virtual PictureBox& operator = (PictureBox && P);
    };

    class MenuBar: public Control
    {
        private:
            std::vector<HMENU> Menus;

        public:
            MenuBar();
            MenuBar(const MenuBar &M) = delete;
            MenuBar(MenuBar && M);
            MenuBar(HWND Parent);
            virtual ~MenuBar();

            tstring GetText(HMENU Menu, int Position);
            std::uint32_t GetMenuItemID(HMENU Menu, int Position);
            HMENU FindMenuItem(tstring MenuName);
            HMENU FindMenuItem(HMENU Parent, tstring MenuName);

            void CreateSubMenu(HMENU Parent, tstring Name, DWORD Style);
            void AddMenuItem(tstring Name, DWORD Style);
            void AppendMenuItem(HMENU Parent, tstring Name, DWORD Style);
            bool ToggleItemCheck(HMENU MenuItem, int Position);
            bool IsItemChecked(HMENU MenuItem, int Position);
            void Show();

            MenuBar& operator = (const MenuBar &M) = delete;
            virtual MenuBar& operator = (MenuBar && M);
    };

    class ToolBar: public Control
    {
        public:
            ToolBar();
            ToolBar(const ToolBar &T) = delete;
            ToolBar(ToolBar && T);
            ToolBar(Point Location, int Width, int Height, HWND Parent);
            virtual ~ToolBar();

            virtual tstring GetText() = delete;

            ToolBar& operator = (const ToolBar &T) = delete;
            virtual ToolBar& operator = (ToolBar && T);
    };

#ifdef UNICODE
    class RichTextBox: public Control
    {
        private:
            static int Instances;
            static HMODULE Module;
            static DWORD __stdcall EditStreamCallback(DWORD_PTR dwCookie, std::uint8_t* Buffer, LONG cb, LONG* pcb);

        public:
            RichTextBox();
            RichTextBox(const RichTextBox &R) = delete;
            RichTextBox(RichTextBox && R);
            RichTextBox(tstring Text, Point Location, int Width, int Height, HWND Parent, bool MultiLine = false);
            virtual ~RichTextBox();

            virtual void SetReadOnly(bool ReadOnly);
            virtual void SetPassword(bool Enabled, char PasswordChar = '*');
            virtual std::uint32_t GetTextLength() const;
            virtual void AppendText(const tstring &Text) const;
            virtual void ShowScrollBar(bool Show, int wBar = SB_VERT);

            virtual bool FindTextInSelection(tstring Text);
            virtual bool LoadFile(tstring FilePath);

            RichTextBox& operator = (const RichTextBox &R) = delete;
            virtual RichTextBox& operator = (RichTextBox && R);
    };
#endif

    class TabControl: public Control
    {
            //Tab Control, WS_OVERLAPPEDWINDOW | WS_VISIBLE
    };
}

#endif // CONTROL_HPP_INCLUDED
