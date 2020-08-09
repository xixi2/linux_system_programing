#ifndef THREADPOOL_THREAD_POOL_H
#define THREADPOOL_THREAD_POOL_H

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>
#include <chrono>
#include <map>
#include <map>
#include <sstream>

using namespace std;
typedef function<int()> Task;

int print(int task_id) {
    // this_thread::get_id()获取当前线程ID
    cout << "[-] task " << task_id << " working in thread " << this_thread::get_id() << endl;
    return task_id;
}

class ThreadPool {
private:
    int thread_num;
    int max_task_num;
    bool is_working;
    condition_variable cond{};
    vector<thread> threads{};
    queue<Task> tasks;
    mutex task_mutex{};
    map<int, string> count;

public:
    void work() {
        while (this->is_working) {
            ostringstream ss; // 创建一个字符串流
            ss << this_thread::get_id();    // 把线程的id放入到字符串流中
            string cur_thread_id = ss.str();

            // 这里为什么一定要用unique_lock，如果不用unique_lock？
            unique_lock<mutex> lk(this->task_mutex);
            while (this->is_working and this->tasks.empty()) {
                this->cond.wait(lk);        // 当前线程被阻塞，等待任务
            }
            if (this->tasks.empty()) {
                continue;
            }
            Task cur_task;
            cur_task = this->tasks.front();
            this->tasks.pop();
            int task_id = cur_task();
            this->count[task_id] = cur_thread_id;
            this->cond.notify_one();            // 唤醒其他被阻塞的线程
        }
    }

    ThreadPool(int thread_num, int max_task_num) {
        this->thread_num = thread_num;  // 线程数量
        this->max_task_num = max_task_num; // 任务数量
        this->is_working = true;
        for (int i = 0; i < thread_num; i++) {
            // thread(&ThreadPool::work, this)表示，创建一个线程，线程启动函数为ThreadPool::work，参数为this指针
            this->threads.push_back(thread(&ThreadPool::work, this));
        }
        cout << "[✔] create ThreadPool finished!" << endl;
    }

    ~ThreadPool() {
        this->is_working = false;
        this->cond.notify_all();
        cout << "------------delete pool--------------" << endl;
        for (auto &t:this->threads) {
            if (t.joinable()) {
                cout << "[-] join thread " << t.get_id();
                ostringstream ss;
                ss << t.get_id();
                string cur_thread_id = ss.str();

                // 统计每个子线程完成的任务数量
                int task_num = 0;
                for (auto &item:count) {    // 从count取出一个键值对
                    if (item.second == cur_thread_id) {
                        task_num++;
                    }
                }
                cout << ", finished task_num =" << task_num << endl;
                t.join();   // 阻塞等待子线程t结束
            }
        }
        this->threads.clear();
        cout << "[✔] delete ThreadPool finished!" << endl;
    }

    void add_task(const Task &t) {
        if (this->is_working) {
            unique_lock<mutex> lk(this->task_mutex);
            while (tasks.size() >= this->max_task_num) {
                cout << "task queue is full, producer is going to sleep for a while!" << endl;
                // 阻塞当前线程，直到task.size() < this->max_task_num
                this->cond.wait(lk);
            }
            this->tasks.push(t);

            // 唤醒一个阻塞的线程，主线程负责往线程池中加入任务，所以，在主线程中调用notify_one被唤醒的只能是工作线程
            this->cond.notify_one();
        }
    }
};


#endif //THREADPOOL_THREAD_POOL_H
