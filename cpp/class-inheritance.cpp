#include <iostream>

// 定义空间的类：比较抽象，太多的东西可以叫做空间了
class space_class
{
protected:
	int __dimensions;
public:
	// 构造
	space_class(const int dimensions__):
		__dimensions{dimensions__}
	{
	}
	int get_dimensions() const
	{
		return __dimensions;
	}
};

// 定义地球空间的类, 继承自空间类：我们所生活的环境
class earth_space_class: public space_class
{
public:
	// 构造
	earth_space_class(const int dimensions__):
		space_class{dimensions__}	// 委派基类构造
	{
	}
};

int main()
{
	space_class space{11};
	earth_space_class earth{3};
	std::cout << space.get_dimensions() << std::endl;
	std::cout << earth.get_dimensions() << std::endl;
}

