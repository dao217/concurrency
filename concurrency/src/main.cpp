#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <random>
#include<chrono>

#include"sorts.h"
#include"execution_timer.h"
int main()
{
	std::vector<int> v1, v2;
	std::list<int> l1, l2;

	v1.reserve(10);
	v2.reserve(10);
	for (int i = 0; i < 1000; i++)
	{
		v1.push_back(i);
		v2.push_back(i);
	}
	std::random_shuffle(v1.begin(), v1.end());
	std::random_shuffle(v2.begin(), v2.end());
	std::copy(v1.begin(), v1.end(), std::back_inserter(l1));
	std::copy(v1.begin(), v1.end(), std::back_inserter(l2));



	execution_timer<std::chrono::microseconds> t;
	
	t.start();
	l1 = parallel_quick_sort(l1);
	std::cout << "parallel time is " << t.stop() << std::endl;

	t.start();
	l1 = sequential_quick_sort(l2);
	std::cout << "sequantial time is " << t.stop() << std::endl;

	

	return 0;
}