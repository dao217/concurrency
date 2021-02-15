#pragma once

#include<exception>
#include<memory>
#include<mutex>
#include<stack>

class empty_stack : std::exception
{
public:
	const char* what() const throw() { return "stack is empty"; }
};

template<typename T>
class threadsafe_stack
{
public:
	threadsafe_stack();
	threadsafe_stack(const threadsafe_stack& other);

	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	void push(T new_value);
	std::shared_ptr<T> pop();
	void pop(T& value);
	bool empty() const;


private:
	std::stack<T> _stack;
	mutable std::mutex _mutex;
};

template<typename T>
inline threadsafe_stack<T>::threadsafe_stack()
{
}

template<typename T>
inline threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other)
{
	std::lock_guard<std::mutex> lock(other._mutex);
	_stack = other._stack;
}

template<typename T>
inline void threadsafe_stack<T>::push(T new_value)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_stack.push(new_value);
}

template<typename T>
inline std::shared_ptr<T> threadsafe_stack<T>::pop()
{
	std::lock_guard<std::mutex> lock(_mutex);

	if (_stack.empty())
	{
		throw empty_stack();

	}

	std::shared_ptr<T> const result(std::make_shared<T>(_stack.top()));
	_stack.pop();

	return result;
}

template<typename T>
inline void threadsafe_stack<T>::pop(T& value)
{
	std::lock_guard<std::mutex> lock(_mutex);
	
	if (_stack.empty())
	{
		throw empty_stack();
	}

	value = _stack.top();
	_stack.pop();
}

template<typename T>
inline bool threadsafe_stack<T>::empty() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _stack.empty();
}
