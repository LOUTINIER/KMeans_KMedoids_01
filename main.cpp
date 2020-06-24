#include "DataReader.h"
#include "KMeans.h"
#include "KMedoids.h"
#include <iostream>
#include <ctime>
using std::cout;

int main()
{
	const constexpr char* file = R"(C:\Users\13614\OneDrive\4\数据挖掘\实验\EX3\data.txt)";
	clock_t start, end;
	start = clock();
	KMeans kmeans = KMeans(file, 5);
	end = clock();
	printf("spent:%lf\n", 1.0* (end - start) / CLOCKS_PER_SEC );
	kmeans.Print();

	start = clock();
	KMedoids kmedoids = KMedoids(file, 5);
	end = clock();
	printf("spent:%lf\n", 1.0 * (end - start) / CLOCKS_PER_SEC);
	kmedoids.Print();
	return 0;
}