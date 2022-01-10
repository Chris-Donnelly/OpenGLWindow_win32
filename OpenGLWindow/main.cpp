#include "OpenGLWindow.h"

void MainLogicCB(float delta)
{
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Start renderer window
    COpenGLWindow window(200, 200, 800, 400, L"Window app", MainLogicCB);
    window.Run();

    return 0;
}
