#include "stdafx.h"
#include "MouseTracker.h"

MouseTracker::MouseTracker() {}

MouseTracker::~MouseTracker() {}

void MouseTracker::start() {
	DWORD ThreadID;
	_running = true;
	CreateThread(NULL, 0, StaticThreadStart, (void*) this, 0, &ThreadID);
}

void MouseTracker::stop() {
	_running = false;
}

void MouseTracker::setWindowHandle(HWND window) {
	_thisWindow = window;
}

DWORD MouseTracker::threadStart(void){
	while (true) {
		RECT r = { 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
		//GetWindowRect(_thisWindow, &r);
		ClipCursor(&r);

		if (GetAsyncKeyState(VK_F12)) {
			break;
		}

		if (GetAsyncKeyState(VK_LBUTTON)) {
			HWND  hwndPt;
			POINT pt;

			if (!GetCursorPos(&pt)) {
				wprintf(L"GetCursorPos failed with %d\n", GetLastError());
				break;
			}

			if ((hwndPt = WindowFromPoint(pt)) != NULL) {
				DWORD  dwPID;
				HANDLE hProcess;

				GetWindowThreadProcessId(hwndPt, &dwPID);

				hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, dwPID);

				if (hProcess == NULL) {
					wprintf(L"OpenProcess failed with error: %d\n", GetLastError());
				} else {
					wchar_t lpFileName[MAX_PATH];
					DWORD   dwSize = _countof(lpFileName);

					QueryFullProcessImageName(hProcess, 0, lpFileName, &dwSize);

					if (hwndPt == _thisWindow && _lastWindow != NULL) {
						wchar_t str[256];
						wsprintf(str, L"Transferring back to %d (%d,%d)\n", _lastWindow, _lastPoint.x, _lastPoint.y);
						OutputDebugString(str);
						//ClientToScreen(_lastWindow, &_lastPoint);
						//SetCursorPos(_lastPoint.x, _lastPoint.y);
						ShowCursor(false);
						SetCursorPos(_lastPoint.x, _lastPoint.y);
						ShowCursor(true);
					}  else {
						_lastWindow = hwndPt;
						_lastPoint = pt;
					}

					CloseHandle(hProcess);
				}
			}
		}

		Sleep(10);
	}
	return NULL;
}

DWORD WINAPI MouseTracker::StaticThreadStart(void* Param) {
	MouseTracker* This = (MouseTracker*)Param;
	return This->threadStart();
}

BOOL WINAPI TrackMouseEvent(_Inout_ LPTRACKMOUSEEVENT lpEventTrack) {
	wchar_t str[256];
	wsprintf(str, L"Mouse in this window: %d \n", lpEventTrack->hwndTrack);
	OutputDebugString(str);

	return true;
}