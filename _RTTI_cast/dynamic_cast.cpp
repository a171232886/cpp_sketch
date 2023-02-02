#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

/*
类的上下：
    因为先写父类，才能写子类。所以从代码上，通常父类在上，子类在下。
    向上转换，即从子类向父类转换；反之同理。
    
    向上转换因为能直接进行 Basic * pb = new Son; 不再讨论
    重点讨论向下转化
*/

class Basic{
public:
    virtual void print_basic(){
        cout << "\tThis is basic!" << endl;
    }
};

class Son : public Basic{
public:
    int a = 1;
    // 考虑到使用dynamic_cast，此处重写虚函数
    void print_basic(){
        cout << "\tThis is basic, But in the son!" << endl;
    }

    void print_son(){
        cout << "\tThis is Son!" << endl;
    }

    void print_son_a(){
        cout<< "\t" << a << "\tThis is Son!" << endl;
    }
};

int main(){
    Basic * pb = new Basic;
    Basic * pbs = new Son;
    Son * ps = new Son;

    pb->print_basic();
    ps->print_basic();
    ps->print_son();
    ps->print_son_a();
    //pbs->print_son();  //编译错误

    // 查看指针指向的类名typeid(p2).name()
    // 也可以通过 typeid(pb) == typeid(Basic) 判断
    cout << typeid(pb).name() <<endl;

    cout << "----------------------------------" << endl;

    // dynamic_cast 向下转化
    cout << "dynamic_cast 向下转化:" << endl;

    // 运行时会检查是否能安全转化，
    // 可转换，则返回对应转换后指针；否则返回nullptr
    Son * p1 = dynamic_cast<Son *>(pbs);  
    if (p1 == nullptr){
        cout << "error" << endl;
    }
    else{
        cout << "succes" << endl;
        p1->print_son();
    }

    // 转换失败
    Son * p2 = dynamic_cast<Son *>(pb);
    if (p2 == nullptr){
        cout << "error" << endl;
        cout << typeid(p2).name() <<endl;  // P3Son
        cout << (typeid(p2) == typeid(nullptr))  <<endl;  // 0
    }

    cout << "但注意即使转换失败也能使用一些与变量无关的函数" << endl;
    /*
    猜测是该部分成员函数代码(print_son())为该类所有对象共用导致
    因此检测p2是否为nullptr十分重要
    */
    p2->print_son();    // 成功运行
    // p2->print_son_a();  // 报错
    // cout << p2->a << endl;  // 报错


    return 0;
}