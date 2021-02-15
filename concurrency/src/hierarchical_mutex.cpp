#include"hierarchical_mutex.h"
#include<exception>

hierarhical_mutex::hierarhical_mutex(unsigned long value) :
	hierarchy_value(value),
	previous_hierarchy_value(0)
{
}

void hierarhical_mutex::lock()
{
	check_for_hierarchy_violation();
	internal_mutex.lock();
	update_hierarchy_value();
}

void hierarhical_mutex::unlock()
{
	this_theead_hierarchy_value = previous_hierarchy_value;
	internal_mutex.unlock();
}

bool hierarhical_mutex::try_lock()
{
	check_for_hierarchy_violation();
	if (!internal_mutex.try_lock())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void hierarhical_mutex::check_for_hierarchy_violation()
{
	if (this_theead_hierarchy_value <= hierarchy_value)
	{
		throw std::logic_error("mutex hierary violated");
	}
}

void hierarhical_mutex::update_hierarchy_value()
{
	previous_hierarchy_value = this_theead_hierarchy_value;
	this_theead_hierarchy_value = hierarchy_value;
}

thread_local unsigned long hierarhical_mutex::this_theead_hierarchy_value(ULONG_MAX);
