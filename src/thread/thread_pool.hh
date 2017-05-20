/***************************************************************************
 *
 * qwerty
 *
 **************************************************************************/

/**
 * @nortrom
 * @file: thread_pool.hh
 * @author: leaveschen
 * @date: 2017-05-20, 20:23:19
 * @version 1.0
 * @brief:
 **/

#ifndef __RPC_LITE_THREAD_POOL_HH__
#define __RPC_LITE_THREAD_POOL_HH__

/****** Include Library ******/

#include <vector>
#include <thread>
#include <future>
#include <functional>
#include "src/thread/safe_queue.hh"

/****** Class or Function declear ******/

namespace rpclite {

template<size_t cnt>
class ThreadPool {
private:
	// members
	std::atomic_bool _done;
	std::mutex _mtx;
	std::vector<std::thread> _threads;
	SafeQueue<std::function<void()>> _task_queue;

	// thread function
	void _work() {
		for (;;) {
			std::function<void()> task;
			if (!_task_queue.wait_pop(task)) {
				continue;
			}
			task();
		}
	}

public:
	// constructor & destructor
	ThreadPool() {
		for (size_t i = 0; i < cnt; ++i) {
			_threads.emplace_back(std::thread(&ThreadPool::_work, this));
		}
	}
	ThreadPool(ThreadPool const&) = delete;
	ThreadPool& operator=(ThreadPool const&) = delete;
	~ThreadPool() { for (auto& t : _threads) { t.join(); }}

	template<class F, class... Args>
	void submit(F&& f, Args&&... args) {
		auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		_task_queue.push(task);
	}
	
};

} // rpclite

#endif


