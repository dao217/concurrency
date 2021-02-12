#include<iostream>
#include<vector>
#include"parallel_accumulate.h"

int main()
{
	std::vector<int> data(100);

	for (int i = 0; i < 100; i++)
	{
		data[i] = i;
	}

	std::cout << "STL accumulate ger result "
		<< std::accumulate(data.begin(), data.end(), 0) << std::endl;

	std::cout << "Our paralel accumulate get result " 
		<< parallel_accumulate(data.begin(), data.end(), 0) << std::endl;

	return 0;
}