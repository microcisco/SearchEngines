#ifndef __Splunk_H__
#define __Splunk_H__

#include<string>
#include<vector>
#include<set>
#include<map>

#include"Bloomfilter.h"
#include"Segments.h"
class Splunk
{
private:
	std::vector<std::string> container;
	std::map<std::string, std::set<int>> searchTable;

	Bloomfilter bloomfilter = 1024;
	Segments segments;
public:
	Splunk();
	~Splunk();

	void addDocument(std::string);
	std::set<std::string> findDocument(std::string);
};

#endif