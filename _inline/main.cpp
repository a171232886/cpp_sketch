#include <iostream>
using namespace std;

/*
内联函数inline:
    1. 内联函数的作用是在函数被调用处展开，省去普通函数的调用开销
    2. 如果函数体代码过长或者函数体重有循环语句，if语句或switch语句或递归时，不宜用内联
    3. inline 是一种“用于实现的关键字”，而不是一种“用于声明的关键字”：
        通知编译器建议次函数在被调用处展开，
        但编译器可以选择忽略该建议。
    4. 通常在定义处天剑inline关键字，但不强制    
*/

inline void printH(){
    cout << "Hello World" << endl;
}

int main(){
    printH();
    return 0;
}