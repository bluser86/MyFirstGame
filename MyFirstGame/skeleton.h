#include "win.h"

class CSkeleton : public CWin
{
private:
    HDC hBufferDC;
    HBITMAP hBufferBMP;
    RECT scrnSize;
public:
    CSkeleton();
    ~CSkeleton();

    LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};