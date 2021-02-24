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
	std::vector<int> v;
	std::list<int> l;

	v.reserve(10000);
	for (int i = 0; i < 10000; i++)
	{
		v.push_back(i);
	}
	std::random_shuffle(v.begin(), v.end());
	std::copy(v.begin(), v.end(), std::back_inserter(l));

	execution_timer<> t;
	t.start();
	parallel_quick_sort(l);
	std::cout << t.stop();

	for (auto it : l)
	{
		std::cout << it;
	}
	
	

	return 0;
}