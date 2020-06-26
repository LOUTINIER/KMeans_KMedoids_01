#include "DataReader.h"
#include "KMeans.h"
#include "KMedoids.h"
#include <iostream>
#include <ctime>
using std::cout;

int main()
{
	const constexpr char *file = R"(data.txt)";
	const unsigned k[3] = {5, 10, 20};
	clock_t start, end;

	for (auto &i : k)
	{
		printf("簇个数为%u时：\n", i);
		start = clock();
		KMeans kmeans = KMeans(file, i);
		end = clock();
		printf("Kmeans算法花费:%lfs\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
		kmeans.Print();
	}
	for (auto &i : k)
	{
		printf("簇个数为%u时：\n", i);
		start = clock();
		KMedoids kmedoids = KMedoids(file, i);
		end = clock();
		printf("Kmedoids算法花费:%lfs\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
		kmedoids.Print();
	}
	return 0;
}