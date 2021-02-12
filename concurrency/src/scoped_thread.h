#pragma once
#include<thread>

class scoped_thread
{
public:
	explicit scoped_thread(std::thread thread);
	~scoped_thread();
	scoped_thread(const scoped_thread&) = delete;
	scoped_thread& operator=(const scoped_thread&) = delete;

private:
	std::thread _thread;
};