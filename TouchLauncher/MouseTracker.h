#pragma once

class MouseTracker {
public:
	MouseTracker();
	~MouseTracker();

	void start();
	void stop();
	void setWindowHandle(HWND window);
private:
	bool _running;
	HWND _thisWindow;
	HWND _lastWindow = NULL;
	POINT _lastPoint = {0,0};
	DWORD threadStart(void);
	static DWORD WINAPI StaticThreadStart(void* Param);
};