#include <iostream>
#include <utility>

using namespace std;

struct MyStruct{
    int a;
    char b;
};

class MyClass{

    int a;
    char b;
public:    
    MyClass(int a, char b){
        this->a = a;
        this->b = b;
    }

    int get_a(){
        return a;
    }
};

int main(){
    
    // std::swap 交换两个同类型的值，
    // 内部使用std::move
    // 头文件  #include <utility>

    int x = 0, y = 1;
    std::swap(x,y);
    cout << x << endl;

    MyStruct a{1,'1'}, b{2,'2'};
    std::swap(a,b);
    cout << a.a << endl;

    MyClass c1(1,'1'), c2(2,'2');
    std::swap(c1,c2);
    cout<< c1.get_a() << endl;

}