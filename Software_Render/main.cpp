
#include"SoftRenderWindow.h"

int main()
{
	softRenderWindow win("render",800,600);
	win.show();
	bool exit = false;
	MSG msg;
	while (!exit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				exit = true;
			else if (win.changeSize)
			{
				win.initBitmapEnv(win.width, win.height);
				InvalidateRect(win.getMyWindow(), NULL, FALSE);
				win.changeSize = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			Sleep(1000);
			win.swapBuffer();
		}
	}
	return 0;
}