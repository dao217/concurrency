#include<iostream>
#include<vector>
#include<string>
#include"parallel_accumulate.h"
#include"threadsafe_stack.h"
#include"scoped_thread.h"


threadsafe_stack<std::string> s;

void test1()
{
	for (int i = 0; i < 10; i++)
	{
		s.push(std::string("new string"));
	}
}

void test2()
{
	for (int i = 0; i < 10; i++)
	{
		s.push(std::string("new other string"));
	}
}

void test3()
{
	for (int i = 0; i < 10; i++)
	{
		if (!s.empty())
		{
			s.pop();
		}
	}
}

int main()
{
	/*std::vector<int> data(100);

	for (int i = 0; i < 100; i++)
	{
		data[i] = i;
	}

	std::cout << "STL accumulate ger result "
		<< std::accumulate(data.begin(), data.end(), 0) << std::endl;

	std::cout << "Our paralel accumulate get result "
		<< parallel_accumulate(data.begin(), data.end(), 0) << std::endl;*/

	std::thread t1(test1);
	std::thread t2(test2);
	std::thread t3(test3);
	t1.join();
	t2.join();
	t3.join();

	

	while (!s.empty())
	{
		std::cout << *s.pop() << std::endl;
	}

	return 0;
}