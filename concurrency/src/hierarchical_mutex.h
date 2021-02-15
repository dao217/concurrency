#pragma once
#include<mutex>

class hierarhical_mutex
{
	explicit hierarhical_mutex(unsigned long value);
	void lock();
	void unlock();
	bool try_lock();


private:
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;
	unsigned previous_hierarchy_value;
	static thread_local unsigned long this_theead_hierarchy_value;

	void check_for_hierarchy_violation();
	void update_hierarchy_value();
};