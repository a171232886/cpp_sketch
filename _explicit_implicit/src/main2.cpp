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
	explicit Str(const char*p) {
		cout << "传入字符串：" << p << endl;
	}

    // 传入数字
	explicit Str(int n) {
		cout << "传入数字："  << n << endl;
	}

	// 带默认参数的情况
	explicit Str(double f, int n1=-1){
		cout << "传入数字，带默认："  << f <<", n1:" << n1 << endl;		
	}
};


class Test {
public:
	explicit Test(int a):m_val(a) {}
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
 
	// Str s = "Hello";//该语句编译出错，因为explicit禁用隐式转换
 
	//下面两种写法比较正常：
	Str s20(10);   //OK. 构造 
    Str s21("10");   //OK. 构造 
	Str s3 = Str(10); //OK. 构造临时对象，拷贝构造 

	// Str s4 = 10; //该语句编译出错，因为explicit禁用隐式转换
	// Str s5 = 'a'; //该语句编译出错，因为explicit禁用隐式转换
	// Str s23 = 1.1; 	//该语句编译出错，因为explicit禁用隐式转换


	Test t(10);
	// if (t.isSame(10)) //该语句编译出错，因为explicit禁用隐式转换
	// {
	// 	cout << "隐式转换" << endl;
	// }

	return 0;
}

