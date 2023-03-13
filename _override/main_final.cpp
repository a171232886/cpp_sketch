#include <iostream>
using namespace std;

/*
final用于类或者函数：
    1. 对类的声明，表明该类禁止被继承
    2. 对类的虚函数声明，表明该函数禁止重写
*/

class Base1 final{
public:
    virtual void printH(){
        cout << "Hello World from Base" << endl;
    }
};

class Base2 {
public:
    virtual void printH() final{
        cout << "Hello World from Base" << endl;
    }
};

// class Son1: public Base1;  // 编译出错，禁止继承用final声明的类

class Son: public Base2{
public:

    // virtual void printH(); // 编译出错，禁止继承用final声明的函数
};

int main(){
    Son son;
    son.printH();
    return 0;
}