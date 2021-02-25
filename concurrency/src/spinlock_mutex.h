#pragma once

#include<atomic>

class spinlock_mutex
{
public:
	spinlock_mutex();
	void lock();
	void unlock();
private:
	std::atomic_flag _flag = ATOMIC_FLAG_INIT;
};