#include <iostream>
#include <thread>

using namespace std;

class Test{
    int num;
public:
    void set_num(int a){
        num = a;
        cout << num << endl;
    }
};

int main(){
    // 使用类成员函数作为线程函数，需依次传入
    // 1. 成员函数地址
    // 2. 对象地址
    // 3. 成员函数所需的参数
    Test test;
    std::thread t(&Test::set_num, &test, 10);
    t.join();
    return 0;
}