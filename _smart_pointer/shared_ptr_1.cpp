#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;


void func(string * p){
    cout << "delete shared_ptr" << endl;
    delete p;
}

int main(){
    // 只能显示调用拷贝构造，不可以sp1=new string("11123")，
    // 可以sp1=make_shared<string>("111")
    // 当创建单个元素时，
    // 第二个参数作为释放指针时的function，不是必需
    std::shared_ptr<string> sp1(new string("11123"), func); 


    // 当创建数组时，必须传入第二个参数(可以用lambda表达式)
    // 注意：shared_ptr没有[], 即无法使用sp_arr[0]
    std::shared_ptr<int> sp_arr(new int[10], [](int *p){delete [] p;});

    // 创建两个vector，共享元素
    std::vector<std::shared_ptr<string>> v1, v2;
    v1.push_back(sp1);
    v1.push_back(std::shared_ptr<string>(new string("abcedf"), func));

    for (auto item : v1){
        v2.push_back(item);
    }
    v2.push_back(std::shared_ptr<string>(new string("!@#$%^&"), func));

    // 通过共享指针修改内容
    *v2[1] = "sdsdsdsd";

    cout << "v1:" << '\t'; 
    for (auto p : v1){
        cout << *p <<'\t';
    }
    cout << endl;

    cout << "v2:" << '\t'; 
    for (auto p : v2){
        cout << *p <<'\t';
    }
    cout << endl;    

    // 统计有几个共享指针指向sp1对应的内存
    // 通常依据该数量进行操作
    cout << sp1.use_count() << endl; 

    // 程序结束自动释放sp1，sp2，sp3



    return 0;
}