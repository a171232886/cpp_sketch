#include <iostream>
using namespace std;

/*
参考：https://blog.csdn.net/weixin_38339025/article/details/89161324

default 和 delete 均针对默认函数：默认构造，默认拷贝，默认赋值，默认析构

default：
    当编写有参构造时，需要手动编写无参构造。此时可用Test() =default，表明使用默认构造

delete：
    当某些类的拷贝或赋值没有意义或可能带来危险时，
    使用Test(const Test &) =delete，Test & operator=(const Test &) =delete表示禁用拷贝或赋值
*/

class TestDefault{
public:
    int a=10;

    TestDefault(int thea){
        cout << "手写的默认构造" <<endl;
    }

    TestDefault() = default;
    TestDefault(const TestDefault &) = default;
    TestDefault & operator=(const TestDefault &) = default;
    ~TestDefault() = default;
};

class TestDelete{
public:    
    int a=10;

    TestDelete() = default;
    TestDelete(int thea){
        cout << "手写的默认构造" <<endl;
    }
    TestDelete(const TestDelete & te) = delete;
    TestDelete & operator=(const TestDelete &) = delete;
    ~TestDelete(){};

};


int main(){
    TestDefault t(1);
    TestDefault t2(t);
    t.a = 2;
    t2 = t;
    cout << t2.a << endl;

    TestDelete te1, te2; // 启用默认构造
    // te1 = te2;  // 编译不通过，因为delete禁用赋值
    // TestDelete te3(te1);  // 编译不通过，因为delete禁用赋值
    

    return 0;
}