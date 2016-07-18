#pragma once

#include <vector>
#include "TouchButton.h"

struct GridPoint {
	int x, y;
};

struct Grid {
	int x, y, width, height;
};

class LauncherUI {
public:
	LauncherUI();
	~LauncherUI();

	// setters
	void setDisplayOrder(std::vector<int> &displayOrder);
	void setButtons(std::vector<TouchButton> &buttons);

	// draw UI
	void draw(HWND &hWnd, HDC &hdc);

private:
	std::vector<int> _displayOrder;
	std::vector<TouchButton> _buttons;

	void inline drawBitmap(HWND &hWnd, HDC &hdc, std::string &iconFile, int x, int y, int width, int height);
	void inline drawGridLines(HDC &hdc, std::vector<Grid> &grids);

	std::vector<Grid> generateGrid(int rows, int columns, int totalWidth, 
		int totalHeight, int offsetX = 0, int offsetY = 0);
	GridPoint centerInGrid(Grid grid, int innerWidth, int innerHeight);
};