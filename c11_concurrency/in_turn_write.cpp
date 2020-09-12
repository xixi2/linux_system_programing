//
// Created by xixi2 on 2020/7/5.
// 两个子线程交替打印1和2,本程序尚无法确定是否可用


#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

mutex mtx;
condition_variable cv1, cv2;
bool printFlag = true;

void func1() {
    unique_lock <mutex> lock(mtx);
    if (!printFlag) {
        cv1.wait(lock);
    }
    printFlag = !printFlag;
    cout << "1";
    cv2.notify_one();
}

void func2() {
    unique_lock <mutex> lock(mtx);
    if (printFlag) {
        cv2.wait(lock);
    }
    printFlag = !printFlag;
    cout << "2";
    cv1.notify_one();
}

int main() {
    thread t1(func1);
    thread t2(func2);
    t1.join();
    t2.join();
    return 0;
}