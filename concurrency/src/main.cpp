#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <random>
#include<chrono>
#include<algorithm>

#include"sorts.h"
#include"execution_timer.h"
#include"parallel_accumulate.h"

#define SIZE 1000000
int main()
{
	std::vector<int> test_vector;
	test_vector.reserve(SIZE);

	for (unsigned i = 0; i < SIZE; i++)
	{
		test_vector.push_back(i);
	}
	execution_timer<std::chrono::milliseconds> timer;


	timer.start();
	int result_parallel = parallel_accumulate(test_vector.begin(), test_vector.end(), 0);
	double stop_parallel = timer.stop_d();
	std::cout << "parallel accumulate result is " << result_parallel << std::endl;
	std::cout << "parallel accumulate time is " << stop_parallel << std::endl;

	std::cout << "======================================" << std::endl;
	std::cout << "======================================" << std::endl;
	std::cout << "======================================" << std::endl;

	timer.start();
	int result_std = std::accumulate(test_vector.begin(), test_vector.end(), 0);
	double stop_std = timer.stop_d();
	std::cout << "std accumulate result is " << result_std << std::endl;
	std::cout << "std accumulate time is " << stop_std << std::endl;


	return 0;
}