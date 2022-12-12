#include<iostream>
#include<time.h>
#include <unistd.h>
#include <thread>
using namespace std;

/*
1. 函数
clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1)统计程序的CPU时间

test_single_thread()测试单线程下该函数的使用
test_multi_thread()测试单线程下该函数的使用
理论上两函数输出的数值应相等，结果表明也相等

说明该函数在测量某个线程时，不受其线程影响

2. CPU时间
关于CPU时间，GNU的解释：
CPU time measures the amount of time that a single process
 has actively used a CPU to perform computations. 

**It does not include the time that process has spent waiting for external events**. 
The system tracks the CPU time used by each process separately.

即CPU时间只考虑程序使用CPU的计算时间，不考虑等待CPU的时间。

3. 参考
https://www.gnu.org/software/libc/manual/
https://www.gnu.org/software/libc/manual/html_node/Time-Basics.html
https://www.gnu.org/software/libc/manual/html_node/Processor-And-CPU-Time.html
*/


void test_single_thread(){

    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    double temp;
 
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);  

    int a = 1;
    for(int i=0;i<100000;i++){
        a++;
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time2);   
    temp = (time2.tv_nsec - time1.tv_nsec);
    printf("time = %f ns\n", temp);

}

void add_thread(int thread_id){
    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    double temp;
 
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);  

    int a = 1;
    for(int i=0;i<100000;i++){
        a++;
    }

    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time2);   
    temp = (time2.tv_nsec - time1.tv_nsec);
    printf("CLOCK_THREAD_CPUTIME_ID, time = %f ns, thread %d\n", temp, thread_id);

}

void test_multi_thread(){

    thread t1(add_thread,1);
    thread t2(add_thread,2);
    t1.join();
    t2.join();
}


int main(){
    test_single_thread();
    test_multi_thread();
    return 0;
}