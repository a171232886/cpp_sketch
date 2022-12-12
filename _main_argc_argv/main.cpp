#include<iostream>
using namespace std;

/*
使用时： ./main 1 'b' "sd"

argc 表示参数个数（输入参数个数+1），自动计算，不必输入。

argv 输入参数
argv[0] 恒为当前可执行文件的相对路径

argv[1] argv[2] argv[3] ... 为输入参数（已转换成字符串）

*/

int main(int argc, char * argv []){

    cout << "the num of input arg: " << argc<< endl;
    cout << "the relative path of exe: " << argv[0]<< endl;

    cout << "the first args: " << argv[1]<< endl;
    cout << "the second args: " << argv[2]<< endl;
    cout << "the second args: " << argv[3]<< endl;

    return 0;
}
