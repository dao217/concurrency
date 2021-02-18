#include <iostream>
#include <queue>
#include <thread>
#include<condition_variable>
#include <chrono>


std::mutex mut;
std::queue<std::string> data;
std::condition_variable data_cond;

void cin_data()
{
	while (true)
	{
		std::string temp;
		std::lock_guard<std::mutex> lk(mut);
		std::cout << "get string: ";
		std::cin >> temp;
		data.push(temp);
		data_cond.notify_one();
	}
}

void cout_data()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [] {return !data.empty(); });
		while (!data.empty())
		{
			std::string temp = data.front();
			data.pop();
			if (temp == "end")
			{
				std::cout << "goobye! (u tipe end)";
				break;
			}
			else
			{
				std::cout << "your string " << temp << " is correct" << std::endl;
			}
		}
		lk.unlock();
		std::this_thread::sleep_for(std::chrono::seconds(2));
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