#include "KMedoids.h"
#include <algorithm>

KMedoids::KMedoids(const char *filename,unsigned clu_c):
	reader(DataReader(filename)),
	cluster_cnt(clu_c),
	iterators_cnt(0),
	//divide_table(nullptr),
	cluster(nullptr),
	medoids(nullptr)
{
	Malloc();
	InitPoint();
	Divide();

}

KMedoids::~KMedoids()
{
	Release();
}

void KMedoids::Malloc()
{
	/*if (divide_table == nullptr) {
		divide_table = new double[reader.raw];
	}*/
	if (medoids == nullptr) {
		medoids = new unsigned[cluster_cnt];
	}
	if (cluster == nullptr) {
		cluster = new vector<unsigned>[cluster_cnt];
	}
}

void KMedoids::Release()
{
	/*if (divide_table != nullptr) {
		delete[]divide_table;
		divide_table = nullptr;
	}*/
	if (medoids != nullptr) {
		delete[] medoids;
		medoids = nullptr;
	}
	if (cluster != nullptr) {
		delete[]cluster;
		cluster = nullptr;
	}
}

void KMedoids::InitPoint()
{
	for (size_t i = 0; i < cluster_cnt; ++i) {
		unsigned selectIndex = reader.raw / cluster_cnt * i;
		cluster[i].push_back(selectIndex);
		medoids[i] = selectIndex;
		//divide_table[selectIndex] = i;
	}
	// 初始化分
	for (size_t i = 0; i < reader.raw; ++i) {
		//滤掉medoids
		if (!CheckInMedoids(i)) {
			unsigned int best_clus = UINT_MAX;
			double min_dist = DBL_MAX;
			for (size_t j = 0; j < cluster_cnt; ++j) {
				double dist = EuclideanDistance(i, medoids[j]);
				if (min_dist > dist) {
					min_dist = dist;
					best_clus = j;
				}
			}
			cluster[best_clus].push_back(i);
			//divide_table[i] = best_clus;
		}
	}
}

void KMedoids::Divide()
{
	while (true) {
		printf("Iteratoring For The %u Time......\n", iterators_cnt);
		bool change = false;
		//计算新的medoids
		for (size_t i = 0; i < cluster_cnt; ++i) {
			double least_cost = DBL_MAX;
			unsigned int index = UINT_MAX;
			for (size_t j = 0; j < cluster[i].size(); ++j) {
				double tmp_cost = 0.0;
				for (size_t k = 0; k < cluster[i].size(); ++k) {
					tmp_cost += EuclideanDistance(cluster[i][j], cluster[i][k]);
				}
				if (least_cost > tmp_cost) {
					least_cost = tmp_cost;
					index = j;
				}
			}
			if (cluster[i][index] != medoids[i]) {
				medoids[i] = cluster[i][index];
				change = true;
			}
		}
		// 划分
		for (size_t i = 0; i < cluster_cnt; ++i) {
			cluster[i].clear();
			cluster[i].push_back(medoids[i]);
		}
		for (size_t i = 0; i < reader.raw; ++i) {
			// 滤掉medoids
			if (!CheckInMedoids(i)) {
				unsigned int best_clus = UINT_MAX;
				double min_dist = DBL_MAX;
				for (size_t j = 0; j < cluster_cnt; ++j) {
					double dist = EuclideanDistance(i, medoids[j]);
					if (min_dist > dist) {
						min_dist = dist;
						best_clus = j;
					}
				}
				cluster[best_clus].push_back(i);
				//divide_table[i] = best_clus;
			}
		}
		if (!change) { 
			break; 
		}
		else {
			++iterators_cnt;
		}
	}
}

const double KMedoids::EuclideanDistance(unsigned a,unsigned b) const
{
	double dist = 0.0;
	for (size_t i = 0; i < reader.column; ++i) {
		dist += (reader[a][i] - reader[b][i]) * (reader[a][i] - reader[b][i]);
	}
	return sqrt(dist);
}

const bool KMedoids::CheckInMedoids(unsigned in) const
{
	for (size_t i = 0; i < cluster_cnt; ++i) {
		if (medoids[i] == in)return true;
	}
	return false;
}

void KMedoids::Print() const
{
	printf("Iterator: %uTimes\n\n", iterators_cnt);
	for (size_t i = 0; i < cluster_cnt; ++i) {
		printf("Cluster%u:\n", i);
		// sort not neccessary
		sort(cluster[i].begin(), cluster[i].end());
		for (auto& val : cluster[i]) {
			printf("%u ", val);
		}
		printf("\n\n");
	}
}
