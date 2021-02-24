#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <random>

#include"sorts.h"


int main()
{
	std::vector<int> temp;
	std::list<int> data;

	temp.reserve(10000);
	for (int i = 0; i < 10000; i++)
	{
		temp.push_back(i);
	}

	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(temp.begin(), temp.end(), generator);
	std::copy(temp.begin(), temp.end(), std::back_inserter(data));



	
	data = sequential_quick_sort(data);

	for (auto it : data)
	{
		std::cout << it << std::endl;
	}


	return 0;
}