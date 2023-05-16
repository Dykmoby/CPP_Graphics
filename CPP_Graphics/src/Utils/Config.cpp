#include "Config.h"

#include <map>

Config* Config::p_instance = nullptr;

Config* Config::Get()
{
	if (!p_instance)
	{
		p_instance = new Config();
	}
	return p_instance;
}

bool Config::Load(std::string configPath)
{
	std::ifstream configFile(configPath);
	if (!configFile) {
		std::cout << "Failed to open the config file.\n";
		return false;
	}

	Config::Get();

	std::map<std::string, std::string> keysAndValues;

	std::string curLine;
	while (std::getline(configFile, curLine))
	{
		curLine = RemoveSpaces(curLine);

		size_t eqPos = curLine.find('=');
		if (eqPos == std::string::npos) {
			continue;
		}

		std::string key = curLine.substr(0, eqPos);
		std::string value = curLine.substr(eqPos + 1);

		keysAndValues.insert(std::pair<std::string, std::string>(key, value));
	}

	configFile.close();

	p_instance->planetCount = std::stoul(keysAndValues.at("planetCount"));
	p_instance->windowWidth = std::stoul(keysAndValues.at("windowWidth"));
	p_instance->windowHeight = std::stoul(keysAndValues.at("windowHeight"));

	std::cout << "Loaded config: " + configPath + '\n';
	return true;
}
