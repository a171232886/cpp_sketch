#include <iostream>
#include <thread>
#include <mutex>

/*
std::recursive_mutex 可使处于同一线程的函数对某个锁重复上锁，而不引发死锁。
1. 重复上锁次数=重复解锁次数，即可将该锁处于unlock状态
2. 若将代码中的std::recursive_mutex替换为std::mutex，会引发死锁：
   - 输出“in fun2, shared variable is now fun2”后卡死
*/
 
class X {
    std::recursive_mutex m;
    std::string shared;
  public:
    void fun1() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun1";
      std::cout << "in fun1, shared variable is now " << shared << '\n';
    }
    void fun2() {
      std::lock_guard<std::recursive_mutex> lk(m);
      shared = "fun2";
      std::cout << "in fun2, shared variable is now " << shared << '\n';
      fun1(); // 递归锁在此处变得有用
      std::cout << "back in fun2, shared variable is " << shared << '\n';
    };
};
 
int main() 
{
    X x;
    std::thread t2(&X::fun2, &x);
    
    t2.join();
}