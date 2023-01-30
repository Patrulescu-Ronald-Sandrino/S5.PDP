//
// Created by kamui on 08.11.2022.
//

#ifndef HOMEWORK3_THREADPOOL_H
#define HOMEWORK3_THREADPOOL_H

#include <thread>
#include <functional>
#include <queue>
#include <condition_variable>

using namespace std;

// https://www.cs.ubbcluj.ro/~rlupsa/edu/pdp/progs/vector_sum_thread_pool.cpp
class ThreadPool {
public:
    explicit ThreadPool(size_t poolSize) {
        m_threads.reserve(poolSize);
        for (int i = 0; i < poolSize; ++i) {
            m_threads.emplace_back([this]() { this->run(); });
        }
    }

    void close() {
        unique_lock<mutex> lock(m_mutex);
        is_shutdown = true;
        m_cond.notify_all();
    }

    ~ThreadPool() {
        close();
        for (auto& thread : m_threads) {
            thread.join();
        }
    }

    void enqueue(const function<void()>& task) {
        unique_lock<mutex> lock(m_mutex);
        m_queue.push(task);
        m_cond.notify_one();
    }

private:
    vector<thread> m_threads;
    queue<function<void()>> m_queue;
    mutex m_mutex;
    condition_variable m_cond;
    bool is_shutdown = false;

    void run() {
        while (true) {
            unique_lock<mutex> lock(m_mutex);
            m_cond.wait(lock, [this] { return !m_queue.empty() || is_shutdown; });
            if (is_shutdown) {
                break;
            }
            auto task = m_queue.front();
            m_queue.pop();
            lock.unlock();
            task();
        }
    }
};


#endif //HOMEWORK3_THREADPOOL_H
