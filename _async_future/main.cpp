#include <iostream>
#include <future>  // future async
#include <thread>
#include <chrono>
#include <vector>
#include <stdlib.h> // srand
#include <time.h>   // time
using namespace std;

vector<char> v;

int add_char(char c){
    srand((unsigned)time(NULL)); // 设置时间为随机种子

    for (int i=0 ; i<10; i++){
        v.push_back(c);
        std::this_thread::sleep_for(std::chrono::microseconds(rand()%100 + 30));
    }

    return 0;
}

int main(){
    
    std::future<int> fun1 = std::async(add_char, '.');

    // int result = fun1.get() + add_char('+');   // . . . . . . . . . . + + + + + + + + + + 
    int result = add_char('+') + fun1.get();
    
    for (auto i : v){
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}
