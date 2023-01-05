// 参看
// 1. https://blog.csdn.net/fuhanghang/article/details/114818215

#include <thread>
#include <iostream>
#include <unistd.h> //sleep
using namespace std;

void f1(int a, int b)  //普通的函数，用来执行线程
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "Hello\n";
        sleep(1);
    }
    cout << a << '\t' << b << endl;

}
void f2()
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "World\n";
        sleep(1);
    }
}

int main(){
    // 创建线程，传入多个参数
    std::thread t1(f1,1,2);
    // 创建线程
    std::thread t2(f2);

    // join运行线程方式
    // 主线程会等待子线程运行结束之后，再退出
    // 主线程阻塞，子线程先运行
    cout<<"before join"<<endl;
    t1.join();
    cout<<"after join t1"<<endl;
    t2.join();
    cout<<"after join t2"<<endl;
    // 查看输出可知，t1和t2几乎同时执行，先于主线程

    // detach运行线程方式
    // 主线程不再管理子线程，不再等子线程结束之后再退出
    // 主线程和子线程并行
    // t1.detach()

    // joinable返回线程是否可执行
    // False True False
    std::thread t3;
    cout<<t3.joinable()<<endl;

    t3=std::thread(f2);
    cout<<t3.joinable()<<endl;

    t3.join();
    cout<<t3.joinable()<<endl;

    

    return 0;
}

