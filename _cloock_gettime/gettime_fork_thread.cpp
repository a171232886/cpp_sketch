#include <iostream>
#include <time.h>
#include <unistd.h>
#include <thread>
using namespace std;

/*
分析google benchmark中的使用：
单进程创建多线程，每个线程都使用clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1)

结果：
线程1和线程2的时间，大概率不相等且其中一个是另一个的2倍
但也有小概率相等。

分析：
1. 每个线程都使用clock_gettime统计进程时间，会统计其他线程的时间。
    若将每个线程统计的结果求和，会造成时间的重复统计
2. “小概率”相等是因为线程近乎同时执行？

*/

void test(int fork_id){

    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    double temp;
 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);  

    int a = 1;
    for(int i=0;i<100000;i++){
        a++;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);   
    temp = (time2.tv_nsec - time1.tv_nsec);
    printf("time = %f ns, fork %d\n", temp, fork_id);

}


void add_thread(int thread_id){
    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    double temp;
 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);  

    int a = 1;
    for(int i=0;i<100000;i++){
        a++;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);   
    temp = (time2.tv_nsec - time1.tv_nsec);
    printf("CLOCK_PROCESS_CPUTIME_ID, time = %f ns, thread %d\n", temp, thread_id);

}


void test_single_fork(){

    thread t1(add_thread,1);
    thread t2(add_thread,2);
    t1.join();
    t2.join();
}


int main(){
    test(0);
    test_single_fork();
    return 0;
}
