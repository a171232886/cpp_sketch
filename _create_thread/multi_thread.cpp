#include <iostream>
#include <thread>

using namespace std;

void fun(){
    for (int i = 0; i < 10; i++){
        cout << std::this_thread::get_id() << ": " << i << endl; 
    }
}

int main(){
    int n = 10;
    std::thread threads[n];
    for (int i = 0; i < n; i++){
        threads[i] = std::thread(fun);
    }

    for (int i = 0; i < n; i++){
        threads[i].join();
    }
}