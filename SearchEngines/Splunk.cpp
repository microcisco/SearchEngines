#include "Splunk.h"


Splunk::Splunk()
{
}

Splunk::~Splunk()
{
}

void Splunk::addDocument(std::string dataStr)
{
	bloomfilter.addElement(dataStr);
	int index = this->container.size();
	this->container.push_back(dataStr);
	for (auto s: this->segments.exec(dataStr))
	{
		bloomfilter.addElement(s);


		this->searchTable[s].insert(index);
	}

}

std::set<std::string> Splunk::findDocument(std::string dataStr)
{
	std::set<std::string> result;
	if (!this->bloomfilter.existElement(dataStr)) return result;
	if (this->searchTable[dataStr].size() == 0) return result;

	for (auto index: searchTable[dataStr])
	{
		result.insert(this->container[index]);
	}
	return result;
}
