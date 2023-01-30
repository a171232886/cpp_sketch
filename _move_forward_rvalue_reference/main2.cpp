#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
构造函数和移动构造函数：
    1. 拷贝构造和赋值重载传入左值引用
    2. 移动构造和移动赋值重载传入右值引用
*/

class Test{
public:
    int *a;
    // 默认构造
    Test(){
        a = new int(1);
        cout << "默认构造" << endl;
    }

    // 传参构造
    Test(int t){
        a = new int(t);
        cout << "传参构造" << endl;
    }

    // 拷贝构造
    Test(const Test & temp){
        a = new int(*(temp.a));
        cout << "拷贝构造" << endl;
    }

    // 赋值重载
    Test& operator=(const Test & temp){

        a = new int(*(temp.a));
        cout << "赋值重载" << endl;
        return *this;
    }

    // 移动构造
    Test(Test && temp){
        a = temp.a;
        temp.a = nullptr;
        cout << "移动构造" << endl;
    }

    // 移动赋值重载
    Test& operator=(Test && temp){
        a = temp.a;
        temp.a = nullptr;
        cout << "移动赋值重载" << endl;
        return *this;
    }

    
    // 析构
    ~Test(){
        if (a != nullptr){
            delete a;
            a = nullptr;
        }
        cout << "析构" << endl;
    }

};

int main(){
    Test t1(2);
    Test t2(t1); // 显示调用拷贝构造
    Test t3 = t1;  // 隐式调用拷贝构造

    Test t4; // 默认构造
    t4 = t1; // 赋值重载

    Test t5(std::move(t1)); // 显示调用移动构造
    cout << "*t5.a=" << *t5.a << endl; 

    Test t6 = std::move(t2); // 隐示调用移动构造
    cout << "*t6.a=" << *t6.a << endl; 

    *t4.a = 1;
    t4 = std::move(t3); // 移动赋值重载
    cout << "*t4.a=" << *t4.a << endl; 

    // cout << "t1.a:" << t1.a << "\t *t1.a:" << *t1.a << endl; // 报错，因为t1.a=nullptr
    Test t7(std::move(t1)); // 尽管此时还可以使用t1，但t1.a=nullptr，无意义

    
    return 0;
}