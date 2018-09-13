#ifndef __Bloomfilter_H__
#define __Bloomfilter_H__

#include<array>
#include<string>
#include<functional>

class Bloomfilter
{
private:
	int* container;
	int containerLength = 0;

	int calcHash(std::string);

public:
	Bloomfilter(int);
	~Bloomfilter();

	void addElement(std::string);
	bool existElement(std::string);
};

#endif

