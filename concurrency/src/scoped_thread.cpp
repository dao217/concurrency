#include"scoped_thread.h"
#include<stdexcept>


scoped_thread::scoped_thread(std::thread thread) :
	_thread(std::move(thread))
{
	if (!_thread.joinable())
	{
		throw std::logic_error("No thread");
	}
}

scoped_thread::~scoped_thread()
{
	_thread.join();
}
