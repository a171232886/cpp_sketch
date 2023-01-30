#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
左值引用：
    1. 类型如 int & a
    2. 可以取地址、位于等号左边

右值引用：
    1. 类型为 int && a
        注意：直接声明 int && a = 1， 实际上a还是左值引用，只有std::move(变量)的返回才是右值引用
                即，作为函数返回值的 && 是右值，直接声明出来的 && 是左值
    2. 没法取地址，位于等号右边
        如： 1， "1", 1+1, Test()

const + 左值引用:
    可以做到左右值引用都接受，但不能改变其中的值
    如函数形参列表中 function(const int & a)


std::move 的功能：把一个左值引用变为右值引用

std::forward<T>(u)
    1. 当T为左值引用类型时，u将被转换为T类型的左值引用
        如：std::forward<int &>(u)
    2. 否则u将被转换为T类型右值引用
        如：std::forward<int>(u)
            std::forward<int &&>(u)
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
    Test t2 = std::move(t1); // 隐式调用移动构造


    // 隐式调用拷贝构造(使用const Test & temp接受右值); 隐式调用移动构造, 两者均可，出现语义矛盾。
    // 直接使用g++编译，既不输出“拷贝构造”，也不输出“移动构造”
    // 在禁用编译器优化的情况下
    //      g++ -fno-elide-constructors main3.cpp -o main3 && ./main3
    // 调用移动构造
    Test t3 = Test(3); 
    cout << "*t3.a:" << *t3.a << endl;
    

    Test && t = Test(); // 作为函数返回值的 && 是右值，直接声明出来的 && 是左值
    Test t4 = t;  //隐式调用拷贝构造

    Test t5 = std::forward<Test>(t2);  // 隐式调用移动构造
    Test t6 = std::forward<Test &>(t3);  // 隐式调用拷贝构造
    Test t7 = std::forward<Test &&>(t4);  // 隐式调用移动构造

    return 0;
}