#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

/*
类的上下：
    因为先写父类，才能写子类。所以从代码上，通常父类在上，子类在下。
    向上转换，即从子类向父类转换；反之同理。

对static_cast的结论:
    static_cast和dynamic_cast相比缺少运行时检查，在向下转换时存在风险！
    不要使用！！！
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

    Son * p3 = static_cast<Son *>(pbs);
    p3->print_son_a();   // 符合预期，输出0       This is Son!

    cout << "----------------------------------" << endl;

    /*
    此时会出现风险：pb指向的Basic没有Son的成员变量和函数
    但static_cast仍然转化，且不返回nullptr
    */
    Son * p4 = static_cast<Son *>(pb);
    if (p4 == nullptr){
        cout << "error" << endl;   // 不会执行
    }
    
    cout << typeid(p4).name() << endl; // P3Son, 但执行却不是按照Son中的定义

    /*
    错误输出：0       This is Son!
    疑似static_cast会给p4自动创建一个Son对象, 但里面的值是默认的，比如int a = 0;
    */
    p4->print_son_a();  
    cout << p4->a << endl; // 甚至可以直接访问成员a
    p4->print_basic();    // 错误输出:This is basic!

    
    return 0;
}