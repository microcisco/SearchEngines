#include<iostream>

#include"Splunk.h"

int main(int argc, char** argv)
{
	Splunk splunk;
	splunk.addDocument("src_ip = 192.168.1.2");
	splunk.addDocument("src_ip = 192.168.2.6");
	splunk.addDocument("dst_ip = 192.168.8.8");

	for (auto s: splunk.findDocument("ip"))
	{
		std::cout << s <<'\n';
	}

	system("pause");
}