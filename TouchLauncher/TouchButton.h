#pragma once

#include <string>

class TouchButton {
public:
	TouchButton(std::string iconFile, std::string caption, int height, int width);
	~TouchButton();

	const int getHeight() const;
	const int getWidth() const;
	const std::string getIconFile() const;
	const std::string getCaption() const;
private:
	int _height, _width;
	std::string _iconFile, _caption;
};