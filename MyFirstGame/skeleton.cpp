#include "skeleton.h"


DWORD dwFrames;
DWORD dwCurrentTime;
DWORD dwLastUpdateTime;
DWORD dwElapsedTime;
TCHAR szFPS[32];

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSkeleton::CSkeleton()
{
    // Zero out the frames per second variables:
    dwFrames = 0;
    dwCurrentTime = 0;
    dwLastUpdateTime = 0;
    dwElapsedTime = 0;
    szFPS[0] = '\0';
}

CSkeleton::~CSkeleton()
{
}

/////////////////////////////////////
// Member functions                  //
/////////////////////////////////////

LRESULT CSkeleton::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //these hold the dimensions of the client window area
    static int cxClient, cyClient; 

    //used to create the back buffer
    static HDC		hdcBackBuffer;
    static HBITMAP	hBitmap;
    static HBITMAP	hOldBitmap;

    PAINTSTRUCT ps;
    HDC hdc;


    switch (uMsg)
    {
    case WM_CREATE:
        {
            // Get device context that belongs to our client window.
            hdc = ::GetDC(hWnd);

            // Get the coordinates of our client window. The returned 
            // rectangle is provided through th scrnSize reference.
            ::GetClientRect(hWnd, &scrnSize);

            // Create a compatible device context based on the client window
            // device context.
            hdcBackBuffer = CreateCompatibleDC(hdc);

            // Create a canvas for us to draw on based on the client window
            // device context.
            hBitmap = CreateCompatibleBitmap(hdc, (32*30), (32*10)*3);

            // Select the canvas into the backbuffer device context.
            SelectObject(hdcBackBuffer, hBitmap);

            // Release the device context of the client window.
            ::ReleaseDC(hWnd, hdc);

            // Set a timer and attach it to the client window
            ::SetTimer(hWnd, TM_TIMER, 0, NULL);
        }
        break;
    case WM_PAINT:
        {
            // Don't uncomment this, or the application wil crash later on! See 
            // http://msdn.microsoft.com/en-us/library/windows/desktop/dd183518(v=vs.85).aspx

            // Every paint event the backbuffer is filled with a solid brush. The brush, however, is never 
            // deleted. It's not so weird that the program will crash because this manifests a memory leak. 
            // The heap will be overflown with HBRUSH objects. In the documentation linked above it's clearly 
            // stated the brush needs to be deleted!
            HBRUSH hBrush = ::CreateSolidBrush(RGB(51, 102,255));
            ::FillRect(hdcBackBuffer, &scrnSize, hBrush); 
            ::DeleteObject(hBrush);

            // Calculate the number of frames per one second:
            dwFrames++;
            dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
            dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

            if(dwElapsedTime >= 1000)
            {
                wsprintf(szFPS, _T("FPS = %u"), (UINT)(dwFrames * 1000.0 / dwElapsedTime));
                dwFrames = 0;
                dwLastUpdateTime = dwCurrentTime;
            }

            // Write the FPS onto the Memory DC.
            TextOut(hdcBackBuffer, 0, 0, szFPS, lstrlen(szFPS));

            // Start painting
            hdc=::BeginPaint(hWnd, &ps);

            // Bring backbuffer to front
            BitBlt(hdc, ps.rcPaint.left,ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom, hdcBackBuffer, 0, 0, SRCCOPY);

            // End painting
            ::EndPaint(hWnd, &ps);

        }
        break;
    case WM_ERASEBKGND:
        return 1;
        break;
    case WM_TIMER:
        switch(wParam)
        {
        case TM_TIMER:
            ::InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        break;
    }

    return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}