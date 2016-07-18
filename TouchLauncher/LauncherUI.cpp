#include "stdafx.h"
#include "LauncherUI.h"
#include <stdio.h>

#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

LauncherUI::LauncherUI() {};

LauncherUI::~LauncherUI() {};

void LauncherUI::setDisplayOrder(std::vector<int> &displayOrder) {
	_displayOrder = displayOrder;
}
void LauncherUI::setButtons(std::vector<TouchButton> &buttons) {
	_buttons = buttons;
}

void LauncherUI::draw(HWND &hWnd, HDC &hdc) {
	//get window height and width
	RECT rect;
	GetWindowRect(hWnd, &rect);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;

	std::vector<Grid> drawPositions = generateGrid(2, 2, windowWidth, windowHeight, 0, 0);
	for (unsigned int index = 0; index < _buttons.size() && index < drawPositions.size(); index++) {
		Grid grid = drawPositions[index];
		TouchButton btn = _buttons[index];

		std::string iconFile = btn.getIconFile();
		int iconWidth = btn.getWidth();
		int iconHeight = btn.getHeight();

		//if icon bigger than grid, shrink icon to match
		if (iconWidth > grid.width) {
			iconWidth = grid.width;
		}
		if (iconHeight > grid.height) {
			iconHeight = grid.height;
		}

		//center icon vertically and horizontally
		GridPoint point = centerInGrid(grid, iconWidth, iconHeight);

		//debug output
		wchar_t str[256];
		wsprintf(str, L"draw index: %d at (%d,%d) \n", index, point.x, point.y);
		OutputDebugString(str);

		//draw icon
		drawBitmap(hWnd, hdc, iconFile, point.x, point.y, iconWidth, iconHeight);
	}

	drawGridLines(hdc, drawPositions);
}

GridPoint LauncherUI::centerInGrid(Grid grid, int innerWidth, int innerHeight) {
	int x = grid.x + ((grid.width - innerWidth) / 2);
	int y = grid.y + ((grid.height - innerHeight) / 2);
	return{ x, y };
}

std::vector<Grid> LauncherUI::generateGrid(int rows, int columns, int totalWidth,
	int totalHeight, int offsetX, int offsetY) {

	int widthPerIcon = totalWidth / columns;
	int heightPerIcon = totalHeight / rows;

	std::vector<Grid> grids;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int x = j * widthPerIcon + offsetX;
			int y = i * heightPerIcon + offsetY;

			grids.push_back({x,y,widthPerIcon,heightPerIcon});
		}
	}
	return grids;
}

void inline LauncherUI::drawBitmap(HWND &hWnd, HDC &hdc, std::string &iconFile, 
	int x, int y, int width, int height) {
	HBITMAP bitmap;
	HDC hdcMem;

	std::wstring stemp = std::wstring(iconFile.begin(), iconFile.end());
	bitmap = (HBITMAP)LoadImageW(NULL, stemp.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	if (bitmap == NULL) {
		wchar_t str[256];
		wsprintfW(str, L"Icon file %hs not found \n", iconFile.c_str());
		OutputDebugString(str);
	}

	hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, bitmap);

	BitBlt(hdc, x, y, width, height, hdcMem, 0, 0, SRCCOPY);

	DeleteDC(hdcMem);
	DeleteObject(bitmap);
}

void inline LauncherUI::drawGridLines(HDC &hdc, std::vector<Grid> &grids) {
	Graphics graphics(hdc);
	Pen      pen(Color(255, 255, 0, 255));
	pen.SetWidth(10);

	for (int i = 0; i < grids.size(); i++) {
		Grid grid = grids[i];
		graphics.DrawLine(&pen, grid.x, grid.y, grid.x + grid.width, grid.y);
		graphics.DrawLine(&pen, grid.x, grid.y, grid.x, grid.y + grid.height);
		graphics.DrawLine(&pen, grid.x, grid.y + grid.height, grid.x + grid.width, grid.y + grid.height);
		graphics.DrawLine(&pen, grid.x + grid.width, grid.y, grid.x + grid.width, grid.y + grid.height);
	}

}