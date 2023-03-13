#include <iostream>
using namespace std;

/*
隐式转换(Implicit conversion)：
    1. 低精度 –> 高精度转换
    2. NULL指针可以转换为任意类型指针
    3. 任意类型的指针可以转换为void指针

在类中的隐式转化:
    1. 出现的场合：  有待深入研究！！！
        （1）单参数构造函数：允许隐式转换特定类型来初始化对象
        （2）赋值操作符：允许从特定类型的赋值进行隐式转换
        （3）类型转换操作符：允许隐式转换到特定类型
    2. 指针向上提升：一个派生类指针可以被转换为一个可访问的无歧义的基类指针，
        不会改变它的const或volatile属性

关键字explicit可以禁用隐式转换，通常用于类的构造函数
*/

class Str
{
public:
	// 传入字符串
	Str(const char*p) {
		cout << "传入字符串：" << p << endl;
	}

    // 传入数字
	Str(int n) {
		cout << "传入数字："  << n << endl;
	}

	// 带默认参数的情况
	Str(double f, int n1=-1){
		cout << "传入数字，带默认："  << f <<", n1:" << n1 << endl;		
	}
};


class Test {
public:
	Test(int a):m_val(a) {}
	bool isSame(Test other)
	{
		return m_val == other.m_val;
	}
private:
		int m_val;
};
 
int main(void) {

    int a = 1;
    float b = 2;
    b = b + a;  // 低精度 –> 高精度转换
 
	Str s = "Hello";//隐式转换，出现类型（1）？，等价于Str s = Str("Hello");
 
	//下面两种写法比较正常：
	Str s20(10);   //OK. 构造 
    Str s21("10");   //OK. 构造 
	Str s3 = Str(10); //OK. 构造临时对象，赋值 
 
	//下面两种写法就比较疑惑了：
	Str s4 = 10; //编译通过
	Str s5 = 'a'; //编译通过，分配int（‘a’）个字节的空字符串,使用的是Str(int n)构造函数
	//s4 和s5 分别把一个int型和char型，隐式转换成了分配若干字节的空字符串，容易令人误解。
	Str s23 = 1.1;

    /*
    本来用于两个Test对象的比较，竟然和int类型相等了。
    这里就是由于发生了隐式转换，实际比较的是一个临时的Test对象。
    这个在程序中是绝对不能允许的。
    */
	Test t(10);
	if (t.isSame(10)) //该语句将返回true
	{
		cout << "隐式转换" << endl;
	}


	return 0;
}

