#include<condition_variable>
#include<mutex>
#include<memory>
#include<queue>

template<typename T>
class threadsafe_queue
{
public:
	threadsafe_queue();
	threadsafe_queue(const threadsafe_queue& other);

public:
	void push(T new_value);
	void wait_and_pop(T& value);
	std::shared_ptr<T> wait_and_pop();
	bool try_pop(T& value);
	std::shared_ptr<T> try_pop();
	bool empty() const;

private:
	mutable std::mutex _mutex;
	std::queue<T> _queue;
	std::condition_variable _cond;

};

template<typename T>
inline threadsafe_queue<T>::threadsafe_queue()
{
}

template<typename T>
inline threadsafe_queue<T>::threadsafe_queue(const threadsafe_queue& other)
{
	std::lock_guard<std::mutex> lk(other._mutex);
	_queue = other._queue;
}

template<typename T>
inline void threadsafe_queue<T>::push(T new_value)
{
	std::lock_guard<std::mutex> lk(_mutex);
	_queue.push(new_value);
	_cond.notify_one();
}

template<typename T>
inline void threadsafe_queue<T>::wait_and_pop(T& value)
{
	std::unique_lock<std::mutex> lk(_mutex);
	_cond.wait(lk, [this] {return !_queue.empty(); });
	value = _queue.front();
	_queue.pop();
}

template<typename T>
inline std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop()
{
	std::unique_lock<std::mutex> lk(_mutex);
	_cond.wait(lk, [this] {return !_queue.empty(); });
	std::shared_ptr<T> result (std::make_shared<T>(_queue.front()));
	_queue.pop();
	return result;
}

template<typename T>
inline bool threadsafe_queue<T>::try_pop(T& value)
{
	std::lock_guard<std::mutex> lk(_mutex);
	if (_queue.empty())
	{
		return false;
	}
	value = _queue.front();
	_queue.pop();
	return true;
}

template<typename T>
inline std::shared_ptr<T> threadsafe_queue<T>::try_pop()
{
	std::lock_guard<std::mutex> lk(_mutex);
	if (_queue.empty())
	{
		return false;
	}
	std::shared_ptr<T> result(std::make_shared<T>(_queue.front()));
	_queue.pop();
	return result;
}

template<typename T>
inline bool threadsafe_queue<T>::empty() const
{
	std::lock_guard<std::mutex> lk(_mutex);
	return _queue.empty();
}
