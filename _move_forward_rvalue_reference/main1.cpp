#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
强烈推荐参考文献：https://zhuanlan.zhihu.com/p/335994370

std::move 的最大用处：
    当对元素使用临时元素进行初始化赋值（或在数组中加入临时元素）时，并且这个临时元素后续不再使用，可以减少一次复制。
    这对于处理一个占空间很大的元素（比如一个长字符串），可提升代码速度。

    比如： vector<int> b = std::move(temp); temp是字符串，且后续不再使用
    注意：
         1. **首先std::move(temp)将temp转变为右值引用；然后触发vector的“移动构造函数”** （详见main2.cpp）

         2. 不是所有的数据类型都支持，int就不支持；而容器string和vector是支持的

         3. string和vector的使用std::move对于temp的行为不一致（详见test1()）
            这与该类的“移动构造函数”的具体实现有关。

         3. vector<int> b = std::move(temp); 
            逻辑大致相当于代码
            Array(const Array& temp_array, bool move) {
                data_ = temp_array.data_;
                size_ = temp_array.size_;
                // 为防止temp_array析构时delete data，提前置空其data_      
                temp_array.data_ = nullptr;  // 受引用的语法限制，该句在此处实际上是无法实现
            }

std::move 的唯一功能：把一个左值引用变为右值引用。    
*/

void test1(){
    string a = "123";
    cout << "a:" << a << "\t&a:" << &a << endl;

    string b = std::move(a);
    cout << "a:" << a << "\t&a:" << &a << endl;  // a 为空字符串，但仍可访问
    cout << "b:" << b << "\t&b:" << &b << endl;  // a 与 b 的地址不同
    cout << "&a[0]:" << &(a[0]) << endl;
    cout << "&b[0]:" << &(b[0]) << endl;

    cout << "-----------------------------"<<endl;


    vector<int> v1 = {1,2,3};
    cout << "v1:" << v1[0] << "\t&v1[0]:" << &v1[0] << endl;
    vector<int> v2 = std::move(v1);
    cout << "&v1:" << &v1 << endl;   
    cout << "&v2:" << &v2 << endl; // v1 与 v2 的地址不同
    // cout << "v1[0]:" << v1[0] << "\t&v1[0]:" << &v1[0] << endl;  // 报错
    cout << "v2[0]:" << v2[0] << "\t&v2[0]:" << &v2[0] << endl;  // v1[0] 与 v2[0] 的地址相同

    return ;
}

int main(){
    test1();
    return 0;
}