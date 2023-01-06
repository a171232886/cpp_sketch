#include <iostream>

using namespace std;

/*
参考：https://learn.microsoft.com/zh-cn/cpp/cpp/examples-of-lambda-expressions?view=msvc-170
*/

void fun(){
    int a = 1;
    /*
    lambda 表达式
    [] 引用参数
    () 传入参数，类似函数形参
    {} Lambda体，函数语句
    */ 
    
    auto c = [](int b){return b + 2;};

    a = c(a);
    cout << a << endl;

}

int main(){
    fun();
    return 0;
}