#include "Segments.h"



Segments::Segments()
{
}


Segments::~Segments()
{
}

std::set<std::string> Segments::exec(std::string str)
{
	auto result = std::set<std::string>();
	for (auto s : this->major(str))
	{
		auto ss = this->minor(s);
		result.insert(ss.begin(), ss.end());
	}
	return result;
}

std::set<std::string> Segments::major(std::string originalString)
{
	auto result = std::set<std::string>();
	int splitIndex = 0;
	std::array<std::string, 2> splits = {" ", "="};
	for (int i = 0, j = originalString.length(); i < j; ++i)
	{
		std::stringstream stream;
		stream << originalString[i];
		std::string s = stream.str();
		if (std::find(splits.begin(), splits.end(), s) != splits.end())
		{
			auto str = originalString.substr(splitIndex, i - splitIndex);
			if(str != "") result.insert(str);
			splitIndex = i + 1;
		}
	}
	result.insert(originalString.substr(splitIndex, originalString.length() - splitIndex));
	return result;
}

std::set<std::string> Segments::minor(std::string originalString)
{
	auto result = std::set<std::string>();
	int splitIndex = 0;
	std::array<std::string, 2> splits = { "_", "." };
	for (int i = 0, j = originalString.length(); i < j; ++i)
	{
		std::stringstream stream;
		stream << originalString[i];
		std::string s = stream.str();
		if (std::find(splits.begin(), splits.end(), s) != splits.end())
		{
			auto str = originalString.substr(splitIndex, i - splitIndex);
			if (str != "") result.insert(str);
			str = originalString.substr(0, i);
			if (str != "") result.insert(str);
			splitIndex = i + 1;
		}
	}
	result.insert(originalString.substr(splitIndex, originalString.length() - splitIndex));
	result.insert(originalString);
	return result;
}
