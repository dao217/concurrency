#pragma once
#include<chrono>
#include<exception>
#include<string>

class execution_timer_error : std::exception
{
public:
	execution_timer_error(std::string msg = "timer not starting")
		: _msg(msg)
	{}
	const char* what() const throw() { return _msg.c_str(); }
	
private:
	std::string _msg;
};


template<typename Resolution  = std::chrono::milliseconds>
class execution_timer
{
public:
	using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>;
	using TimePoint = Clock::time_point;

public:
	execution_timer(bool start = true)
	{
		if (start)
		{
			_start = Clock::now();
		}
	}
	~execution_timer()
	{
	}

	void start()
	{
		_start = Clock::now();
	}

	double stop()
	{
		if (_start == _stop)
		{
			throw new execution_timer_error();
		}
		_stop = Clock::now();
		auto result = _stop - _start;
		_start = _stop;
		return std::chrono::duration_cast<Resolution>(result).count();
	}

private:
	TimePoint _start;
	TimePoint _stop;
};