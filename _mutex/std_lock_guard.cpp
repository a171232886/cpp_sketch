#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex mtx;
int counter = 0;

void f1(int a){
    cout << std::this_thread::get_id() << ": counter =" << counter << endl;
    {
        // std::lock_guard可以使程序进入该作用域时，
        // 在创建std::lock_guard处，自动上锁，此处相当于mtx.lock()
        // 当程序走出该作用域时，自动解锁，此处相当于mtx.unlock()
        std::lock_guard<std::mutex> lock(mtx);
        counter = a; 
        for (int i = 0; i<10; i++){
            counter++;
            std::this_thread::sleep_for(std::chrono::microseconds(10));
        }
        cout << std::this_thread::get_id() << ": counter =" << counter << endl;
    } 
    return;
}

int main(){
    std::thread t1(f1,10);
    std::thread t2(f1,100);

    t1.join();
    t2.join();
    return 0;
}