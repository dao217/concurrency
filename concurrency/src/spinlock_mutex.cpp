#pragma once
#include"spinlock_mutex.h"

spinlock_mutex::spinlock_mutex()
{
}

void spinlock_mutex::lock()
{
	while (_flag.test_and_set(std::memory_order_acquire));
}

void spinlock_mutex::unlock()
{
	_flag.clear(std::memory_order_release);
}

