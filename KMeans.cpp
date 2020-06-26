#include "KMeans.h"

#include <random>
#include <cmath>

using dre = std::default_random_engine;
using uidui = std::uniform_int_distribution<unsigned int>;

KMeans::KMeans(const char* filename,unsigned int cluster_c):
	reader(DataReader(filename)),
	cluster_cnt(cluster_c),
	iterator_cnt(0),
	cluster(nullptr),
	divide_table(nullptr)
{
	
	MallocMemory();
	RandomPoint();
	Devide();
}

KMeans::~KMeans()
{
	ReleaseMemory();
}

void KMeans::RandomPoint() const
{
	// 设置好中心点，并将其划分到簇中
	// random
	// dre e(80);
	// uidui u(0, reader.raw - 1);
	for (size_t i = 0; i < cluster_cnt; ++i) {
		// random
		// unsigned int randomui = u(e);
		// no-random
		unsigned randomui = reader.raw/cluster_cnt * i;
		for (size_t j = 0; j < reader.column; ++j) {
			cluster[i]->mean[j] = reader[randomui][j];
		}
		cluster[i]->clusters.push_back(randomui);
		divide_table[randomui] = i;
	}
	//初次划分
	for (size_t i = 0; i < reader.raw; ++i) {
		// 记录最优划分
		unsigned int best_cluster = UINT_MAX;
		double min_dist = DBL_MAX;
		for (size_t j = 0; j < cluster_cnt; ++j) {
			double dist = EuclideanDistance(reader[i], cluster[j]->mean);
			if (min_dist > dist) {
				best_cluster = j;
				min_dist = dist;
			}
		}
		if (cluster[best_cluster]->clusters[0] != i) {
			cluster[best_cluster]->clusters.push_back(i);
			divide_table[i] = best_cluster;
		}
	}
}

void KMeans::MallocMemory()
{
	if (cluster == nullptr) {
		cluster = new Cluster * [cluster_cnt];
		for (size_t i = 0; i < cluster_cnt; ++i) {
			cluster[i] = new Cluster(reader.column);
		}
	}
	if (divide_table == nullptr) {
		divide_table = new unsigned int[reader.raw];
	}
}

void KMeans::ReleaseMemory()
{
	if (cluster != nullptr) {
		for (size_t i = 0; i < cluster_cnt; ++i) {
			delete cluster[i];
			cluster[i] = nullptr;
		}
		delete[]cluster;
		cluster = nullptr;
	}
	if (divide_table != nullptr){
		delete[]divide_table;
		divide_table = nullptr;
	}
}


double KMeans::EuclideanDistance(double *&a,double *&b) const
{
	double aver = 0.0;
	for (size_t i = 0; i < reader.column; ++i) {
		aver += (a[i] - b[i]) * (a[i] - b[i]);
	} 
	return sqrt(aver);
}

void KMeans::Devide()
{
	while (true) {
		// 求均值
		printf("Iteratoring For The %u Time......\n", iterator_cnt + 1);
		bool changed = false;
		for (size_t i = 0; i < cluster_cnt; ++i) {
			unsigned int size = cluster[i]->clusters.size();
			auto tmp_means = new double[reader.column];
			memset(tmp_means, 0, sizeof(double) * reader.column);
			for (auto& index : cluster[i]->clusters) {
				for (size_t k = 0; k < reader.column; ++k) {
					tmp_means[k] += reader[index][k] / size;
				}
			}
			for (size_t j = 0; j < reader.column; ++j) {
				if (tmp_means[j] != cluster[i]->mean[j]) {
					changed = true;
					cluster[i]->mean[j] = tmp_means[j];
				}
			}
			delete[] tmp_means;
		}
		if (!changed) {
			break;
		}
		else {
			++iterator_cnt;
		}
		for (size_t i = 0; i < cluster_cnt; ++i) {
			cluster[i]->clusters.clear();
		}
		// 根据均值再划分 dividetable表不变的话直接break
		for (size_t i = 0; i < reader.raw; ++i) {
			unsigned int best_cluster = UINT_MAX;
			double min_dist = DBL_MAX;
			for (size_t j = 0; j < cluster_cnt; ++j) {
				double dist = EuclideanDistance(reader[i], cluster[j]->mean);
				if (min_dist > dist) {
					best_cluster = j;
					min_dist = dist;
				}
			}
			cluster[best_cluster]->clusters.push_back(i);
			divide_table[i] = best_cluster;
			//if (best_cluster != divide_table[i]) {
			//	//转移pointer到合适的簇
			//	for (size_t k = 0; k < cluster[divide_table[i]]->clusters.size(); ++k) {
			//		if (cluster[divide_table[i]]->clusters[k] == i) {
			//			cluster[divide_table[i]]->clusters.erase(cluster[divide_table[i]]->clusters.begin() + k);
			//			break;
			//		}
			//	}
			//	cluster[best_cluster]->clusters.push_back(i);
			//	divide_table[i] = best_cluster;
			//}
		}
	}
}

void KMeans::Print()
{
	printf("Iterator: %uTimes\n", iterator_cnt);
	for (size_t i = 0; i < cluster_cnt; ++i) {
		// sort not neccessary
		sort(cluster[i]->clusters.begin(), cluster[i]->clusters.end());
		printf("Cluster%u:", i);
		for (auto &j : cluster[i]->clusters) {
			printf("%u ",j);
		}
		printf("\n");
	}
}