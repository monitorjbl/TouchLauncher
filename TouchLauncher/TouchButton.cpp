#include "stdafx.h"
#include "TouchButton.h"

TouchButton::TouchButton(std::string iconFile, std::string caption, int height, int width):
	_iconFile(iconFile), _caption(caption), _height(height), _width(width) {}

TouchButton::~TouchButton() {}

const int TouchButton::getHeight() const {
	return _height;
}

const int TouchButton::getWidth() const {
	return _width;
}

const std::string TouchButton::getIconFile() const {
	return _iconFile;
}

const std::string TouchButton::getCaption() const {
	return _caption;
}
