#pragma once
#include<windows.h>
#include"camera.h"

typedef LRESULT (*WinCallBack) (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


class myWindow
{
public:
	myWindow(const char* WindowName, int Width, int height);
	~myWindow();
	void show();
	HWND getMyWindow();
	void bottonClickDown(int x, int y);
	void bottonClickUp();
	Camera* getCamera();

	bool getClickedPosition(int& x, int& y);
	bool setClickedPosition(int x, int y);

	void setPrivateData(long pointer);

	int width;
	int height;
	bool changeSize;
private:
	WNDCLASS wndClass;
	HWND hwnd;
	char winName[64];
	int botton_click_x;
	int botton_click_y;
	bool button_clicked;
	Camera camera;
};
