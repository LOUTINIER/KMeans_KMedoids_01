#pragma once
#include "DataReader.h"

#include <vector>
using std::vector;

struct Cluster
{
	vector<unsigned int> clusters;
	double* mean;

	Cluster(unsigned int size) :
		mean(new double[size]){

	}

	~Cluster() {
		if (mean != nullptr) {
			delete[]mean;
		}
	}
};

class KMeans
{
public:
	KMeans(const char* filename,unsigned int cluster_cnt);
	~KMeans();
	void Print();
	unsigned int iterator_cnt;
private:
	Cluster** cluster;
	unsigned int* divide_table;
	const DataReader reader;
	const unsigned int cluster_cnt;
	void RandomPoint() const;
	void MallocMemory();
	void ReleaseMemory();
	double EuclideanDistance(double*& a, double*& b) const;
	void Devide();
	
};

