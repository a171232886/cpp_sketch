#include <iostream>
using namespace std;

/*
参看：https://zhuanlan.zhihu.com/p/260992059
override用于重写虚函数的检查：
    当重写虚函数时，需要保证函数名，返回类型，参数列表，const属性一致；
    若本意想重写虚函数，但不小心其中一项不一致，则创建了一个新的函数。

    override关键字提供检查保证以上几项一致，否则编译报错。

final用于类或者函数：
    1. 对类的声明
*/

class Base{
public:
    virtual void printH(){
        cout << "Hello World from Base" << endl;
    }
};

class Son: public Base{
public:

    virtual void printH() override{
        cout << "Hello World from Son" << endl;
    }

    // virtual void printH() const override; //报错, 因为override检查
    // virtual void printH() const; //编译通过
};

int main(){
    Son son;
    son.printH();
    return 0;
}