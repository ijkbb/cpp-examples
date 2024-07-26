#include <iostream>

/*
三个要点：
1. 虚拟析构
2. 虚拟继承
3. 当基类虚拟继承基类的基类时，本类对基类的基类的构造函数的委派
*/

class space
{
public:
	virtual ~space()	// 虚拟析构函数
	{
		std::cout << "Destroyed !" << std::endl;
	}
public:
	space()
	{
		std::cout << "space is created." << std::endl;
	}
	space(int)
	{
		std::cout << "space: 0" << std::endl;
	}
};
// 虚拟析构函数的虚拟析构基因会逐层传递给所有的后代

class physical_space: virtual public space	// 虚拟继承
{
public:
	physical_space()
	{
		std::cout << "physical space is created." << std::endl;
	}
	physical_space(int):
		space{0}	// 委派构造
	{
		std::cout << "physical_space: 0" << std::endl;
	}
};
// 虚拟继承的虚拟继承基因只能作用于直接继承关系，不能向除此之外的所有的后代传播

class earth_space: public physical_space
{
public:
	earth_space()
	{
		std::cout << "earth space is created." << std::endl;
	}
	earth_space(int):
		space{0},	// (1)
		physical_space{0}	// (2)
	{
		std::cout << "earth_space: 0" << std::endl;
	}
};

/*
行 (2):
	由于 physical_space 虚拟继承于 space, 
	尽管 physical_space 非默认构造函数会委派调用 space 非默认构造函数，
	当 earth_space 非默认委派构造函数委派调用 physical_space 非默认构造函数时，
	并不会进而先调用 space 非默认构造函数，而是去调用 space 默认构造函数，
	解决的方法是加上 行 (1)，直接委派基类的基类 space 的非默认构造函数。

行 (1):
	只有在基类对基类的基类是虚拟继承时才可以写这一行：对基类的基类的构造函数的委派；
	如果基类对基类的基类不是虚拟继承，写上这行就是语法错误。
*/

int main()
{
	earth_space earth{0};
}

// 从输出信息可以看出，space 并没有被构造两次
/*

// 输出：

space: 0
physical_space: 0
earth_space: 0
Destroyed !

*/
