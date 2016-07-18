#include "stdafx.h"
#include "Configuration.h"

Configuration::Configuration() {}

Configuration::~Configuration() {}

const std::vector<int> Configuration::getDisplayOrder() const {
	std::vector<int> order;
	order.push_back(0);
	return order;
}

const std::vector<TouchButton> Configuration::getButtons() const {
	//TODO: load this from a JSON config file
	std::string fileName = "C:\\WoW.bmp";
	std::string caption = "butts";
	TouchButton tb(fileName, caption, 256, 256);

	std::vector<TouchButton> buttons;
	buttons.push_back(tb);
	buttons.push_back(tb);
	buttons.push_back(tb);
	buttons.push_back(tb);
	buttons.push_back(tb);
	return buttons;
}