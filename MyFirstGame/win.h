#include <windows.h>
#include <tchar.h>
#include "resource.h"

class CWin
{
protected:
    static HINSTANCE m_hInstance;
    HWND  m_hWnd;

    DWORD  m_PosX;
    DWORD  m_PosY;
    DWORD  m_dwWindowStyle;
    DWORD  m_dwExWindowStyle;
    DWORD  m_dwCreationFlags;
    int    m_dwCreationHeight;
    int    m_dwCreationWidth;
    TCHAR* m_strWindowTitle;
    HBRUSH m_hbrWindowColor;
    HICON  m_hIcon;
    HMENU  m_hMenu;
    HACCEL m_hAccelTable;

public:
    CWin();
    HRESULT Create();
    int Run();
    HWND GetHWND(void);
    virtual ~CWin();
    virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};