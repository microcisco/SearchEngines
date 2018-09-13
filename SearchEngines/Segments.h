#ifndef __Segments_H__
#define __Segments_H__

#include<vector>
#include<set>
#include<array>
#include<string>
#include<algorithm>
#include<sstream>
#include<iostream>

class Segments
{
private:
	std::set<std::string> major(std::string);
	std::set<std::string> minor(std::string);
public:
	Segments();
	~Segments();

	std::set<std::string> exec(std::string);
};

#endif