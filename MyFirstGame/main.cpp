#include "skeleton.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>


int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    CSkeleton app;

    if (!app.Create())
        return 0;

    return app.Run();
}