#pragma once
#include <memory>
using std::shared_ptr;

class DataReader
{
public:
	DataReader(const char* const filename);
	~DataReader();
	double*& operator[](unsigned int r) const { return source[r]; }
	unsigned int column;
	unsigned int raw;
	const char* const filepath;
private:
	void MallocMemory();
	void ReleaseMemory();
	void ReadFromFile();
	double** source;
	
};

