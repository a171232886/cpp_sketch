#include <iostream>
#include <thread>
#include <vector>

using namespace std;

/*
auto 自动类型推导
1. 给定初值（或初始化），编译器自动推导变量类型
    auto a = 1; 相当于 int a = 1;
    auto a = fun(); 取决于函数返回类型；

for循环的新写法
1. for (i:coll) 相当于python中 for i in coll：
2. 通常会和auto一起使用，遍历数组和容器
*/


int main(){

    int arr[]={1,2,3};
    std::vector<int> v{1,2,3};

    auto i = 1; // 相当于int a = 1;
    // 相当于 std::vector<int>::itreator it = v.begin();
    auto it = v.begin();  

    /* 相当于
    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        auto a = arr[i];
        cout << a <<endl;
    }  
    */
    for (auto a : arr){
        cout << a <<endl;
    }
    
    /*
    for (auto vi : v){
        cout << vi << endl;
    }
    相当于
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        auto vi = *it;
        cout << vi << endl;
    }

    注意区分 auto & vi 和 auto vi的区别
    1. 对于v而言，auto & v : vi 相当于对其中元素的引用 
    2. auto vi : vi 相当于对其中元素的copy
    */

    for (auto & vi : v){
        vi ++;
    }

    for (auto vi : v){
        cout << vi << endl;
    }


    return 0;
}