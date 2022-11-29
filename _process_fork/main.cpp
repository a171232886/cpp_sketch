#include <iostream>
#include <unistd.h> // fork sleep
using namespace std;

int main()
{
    cout << "主进程" << endl;
    // fork() 在此处创建两个分支，同时返回两个值
    // 一个pid>0，表示父进程
    // 一个pid<0，表示子进程
    // 注意是同时返回，即父子进程同时执行
    pid_t pid = fork();

    if (pid < 0)
    {
        // 若pid小于0，表示创建失败
        cout << "未创建成功" << endl;
    }

    if (pid == 0)
    {
        cout << "子进程" << endl;
    }

    if (pid > 0)
    {
        cout << "父（主）进程" << endl;
    }

    return 0;
}