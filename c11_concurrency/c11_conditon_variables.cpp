//
// Created by xixi2 on 2020/7/4.
// 使用条件变量

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;  // 全局互斥锁
condition_variable cv; // 全局条件变量
bool ready = false; // 全局标志位

void do_print_id(int id) {
    unique_lock<mutex> lck(mtx);
    while (!ready) {    // 如果标志位不为true，则等待...
        cout << "[thread " << id << " is waiting" << endl;
        cv.wait(lck);        //当前线程被阻塞
    }
    // 当全局标志位变为true之后，线程被唤醒，继续往下执行，打印线程编号ID
    cout << "[thread " << id << "]" << endl;
}

void go() {
    unique_lock<mutex> lck(mtx);
    ready = true;   // 设置全局标志位为true
    cv.notify_all();    // 唤醒所有线程
}

int main() {
    int threads_num = 5;
    thread threads[threads_num];
    for (int i = 0; i < threads_num; ++i) {
//        threads[i] = thread(do_print_id, i);
        threads[i] = std::thread(do_print_id, i);
    }
    this_thread::sleep_for(std::chrono::milliseconds(10));
    cout << threads_num << " threads ready to race..." << endl;
    go();
    for (auto &th: threads) {
        th.join();      // 主线程阻塞等待子线程
    }
    return 0;
}