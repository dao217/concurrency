#include <iostream>
#include <thread>
#include<condition_variable>
#include <chrono>

#include"threadsafe_queue.h"

std::mutex mut;
threadsafe_queue<std::string> data;

void cin_data()
{
	while (true)
	{
		std::lock_guard<std::mutex> lk(mut);
		std::string temp;
		std::cout << "get string: ";
		std::cin >> temp;
		data.push(temp);
	}
}

void cout_data()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mut);
		std::string temp;

		while (data.try_pop(temp))
		{
			if (temp == "end")
			{
				std::cout << "goobye! (u tipe end)";
			}
			else
			{
				std::cout << "your string " << temp << " is correct" << std::endl;
			}
		}
		lk.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}



int main()
{
	std::thread cin_data_thread(cin_data);
	std::thread coud_data_thread(cout_data);
	cin_data_thread.join();
	coud_data_thread.join();
	return 0;
}