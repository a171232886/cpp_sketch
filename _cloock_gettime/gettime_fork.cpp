#include <iostream>
#include <time.h>
#include <unistd.h>
using namespace std;

/*
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1)测试该进程的全部线程的CPU时间

1. 函数
test(0) 基准测试
test_multi_fork_version1() 使用fork创建多进程，每个进程使用clock_gettime
                            测试全部线程消耗的CPU时间
test_multi_fork_version2() 与version1区别在于，会衡量父（主）进程的CPU时间

2. 结果
- test(0)和version1()的结果基本相同
- version2()在子进程中额外添加时间统计是子进程的两倍
- version2()的父（主）进程时间是子进程的两倍

表明：
- fork创建的多进程，每个进程下使用clock_gettime可正确统计当前进程的CPU时间
- 衡量主进程的时间，可以在父（主）进程中添加相关代码
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


void test_multi_fork_version1(){
    pid_t pid = fork();

        if (pid < 0)
    {
        // 若pid小于0，表示创建失败
        cout << "未创建成功" << endl;
    }

    if (pid == 0)
    {
        // cout << "子进程" << endl;
        test(0);
    }

    if (pid > 0)
    {
        // cout << "父（主）进程" << endl;
        test(1);

    }
}

void test_multi_fork_version2(){

    struct timespec time1 = {0, 0}; 
    struct timespec time2 = {0, 0};
	
    double temp;
 
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);  

    pid_t pid = fork();

        if (pid < 0)
    {
        // 若pid小于0，表示创建失败
        cout << "未创建成功" << endl;
    }

    if (pid == 0)
    {
        // cout << "子进程" << endl;
        test(0);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);   
        temp = (time2.tv_nsec - time1.tv_nsec);
        printf("time = %f ns, child fork %d\n", temp, -1);

    }

    if (pid > 0)
    {
        // cout << "父进程" << endl;
        test(1);

        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);   
        temp = (time2.tv_nsec - time1.tv_nsec);
        printf("time = %f ns, father fork %d\n", temp, -1);
    }

}


int main(){
    cout<<"------------test(0)-----------------"<<endl;
    test(0);
    cout<<"---test_multi_fork_version1()-------"<<endl;
    test_multi_fork_version1();
    cout<<"---test_multi_fork_version2()-------"<<endl;
    test_multi_fork_version2();
    return 0;
}
