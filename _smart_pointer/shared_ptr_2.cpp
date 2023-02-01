#include <iostream>
#include <memory>
#include <vector>
#include <string>
using namespace std;

class Basic{
public:
    int a = 1;
    std::shared_ptr<Basic> sptr = nullptr; 

    Basic(){}
    Basic(int v, std::shared_ptr<Basic> s = nullptr){
        a = v;
        sptr = s;
    }

    void set_a(int value){
        a = value;
    }

};

int main(){
    std::shared_ptr<Basic> sp(new Basic);
    std::shared_ptr<Basic> sp1(new Basic(10, sp));

    cout << "sp1->a=" << sp1->a << endl;
    
    sp1->set_a(2);
    cout << "sp1->a=" << sp1->a << endl;
    cout << "(*sp1).a=" << (*sp1).a << endl;
    cout << "sp1->sptr->a=" << sp1->sptr->a << endl;

    cout << "sp1.get()=" << sp1.get() << endl;
    cout << "((Basic*)sp1.get())->a=" << ((Basic*)sp1.get())->a << endl;

    return 0;
}