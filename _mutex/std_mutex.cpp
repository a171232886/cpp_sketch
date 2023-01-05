#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <unistd.h> //sleep

using namespace std;

// 定义一个互斥量
std::mutex m;

// 启用互斥量后，可以看到每个线程输出是连续的，不是交叉的
void f1(int a){
    int i = 10;
    // 锁定该互斥量
    m.lock();
    while (i>0)
    {
        cout << (i+a) << endl;
        i--;
        sleep(0.1);
        
    }
    // 解锁该互斥量
    m.unlock();
    
}

int counter = 0;

void f2(){
    for (int i=0; i<10000; ++i) {
        // m.try_lock() 
        // 当可以m处于unlock状态，上锁并返回true
        // 否则，返回false
        if (m.try_lock()) {   
            ++counter;
            m.unlock();
        }
    }
    
}


int main(){
    // std::thread t1(f1,10);
    // std::thread t2(f1,1000);

    // t1.join();
    // t2.join();

    std::thread t3(f2);
    std::thread t4(f2);

    t3.join();
    t4.join();
    // counter 应该小于 20000
    cout << counter << endl;
 
}