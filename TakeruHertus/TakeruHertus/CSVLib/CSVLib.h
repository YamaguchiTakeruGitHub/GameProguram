#pragma once
#include <string>
#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>




class CSVLib
{
public:

	template<typename T>
	inline std::vector<T> loadCSV(const std::string& _filename, std::function<T(const std::vector<std::string>&)> _parseFunction)
	{
		std::vector<T> result;
		std::ifstream file(_filename);

		if (!file.is_open())
		{
			std::cerr << "filed to open file:" << _filename << std::endl;
			return result;
		}

		std::string line;
		std::getline(file, line);

		while (std::getline(file, line))
		{
			std::istringstream ss(line);
			std::string token;
			std::vector<std::string> tokens;

			while (std::getline(ss, token, ','))
			{
				token.push_back(token);
			}

			result.push_back(_parseFunction(token));
		}

		file.close();
		return result;
	}



	template<typename T>
	void saveCSV(const std::string& _filename, const std::vector<T>& _data, std::function<std::vector<std::string>(const T&)> _formatFunction)
	{
		std::ofstream file(_filename);

		if (!file.is_open())
		{
			std::cerr << "filed to open file for writing:" << _filename << std::endl;

			return;
		}

		for (const auto& item : _data)
		{
			std::vector<std::string> tokens = _formatFunction(item);
			for (size_t i = 0; i < tokens.size(); i++)
			{
				file << tokens[i];
				if (i < tokens.size() - 1) file << ',';
			}
			file << "/n";
		}

		file.close();
	}

};


