#include "DataReader.h"
#include <fstream>
#include<cstdio>
#include <iostream>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;
using std::string;

DataReader::DataReader(const char* const filename):
	source(nullptr),
	filepath(filename),
	column(690),
	raw(320)
{
	MallocMemory();
	ReadFromFile();
}

DataReader::~DataReader()
{
	ReleaseMemory();
}


void DataReader::MallocMemory()
{
	source = new double* [raw];
	for (size_t i = 0; i < raw; ++i) {
		source[i] = new double[column];
	}
}

void DataReader::ReleaseMemory()
{
	if (source != nullptr) {
		for (size_t i = 0; i < raw; ++i) {
			delete[]source[i];
		}
	}
	delete[]source;
}

void DataReader::ReadFromFile()
{
	ifstream ifobj(filepath, std::ios_base::in);
	if (ifobj) {
		string line;
		string sunit;
		unsigned int colcnt = 0;
		unsigned int rawcnt = 0;
		while (getline(ifobj, line))
		{
			for (auto& i : line) {
				if (i == ' ') {
					source[rawcnt][colcnt] = atof(sunit.c_str());
					sunit.clear();
					colcnt = (++colcnt) % column;
				}
				else {
					sunit.push_back(i);
				}
			}
			++rawcnt;
		}
	}
	else {
		cout << "打开文件失败!" << endl;
		exit(1);
	}
	ifobj.close();
}
