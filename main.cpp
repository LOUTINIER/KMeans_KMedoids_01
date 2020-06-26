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
		printf("�ظ���Ϊ%uʱ��\n", i);
		start = clock();
		KMeans kmeans = KMeans(file, i);
		end = clock();
		printf("Kmeans�㷨����:%lfs\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
		kmeans.Print();
	}
	for (auto &i : k)
	{
		printf("�ظ���Ϊ%uʱ��\n", i);
		start = clock();
		KMedoids kmedoids = KMedoids(file, i);
		end = clock();
		printf("Kmedoids�㷨����:%lfs\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
		kmedoids.Print();
	}
	return 0;
}