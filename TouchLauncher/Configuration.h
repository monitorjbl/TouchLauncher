#pragma once

#include <string>
#include <vector>
#include "TouchButton.h"

class Configuration{
public:
	Configuration();
	Configuration(std::string configFile);
	~Configuration();

	const std::vector<int> getDisplayOrder() const;
	const std::vector<TouchButton> getButtons() const;
};