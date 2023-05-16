#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Config
{
public:
	static Config* Get();
	static bool Load(std::string configPath = p_defaultConfigPath);

	unsigned int planetCount = 0;
	unsigned int windowWidth = 800;
	unsigned int windowHeight = 600;
private:
	Config() {}
	static Config* p_instance;

	static inline const std::string p_defaultConfigPath = "config.txt";

	static std::string RemoveSpaces(std::string inputStr)
	{
        bool b_insideQuotes = false;
        std::string result = "";

        for (char c : inputStr) {
            if (c == '"') {
                b_insideQuotes = !b_insideQuotes;
                result += c;
            }
            else if (!b_insideQuotes && c == ' ') {
                continue;
            }
            else {
                result += c;
            }
        }

        return result;
	}
};