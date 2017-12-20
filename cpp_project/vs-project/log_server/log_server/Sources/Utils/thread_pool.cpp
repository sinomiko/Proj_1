
#include "logger.h"
#include "thread_pool.h"

//!
//! ctor & dtor
//!

thread_pool::thread_pool(std::size_t nb_threads){
	__MC_LOG(debug, "create thread_pool");

	for (std::size_t i = 0; i < nb_threads; ++i) { m_workers.push_back(std::thread(std::bind(&thread_pool::run, this))); }
}

thread_pool::~thread_pool(void) {
	__MC_LOG(debug, "destroy thread_pool");
	stop();
}

//!
//! worker main loop
//!

void
thread_pool::run(void) {
	__MC_LOG(debug, "start run() worker");

	while (!m_should_stop) {
		task_t task = fetch_task();

		if (task) {
			__MC_LOG(debug, "execute task");
			task();
		}
	}

	__MC_LOG(debug, "stop run() worker");
}

//!
//! stop the thread pool and wait for workers completion
//!

void
thread_pool::stop(void) {
	if (!is_running()) { return; }

	m_should_stop = true;
	m_tasks_condvar.notify_all();

	for (auto& worker : m_workers) { worker.join(); }

	m_workers.clear();

	__MC_LOG(debug, "thread_pool stopped");
}

//!
//! whether the thread_pool is running or not
//!
bool
thread_pool::is_running(void) const {
	return !m_should_stop;
}

//!
//! retrieve a new task
//!

thread_pool::task_t
thread_pool::fetch_task(void) {
	std::unique_lock<std::mutex> lock(m_tasks_mtx);

	__MC_LOG(debug, "waiting to fetch task");

	m_tasks_condvar.wait(lock, [&] { return m_should_stop || !m_tasks.empty(); });

	if (m_tasks.empty()) { return nullptr; }

	task_t task = std::move(m_tasks.front());
	m_tasks.pop();
	return task;
}

//!
//! add tasks to thread pool
//!

void
thread_pool::add_task(const task_t& task) {
	std::lock_guard<std::mutex> lock(m_tasks_mtx);

	__MC_LOG(debug, "add task to thread_pool");

	m_tasks.push(task);
	m_tasks_condvar.notify_all();
}

thread_pool&
thread_pool::operator<<(const task_t& task) {
	add_task(task);

	return *this;
}