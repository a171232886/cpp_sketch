#include<iostream>
#include<time.h>
#include <unistd.h>
#include <thread>
using namespace std;

/*
1. 函数
struct timespec为内置结构体，
timespec.tv_sec为秒级精确度，timespec.tv_nsec为纳秒级精确度


#include<time.h>
clock_gettime(CLOCK_REALTIME, &time1)统计程序运行时间

*/

void test(){

    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    float temp;
 
    clock_gettime(CLOCK_REALTIME, &time1);      
    usleep(1000);
    clock_gettime(CLOCK_REALTIME, &time2);   
    temp = (time2.tv_nsec - time1.tv_nsec) / 1000000;
    printf("time = %f ms\n", temp);

}




int main(){
    test();
    return 0;
}
