#include "Config.h"

#include <string>
#include <iostream>
#include <fstream>

namespace Utils
{
	const std::string Config::DEFAULT_CONFIG_PATH = "config.yaml";

	std::shared_ptr<Config> Config::Load(std::string configPath)
	{
		std::ifstream file(configPath);
		if (!file.good())
		{
			std::cout << "Failed to load the config file: " + configPath + ".\n";
			std::cout << "A default config will be created and used instead.";
			Config::CreateDefault(DEFAULT_CONFIG_PATH.c_str());
			YAML::Node node = YAML::LoadFile(DEFAULT_CONFIG_PATH.c_str());
			return std::make_shared<Config>(Config(node));
		}

		YAML::Node node = YAML::LoadFile(configPath);
		return std::make_shared<Config>(Config(node));
	}

	void Config::CreateDefault(const char* name)
	{
		YAML::Node node = YAML::Node();
		node["window_width"] = 800;
		node["window_height"] = 600;
		node["planets_count"] = 500;
		std::ofstream fout(name);
		fout << node;
	}

	int Config::GetInt(const char* key) const
	{
		if (p_node && p_node[key])
		{
			return p_node[key].as<int>();
		}
		return 0;
	}

	float Config::GetFloat(const char* key) const
	{
		if (p_node[key])
		{
			return p_node[key].as<float>();
		}
		return 0.0F;
	}

	double Config::GetDouble(const char* key) const
	{
		if (p_node[key])
		{
			return p_node[key].as<double>();
		}
		return 0.0F;
	}

	std::string Config::GetString(const char* key) const
	{
		if (p_node[key])
		{
			return p_node[key].as<std::string>();
		}
		return "";
	}
}