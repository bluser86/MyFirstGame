#include "win.h"
#include <tchar.h>

//////////////////////////////////////////////////////////////////
// Static Initialisation
//////////////////////////////////////////////////////////////////
static CWin * g_pCWin		= NULL;
HINSTANCE CWin::m_hInstance = GetModuleHandle(NULL);

//////////////////////////////////////////////////////////////////
// Connectivity WIN32 -> Class
//////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return g_pCWin->MsgProc(hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////////
// Constructors/Destructors
//////////////////////////////////////////////////////////////////
CWin::CWin()
{
    g_pCWin		 = this;

    this->m_hWnd = NULL;
    this->m_dwCreationFlags  = 0L;
    this->m_dwWindowStyle	 = WS_OVERLAPPEDWINDOW;
    this->m_dwExWindowStyle	 = WS_EX_OVERLAPPEDWINDOW;
    this->m_dwCreationFlags	 = SW_SHOW;
    this->m_PosX			 = CW_USEDEFAULT;	
    this->m_PosY			 = CW_USEDEFAULT;	
    this->m_dwCreationWidth	 = CW_USEDEFAULT;
    this->m_dwCreationHeight = CW_USEDEFAULT;
    this->m_hbrWindowColor	 = (HBRUSH)(COLOR_WINDOW+1);
    this->m_hIcon			 = LoadIcon(m_hInstance, (LPCTSTR)IDI_APPLICATION);
    this->m_strWindowTitle	 = _T("Win32 OO Skeleton Program...");
    this->m_hMenu			 = NULL; 	
}

CWin::~CWin()
{
}


//////////////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////////////
int CWin::Run()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (!TranslateAccelerator(msg.hwnd, m_hAccelTable, &msg)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

    }	return msg.wParam;
}

HWND CWin::GetHWND()
{
    return this->m_hWnd;
}

HRESULT CWin::Create()
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX); 

    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = (WNDPROC)WndProc;
    wcex.cbClsExtra	   = 0;
    wcex.cbWndExtra	   = 0;
    wcex.hInstance     = m_hInstance;
    wcex.hIcon         = m_hIcon;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = m_hbrWindowColor;
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = _T("Skeleton");
    wcex.hIconSm       = NULL;

    ::RegisterClassEx(&wcex);

    m_hWnd = ::CreateWindowEx(m_dwExWindowStyle,_T("Skeleton"), m_strWindowTitle, m_dwWindowStyle,
        m_PosX, m_PosY, m_dwCreationWidth, m_dwCreationHeight, NULL, m_hMenu, m_hInstance, NULL);

    if (!m_hWnd)
    {
        return FALSE;
    }

    RECT rcClient, rcWindow;
    POINT ptDiff;
    GetClientRect(m_hWnd, &rcClient);
    GetWindowRect(m_hWnd, &rcWindow);
    ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
    ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
    MoveWindow(m_hWnd, rcWindow.left, rcWindow.top, m_dwCreationWidth + ptDiff.x, 
        m_dwCreationHeight + ptDiff.y, TRUE);

    ::ShowWindow(m_hWnd, m_dwCreationFlags);
    ::UpdateWindow(m_hWnd);

    return TRUE;

}

LRESULT CWin::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId;
    int wmEvent;

    if (!m_hWnd)
        m_hWnd = hWnd;

    switch (uMsg) 
    {
    case WM_COMMAND:
        wmId    = LOWORD(wParam); 
        wmEvent = HIWORD(wParam); 
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}
