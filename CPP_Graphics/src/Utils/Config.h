#pragma once

#include <memory>
#include "yaml-cpp/yaml.h"

namespace Utils
{
	class Config
	{
	public:
		static std::shared_ptr<Config> Load(std::string configPath);

		int GetInt(const char* key) const;
		float GetFloat(const char* key) const;
		double GetDouble(const char* key) const;
		std::string GetString(const char* key) const;

		static const std::string DEFAULT_CONFIG_PATH;
	private:
		Config(YAML::Node node): p_node(node) {}
		static void CreateDefault(const char* name);

		YAML::Node p_node;
	};
}