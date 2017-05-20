/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: safe_queue.hh
 * @author: leaveschen
 * @date: 2017-05-20, 20:42:59
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_SAFE_QUEUE_HH__
#define __RPC_LITE_SAFE_QUEUE_HH__

/****** Include Library ******/

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

/****** Class or Function declare ******/

namespace rpclite {

template<class T>
class SafeQueue {
private:
	// members
	std::atomic_bool _valid;
	std::queue<T> _queue;
	std::mutex _mtx;
	std::condition_variable _cond;

public:
	// constructor and destructor
	SafeQueue() : _valid(true) {}
	SafeQueue(SafeQueue const&) = delete;
	SafeQueue& operator=(SafeQueue const&) = delete;
	~SafeQueue() {
		std::lock_guard<std::mutex> lk(_mtx);
		_valid = false;
		_cond.notify_all();
	}

	// interface
	void push(T const& v) {
		std::lock_guard<std::mutex> lk(_mtx);
		_queue.push(v);
		_cond.notify_one();
	}

	inline bool wait_pop(T& v) {
		std::unique_lock<std::mutex> lk(_mtx);
		_cond.wait(lk, [&](){ return !_queue.empty() || !_valid; });
		if (!_valid) { return false; }
		v = std::move(_queue.front());
		_queue.pop();
		return true;
	}

	inline bool try_pop(T& v) {
		std::lock_guard<std::mutex> lk(_mtx);
		if (_queue.empty()) {
			return false;
		} else {
			v = std::move(_queue.front());
			_queue.pop();
		}
		return true;
	}
};

} // rpclite

#endif


