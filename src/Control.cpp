#include "Control.hpp"

namespace cxx
{
    std::size_t Control::IDs = 0;

    void Control::Swap(Control &C)
    {
        using std::swap;
        swap(ID, C.ID);
        swap(Handle, C.Handle);
        swap(Parent, C.Parent);
        swap(Class, C.Class);
        swap(Title, C.Title);
        swap(dwExStyle, C.dwExStyle);
        swap(dwStyle, C.dwStyle);
        swap(Location, C.Location);
        swap(Width, C.Width);
        swap(Height, C.Height);
        swap(Functions, C.Functions);
        swap(Initialized, C.Initialized);
    }

    void Control::UnInitialized()
    {
        if (!Initialized)
        {
            throw std::runtime_error("\nError! Control Not Constructed!");
            MessageBox(nullptr, _T("Control Not Constructed!"), _T("Initialization Error!"), MB_ICONERROR);
            ExitProcess(0);
        }
    }

    Control::~Control()
    {
        RemoveWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID));
        SetWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID), 0);
    }

    Control::Control(Control && C) : ID(std::move(C.ID)), Handle(std::move(C.Handle)), Parent(std::move(C.Parent)), Class(std::move(C.Class)), Title(std::move(C.Title)), dwExStyle(std::move(C.dwExStyle)), dwStyle(std::move(C.dwStyle)), Location(std::move(C.Location)), Width(std::move(C.Width)), Height(std::move(C.Height)), Functions(std::move(C.Functions)), Initialized(std::move(C.Initialized))
    {
        RemoveWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID));
        SetWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID), reinterpret_cast<DWORD_PTR>(this));
    }

    Control::Control() : ID(nullptr), Handle(nullptr), Parent(nullptr), Class(tstring()), Title(tstring()), dwExStyle(0), dwStyle(0), Location(Point(0, 0)), Width(0), Height(0), Functions(), Initialized(false) {}

    Control::Control(DWORD dwExStyle, tstring Class, tstring Title, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HINSTANCE Instance, void* LParam) : ID(nullptr), Handle(nullptr), Parent(Parent), Class(Class), Title(Title), dwExStyle(dwExStyle), dwStyle(dwStyle), Location(Location), Width(Width), Height(Height), Functions(), Initialized(true)
    {
        ID = reinterpret_cast<HMENU>(++IDs);
        Handle = CreateWindowEx(dwExStyle, Class.c_str(), Title.c_str(), dwStyle, Location.X, Location.Y, Width, Height, Parent, ID, Instance, LParam);
        SetWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID), reinterpret_cast<DWORD_PTR>(this));
    }

    Control::Control(DWORD dwExStyle, tstring Class, tstring Title, DWORD dwStyle, Point Location, int Width, int Height, HWND Parent, HMENU ID, HINSTANCE Instance, void* LParam) : ID(ID), Handle(nullptr), Parent(Parent), Class(Class), Title(Title), dwExStyle(dwExStyle), dwStyle(dwStyle), Location(Location), Width(Width), Height(Height), Functions(), Initialized(true)
    {
        Handle = CreateWindowEx(dwExStyle, Class.c_str(), Title.c_str(), dwStyle, Location.X, Location.Y, Width, Height, Parent, ID, Instance, LParam);
        SetWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID), reinterpret_cast<DWORD_PTR>(this));
    }

    HMENU Control::GetID() const
    {
        return ID;
    }

    HWND Control::GetHandle() const
    {
        return Handle;
    }

    HWND Control::GetParent() const
    {
        return Parent;
    }

    tstring Control::GetClass() const
    {
        return Class;
    }

    int Control::GetWidth() const
    {
        return Width;
    }

    int Control::GetHeight() const
    {
        return Height;
    }

    Point Control::GetLocation() const
    {
        return Location;
    }

    bool Control::IsEnabled() const
    {
        return IsWindowEnabled(Handle);
    }

    bool Control::IsVisible() const
    {
        return IsWindowVisible(Handle);
    }

    bool Control::GetTabStop() const
    {
        return ((GetWindowLongPtr(Handle, GWL_STYLE) & WS_TABSTOP) != 0);
    }

    void Control::SetTabStop(bool Enabled)
    {
        SetWindowLongPtr(Handle, GWL_STYLE, GetWindowLongPtr(Handle, GWL_STYLE) | WS_TABSTOP);
    }

    void Control::SetEnabled(bool Enabled)
    {
        EnableWindow(Handle, Enabled);
    }

    void Control::SetVisibility(bool Visible)
    {
        ShowWindow(Handle, Visible ? SW_SHOW : SW_HIDE);
    }

    void Control::SetBounds(Box Bounds)
    {
        MoveWindow(Handle, Bounds.X1, Bounds.Y1, Bounds.Width(), Bounds.Height(), false);
    }

    void Control::SetParentHandle(HWND Parent)
    {
        this->Parent = Parent;
    }

    tstring Control::GetText() const
    {
        std::vector<TCHAR> Buffer(GetWindowTextLength(Control::GetHandle()) + 1);
        GetWindowText(Control::GetHandle(), Buffer.data(), Buffer.size());
        return tstring(Buffer.begin(), Buffer.end());
    }

    void Control::SetText(const tstring &Text)
    {
        UnInitialized();
        this->Title = Text;
        SetWindowText(Handle, Text.c_str());
    }

    void Control::SetParent(HWND Parent)
    {
        UnInitialized();
        this->Parent = Parent;
        ::SetParent(Handle, Parent);
        ShowWindow(Handle, SW_SHOW);
    }

    void Control::SetLocation(Point Location)
    {
        UnInitialized();
        this->Location = Location;
        SetWindowPos(Handle, HWND_TOP, Location.X, Location.Y, 0, 0, SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
    }

    void Control::SetSize(int Width, int Height)
    {
        UnInitialized();
        this->Width = Width;
        this->Height = Height;
        SetWindowPos(Handle, HWND_TOP, 0, 0, Width, Height, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
    }

    void Control::SetStyle(DWORD Style, bool RemoveStyle)
    {
        if (RemoveStyle)
        {
            SetWindowLong(Handle, GWL_STYLE, GetWindowLong(Handle, GWL_STYLE) & ~Style);
        }
        else
        {
            SetWindowLong(Handle, GWL_STYLE, GetWindowLong(Handle, GWL_STYLE) | Style);
        }
        SetWindowPos(Handle, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
    }

    void Control::Dispose()
    {
        ID = nullptr;
        Parent = nullptr;

        for (int I = 0; I < 6; ++I)
        {
            Functions[I] = nullptr;
        }

        if (Handle != nullptr)
        {
            RemoveWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID));
            DestroyWindow(Handle);
            Handle = nullptr;
        }
    }

    Control& Control::operator = (Control && C)
    {
        C.Swap(*this);
        RemoveWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID));
        SetWindowSubclass(Handle, SubClass, reinterpret_cast<UINT_PTR>(ID), reinterpret_cast<DWORD_PTR>(this));
        C.Dispose();
        return *this;
    }

    LRESULT __stdcall Control::SubClass(HWND Window, UINT Msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
    {
        //GET DYNAMIC ID.. GetWindowLong(HWnd, GWL_ID);
        //GET CLASS NAME.. GetClassName(HWnd, out LPSTR, MaxCount);
        Control* Instance = reinterpret_cast<Control*>(dwRefData);

        switch(Msg)
        {
            case WM_LBUTTONDOWN:
            {
                return DefSubclassProc(Window, Msg, wParam, lParam);
            }

            case WM_NCDESTROY:
            {
                RemoveWindowSubclass(Window, SubClass, uIdSubclass);
                return DefSubclassProc(Window, Msg, wParam, lParam);
            }

            default:
                return DefSubclassProc(Window, Msg, wParam, lParam);
        }
        return 0;
    }

    Button::~Button() {}

    Button::Button() : Control() {};

    Button::Button(Button && B) : Control(std::move(B)) {}

    Button::Button(tstring Title, Point Location, int Width, int Height, HWND Parent) : Control(0, _T("Button"), Title, WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, Location, Width, Height, Parent, nullptr, nullptr) {}

    Button& Button::operator = (Button && B)
    {
        Control::operator = (std::move(B));
        return *this;
    }

    CheckBox::~CheckBox() {}

    CheckBox::CheckBox() : Control() {};

    CheckBox::CheckBox(CheckBox && C) : Control(std::move(C)) {}

    CheckBox::CheckBox(tstring Title, Point Location, int Width, int Height, HWND Parent, bool Checked) : Control(0, _T("Button"), Title, WS_CHILD | BS_AUTOCHECKBOX | WS_VISIBLE, Location, Width, Height, Parent, nullptr, nullptr)
    {
        if (Checked)
        {
            CheckDlgButton(Control::GetHandle(), reinterpret_cast<std::size_t>(Control::GetID()), BST_CHECKED);
        }
    }

    bool CheckBox::IsChecked()
    {
        return IsDlgButtonChecked(Control::GetHandle(), reinterpret_cast<std::size_t>(Control::GetID()));
    }

    void CheckBox::SetChecked(bool Checked)
    {
        CheckDlgButton(Control::GetHandle(), reinterpret_cast<std::size_t>(Control::GetID()), Checked ? BST_CHECKED : BST_UNCHECKED);
    }

    CheckBox& CheckBox::operator = (CheckBox && C)
    {
        Control::operator = (std::move(C));
        return *this;
    }

    TextBox::~TextBox() {}

    TextBox::TextBox() : Control() {};

    TextBox::TextBox(TextBox && T) : Control(std::move(T)) {}

    TextBox::TextBox(tstring Text, Point Location, int Width, int Height, HWND Parent, bool MultiLine) : Control(WS_EX_STATICEDGE, _T("Edit"), Text, WS_CHILD | WS_VISIBLE | (MultiLine ? ES_MULTILINE | ES_AUTOVSCROLL : 0), Location, Width, Height, Parent, nullptr, nullptr) {}

    void TextBox::SetReadOnly(bool ReadOnly)
    {
        SendMessage(Control::GetHandle(), EM_SETREADONLY, ReadOnly, 0);
    }

    void TextBox::SetPassword(bool Enabled, char PasswordChar)
    {
        SendMessage(Control::GetHandle(), EM_SETPASSWORDCHAR, Enabled ? PasswordChar : 0, 0);
    }

    std::uint32_t TextBox::GetTextLength() const
    {
        return GetWindowTextLength(Control::GetHandle());
    }

    void TextBox::ShowScrollBar(bool Show, int wBar)
    {
        ::ShowScrollBar(Control::GetHandle(), wBar, true);
    }

    void TextBox::AppendText(const tstring &Text) const
    {
        SendMessage(Control::GetHandle(), EM_SETSEL, -1, -1);
        SendMessage(Control::GetHandle(), EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(Text.c_str()));
    }

    TextBox& TextBox::operator = (TextBox && T)
    {
        Control::operator = (std::move(T));
        return *this;
    }

    ListBox::~ListBox() {}

    ListBox::ListBox() : Control() {};

    ListBox::ListBox(ListBox && L) : Control(std::move(L)) {}

    ListBox::ListBox(Point Location, int Width, int Height, HWND Parent) : Control(WS_EX_CLIENTEDGE, _T("Listbox"), tstring(), WS_CHILD | WS_VISIBLE | LBS_NOTIFY, Location, Width, Height, Parent, nullptr, nullptr) {}

    int ListBox::GetItemCount() const
    {
        return SendMessage(Control::GetHandle(), LB_GETCOUNT, 0, 0);
    }

    int ListBox::GetSelectedIndex() const
    {
        return SendMessage(Control::GetHandle(), LB_GETCURSEL, 0, 0);
    }

    void ListBox::SetSelectedIndex(int Index)
    {
        SendMessage(Control::GetHandle(), LB_SETCURSEL, Index, 0);
    }

    void ListBox::AddItem(const tstring &Item, int Index)
    {
        SendMessage(Control::GetHandle(), Index == 0 ? LB_ADDSTRING : LB_INSERTSTRING, Index, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    void ListBox::RemoveItem(int Index)
    {
        SendMessage(Control::GetHandle(), LB_DELETESTRING, Index, 0);
    }

    void ListBox::Clear()
    {
        SendMessage(Control::GetHandle(), LB_RESETCONTENT, 0, 0);
    }

    int ListBox::GetIndexOf(const tstring &Item)
    {
        return SendMessage(Control::GetHandle(), LB_FINDSTRINGEXACT, -1, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    int ListBox::GetIndexPartial(const tstring &Item)
    {
        return SendMessage(Control::GetHandle(), LB_FINDSTRING, -1, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    void ListBox::SetColumnWidth(int Width)
    {
        SendMessage(Control::GetHandle(), LB_SETCOLUMNWIDTH, Width, 0);
    }

    tstring ListBox::GetItem(int Index) const
    {
        std::vector<char> Buffer(SendMessage(Control::GetHandle(), LB_GETTEXTLEN, Index, 0) + 1);
        SendMessage(Control::GetHandle(), LB_GETTEXT, Index, reinterpret_cast<LPARAM>(Buffer.data()));
        return tstring(Buffer.begin(), Buffer.end());
    }

    ListBox& ListBox::operator = (ListBox && L)
    {
        Control::operator = (std::move(L));
        return *this;
    }

    ComboBox::~ComboBox() {}

    ComboBox::ComboBox() : Control() {};

    ComboBox::ComboBox(ComboBox && L) : Control(std::move(L)) {}

    ComboBox::ComboBox(DropDownStyle Style, Point Location, int Width, int Height, HWND Parent) : Control(WS_EX_CLIENTEDGE, _T("ComboBox"), tstring(), (Style == DropDownStyle::STYLE_SIMPLE ? CBS_SIMPLE : Style == DropDownStyle::STYLE_DROPDOWN ? CBS_DROPDOWN : CBS_DROPDOWNLIST) | WS_CHILD | WS_VISIBLE, Location, Width, Height, Parent, nullptr, nullptr) {}

    int ComboBox::GetItemCount() const
    {
        return SendMessage(Control::GetHandle(), CB_GETCOUNT, 0, 0);
    }

    int ComboBox::GetSelectedIndex() const
    {
        return SendMessage(Control::GetHandle(), CB_GETCURSEL, 0, 0);
    }

    void ComboBox::SetSelectedIndex(int Index)
    {
        SendMessage(Control::GetHandle(), CB_SETCURSEL, Index, 0);
    }

    void ComboBox::AddItem(const tstring &Item, int Index)
    {
        SendMessage(Control::GetHandle(), Index == 0 ? CB_ADDSTRING : CB_INSERTSTRING, Index, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    void ComboBox::RemoveItem(int Index)
    {
        SendMessage(Control::GetHandle(), CB_DELETESTRING, Index, 0);
    }

    void ComboBox::Clear()
    {
        SendMessage(Control::GetHandle(), CB_RESETCONTENT, 0, 0);
    }

    int ComboBox::GetIndexOf(const tstring &Item)
    {
        return SendMessage(Control::GetHandle(), CB_FINDSTRINGEXACT, -1, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    int ComboBox::GetIndexPartial(const tstring &Item)
    {
        return SendMessage(Control::GetHandle(), CB_FINDSTRING, -1, reinterpret_cast<LPARAM>(Item.c_str()));
    }

    void ComboBox::SetDropDownWidth(int Width)
    {
        SendMessage(Control::GetHandle(), CB_SETDROPPEDWIDTH, Width, 0);
    }

    void ComboBox::SetDropDownStyle(DropDownStyle Style)
    {
        Control::SetStyle(CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST, true);
        Control::SetStyle(Style == DropDownStyle::STYLE_SIMPLE ? CBS_SIMPLE : Style == DropDownStyle::STYLE_DROPDOWN ? CBS_DROPDOWN : CBS_DROPDOWNLIST);
    }

    tstring ComboBox::GetItem(int Index) const
    {
        std::vector<char> Buffer(SendMessage(Control::GetHandle(), CB_GETLBTEXTLEN, Index, 0) + 1);
        SendMessage(Control::GetHandle(), CB_GETLBTEXT, Index, reinterpret_cast<LPARAM>(Buffer.data()));
        return tstring(Buffer.begin(), Buffer.end());
    }

    ComboBox& ComboBox::operator = (ComboBox && C)
    {
        Control::operator = (std::move(C));
        return *this;
    }

    PictureBox::~PictureBox() {}

    PictureBox::PictureBox() : Control() {};

    PictureBox::PictureBox(PictureBox && P) : Control(std::move(P)) {}

    PictureBox::PictureBox(Point Location, int Width, int Height, HWND Parent) : Control(WS_EX_CLIENTEDGE, _T("Static"), tstring(), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_BITMAP, Location, Width, Height, Parent, nullptr, nullptr) {}

    void PictureBox::SetImage(HBITMAP Img)
    {
        SendMessage(Control::GetHandle(), STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(Img));
    }

    void PictureBox::SetImage(Image Img)
    {
        SendMessage(Control::GetHandle(), STM_SETIMAGE, IMAGE_BITMAP, reinterpret_cast<LPARAM>(Img.ToHBitmap()));
    }

    PictureBox& PictureBox::operator = (PictureBox && P)
    {
        Control::operator = (std::move(P));
        return *this;
    }


    MenuBar::~MenuBar() {}

    MenuBar::MenuBar() : Control(), Menus() {};

    MenuBar::MenuBar(MenuBar && M) : Control(std::move(M)), Menus(std::move(M.Menus)) {}

    MenuBar::MenuBar(HWND Parent) : Control(), Menus()
    {
        Control::Initialized = false;
        this->SetParentHandle(Parent);
        Menus.push_back(CreateMenu());
    }

    tstring MenuBar::GetText(HMENU Menu, int Position)
    {
        TCHAR Buffer[1024] = {0};
        MENUITEMINFO MenuInfo = {0};
        MenuInfo.cbSize = sizeof(MenuInfo);
        MenuInfo.fMask = MIIM_TYPE;
        MenuInfo.fType = MFT_STRING;
        MenuInfo.cch = sizeof(Buffer);
        MenuInfo.dwTypeData = Buffer;
        if (GetMenuItemInfo(Menu, Position, true, &MenuInfo))
        {
            return Buffer;
        }
        return tstring();
    }

    std::uint32_t MenuBar::GetMenuItemID(HMENU Menu, int Position)
    {
        return ::GetMenuItemID(Menu, Position);
    }

    HMENU MenuBar::FindMenuItem(tstring MenuName)
    {
        for (std::size_t I = 0; I < Menus.size(); ++I)
        {
            if (MenuName == GetText(Menus.front(), I))
            {
                return GetSubMenu(Menus.front(), I);
            }
        }
        return nullptr;
    }

    HMENU MenuBar::FindMenuItem(HMENU Parent, tstring MenuName)
    {
        std::size_t Count = GetMenuItemCount(Parent);
        for (std::size_t I = 0; I < Count; ++I)
        {
            if (MenuName == GetText(Parent, I))
            {
                return GetSubMenu(Parent, I);
            }
        }
        return nullptr;
    }

    void MenuBar::CreateSubMenu(HMENU Parent, tstring Name, DWORD Style)
    {
        Menus.push_back(CreatePopupMenu());
        AppendMenu(Parent, Style, reinterpret_cast<UINT_PTR>(Menus.back()), Name.c_str());
    }

    void MenuBar::AddMenuItem(tstring Name, DWORD Style)
    {
        Menus.push_back(CreateMenu());
        MENUINFO MenuInfo = {0};
        MenuInfo.cbSize = sizeof(MenuInfo);
        MenuInfo.fMask = MIM_STYLE;
        GetMenuInfo(Menus.back(), &MenuInfo);
        MenuInfo.dwStyle |= MNS_NOTIFYBYPOS;
        SetMenuInfo(Menus.back(), &MenuInfo);
        AppendMenu(Menus.front(), Style, reinterpret_cast<UINT_PTR>(Menus.back()), Name.c_str());
    }

    void MenuBar::AppendMenuItem(HMENU Parent, tstring Name, DWORD Style)
    {
        static int ID = 0;
        AppendMenu(Parent, Style, ++ID, Name.c_str());
    }

    bool MenuBar::ToggleItemCheck(HMENU MenuItem, int Position)
    {
        MENUITEMINFO MenuInfo = {0};
        MenuInfo.cbSize = sizeof(MenuInfo);
        MenuInfo.fMask = MIIM_STATE;
        GetMenuItemInfo(MenuItem, Position, true, &MenuInfo);
        MenuInfo.fState = (MenuInfo.fState & MF_CHECKED ? MenuInfo.fState & ~MF_CHECKED : MenuInfo.fState | MF_CHECKED);
        SetMenuItemInfo(MenuItem, Position, true, &MenuInfo);
        return MenuInfo.fState & MF_CHECKED;
    }

    bool MenuBar::IsItemChecked(HMENU MenuItem, int Position)
    {
        MENUITEMINFO MenuInfo = {0};
        MenuInfo.cbSize = sizeof(MenuInfo);
        MenuInfo.fMask = MIIM_STATE;
        GetMenuItemInfo(MenuItem, Position, true, &MenuInfo);
        return MenuInfo.fState & MF_CHECKED;
    }

    void MenuBar::Show()
    {
        SetMenu(Control::GetParent(), Menus.front());
    }

    MenuBar& MenuBar::operator = (MenuBar && M)
    {
        Control::operator = (std::move(M));
        return *this;
    }


    ToolBar::~ToolBar() {}

    ToolBar::ToolBar() : Control() {};

    ToolBar::ToolBar(ToolBar && T) : Control(std::move(T)) {}

    ToolBar::ToolBar(Point Location, int Width, int Height, HWND Parent) : Control(0, TOOLBARCLASSNAME, tstring(), WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT | CCS_ADJUSTABLE | CCS_NODIVIDER, Location, Width, Height, Parent, nullptr, nullptr) {}

    ToolBar& ToolBar::operator = (ToolBar && T)
    {
        Control::operator = (std::move(T));
        return *this;
    }

#ifdef UNICODE
    int RichTextBox::Instances = 0;
    HMODULE RichTextBox::Module = xLoadLibrary(_T("Msftedit.dll"));

    RichTextBox::~RichTextBox()
    {
        if (--RichTextBox::Instances == 0)
        {
            xFreeLibrary(RichTextBox::Module);
        }
    }

    RichTextBox::RichTextBox() : Control()
    {
        ++RichTextBox::Instances;
    };

    RichTextBox::RichTextBox(RichTextBox && R) : Control(std::move(R))
    {
        ++RichTextBox::Instances;
    }

    RichTextBox::RichTextBox(tstring Text, Point Location, int Width, int Height, HWND Parent, bool MultiLine) : Control(WS_EX_STATICEDGE, MSFTEDIT_CLASS, Text, WS_CHILD | WS_VISIBLE | (MultiLine ? ES_MULTILINE | ES_AUTOVSCROLL : 0), Location, Width, Height, Parent, nullptr, nullptr)
    {
        ++RichTextBox::Instances;
    }

    void RichTextBox::SetReadOnly(bool ReadOnly)
    {
        SendMessage(Control::GetHandle(), EM_SETREADONLY, ReadOnly, 0);
    }

    void RichTextBox::SetPassword(bool Enabled, char PasswordChar)
    {
        SendMessage(Control::GetHandle(), EM_SETPASSWORDCHAR, Enabled ? PasswordChar : 0, 0);
    }

    std::uint32_t RichTextBox::GetTextLength() const
    {
        return GetWindowTextLength(Control::GetHandle());
    }

    void RichTextBox::ShowScrollBar(bool Show, int wBar)
    {
        ::ShowScrollBar(Control::GetHandle(), wBar, true);
    }

    void RichTextBox::AppendText(const tstring &Text) const
    {
        SendMessage(Control::GetHandle(), EM_SETSEL, -1, -1);
        SendMessage(Control::GetHandle(), EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(Text.c_str()));
    }

    bool RichTextBox::FindTextInSelection(tstring Text)
    {
        CHARRANGE SelectedRange;
        FINDTEXTEX FindTextEx;
        SendMessage(Control::GetHandle(), EM_EXGETSEL, 0, reinterpret_cast<LPARAM>(&SelectedRange));

        FindTextEx.lpstrText = Text.c_str();
        FindTextEx.chrg.cpMin = SelectedRange.cpMin;
        FindTextEx.chrg.cpMax = SelectedRange.cpMax;
        if (SendMessage(Control::GetHandle(), EM_FINDTEXTEXW, static_cast<WPARAM>(FR_DOWN), reinterpret_cast<LPARAM>(&FindTextEx)) > 0)
        {
            SendMessage(Control::GetHandle(), EM_EXSETSEL, 0, reinterpret_cast<LPARAM>(&FindTextEx.chrgText));
            SendMessage(Control::GetHandle(), EM_HIDESELECTION, false, 0);
            return true;
        }
        return false;
    }

    bool RichTextBox::LoadFile(tstring FilePath)
    {
        HANDLE hFile = CreateFile(FilePath.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            EDITSTREAM Stream = {0};
            Stream.dwCookie = reinterpret_cast<DWORD_PTR>(hFile);
            Stream.pfnCallback = RichTextBox::EditStreamCallback;
            if (SendMessage(Control::GetHandle(), EM_STREAMIN, SF_RTF, reinterpret_cast<LPARAM>(&Stream)) && !Stream.dwError)
            {
                CloseHandle(hFile);
                return true;
            }
        }
        CloseHandle(hFile);
        return false;
    }

    DWORD __stdcall RichTextBox::EditStreamCallback(DWORD_PTR dwCookie, std::uint8_t* Buffer, LONG cb, LONG* pcb)
    {
        HANDLE hFile = reinterpret_cast<HANDLE>(dwCookie);
        if (ReadFile(hFile, Buffer, cb, reinterpret_cast<DWORD*>(pcb), nullptr))
        {
            return 0;
        }
        return -1;
    }

    RichTextBox& RichTextBox::operator = (RichTextBox && R)
    {
        Control::operator = (std::move(R));
        return *this;
    }
#endif
}
