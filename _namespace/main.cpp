#include "header1.h"
#include "header2.h"

// 以下代码均使用命名空间std
using namespace std;

// 对命名空间space1和space2的函数进行定义
void space1::func(){
    cout<<"Hello"<<endl;
}

void space1::say(){
    cout<<"!"<<endl;
}

void space2::func(){
    cout<<"World"<<endl;
}

int main(){
    // space1和space2的函数的使用
    space1::func();
    space2::func();
    space1::say();
}

// 参考
// https://www.runoob.com/cplusplus/cpp-namespaces.html