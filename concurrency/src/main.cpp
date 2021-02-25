#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <random>
#include<chrono>
#include<algorithm>
#include<atomic>
#include<thread>
#include"sorts.h"
#include"execution_timer.h"
#include"parallel_accumulate.h"
#include"spinlock_mutex.h"


void test1()
{
	while (true)
	{
		std::cout << "1" << std::endl;
		std::cout << "1" << std::endl;
		std::cout << "1" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}

void test2()
{
	while (true)
	{
		std::cout << "2" << std::endl;
		std::cout << "2" << std::endl;
		std::cout << "2" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}


int main()
{
	std::thread t1(test1);
	std::thread t2(test2);
	t1.join();
	t2.join();


	return 0;
}