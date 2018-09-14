#include "Bloomfilter.h"


int Bloomfilter::calcHash(std::string value)
{
	std::hash<std::string> hash_fn;
	return hash_fn(value);
}

Bloomfilter::Bloomfilter(int length)
{
	this->container = new bool[length] {0};
	this->containerLength = length;

}

Bloomfilter::~Bloomfilter()
{
	delete[] this->container;
}

void Bloomfilter::addElement(std::string str)
{
	this->container[this->calcHash(str) % this->containerLength] = 1;
}

bool Bloomfilter::existElement(std::string str)
{
	return this->container[this->calcHash(str) % this->containerLength] == 1;
}
