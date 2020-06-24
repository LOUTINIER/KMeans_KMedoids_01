#pragma once

#include "DataReader.h"
#include <vector>
using std::vector;

class KMedoids
{
public:
	KMedoids(const char* filename, unsigned cluster_cnt);
	~KMedoids();
	void Print() const;
	unsigned int iterators_cnt;
private:
	const DataReader reader;
	const unsigned cluster_cnt;
	vector<unsigned>* cluster;
	unsigned* medoids;
	//double* divide_table;
	void Malloc();
	void Release();
	void InitPoint();
	void Divide();
	const double EuclideanDistance(unsigned a,unsigned b) const;
	const bool CheckInMedoids(unsigned in) const;
};

