#include <iostream>
#include <concepts>
#include <string>

using std::string_literals::operator""s;

template <typename type_t>
class number_box;

template <std::integral type_t>
class number_box<type_t>
{
protected:
	type_t __value;
public:
	number_box(const type_t value__):
		__value{value__}
	{
	}
	std::string get() const
	{
		return "Integral: "s + std::to_string(__value);
	}
};

template <std::floating_point type_t>
class number_box<type_t>
{
protected:
	type_t __value;
public:
	number_box(const type_t value__):
		__value{value__}
	{
	}
	std::string get() const
	{
		return "floating: "s + std::to_string(__value);
	}
};

template <>
class number_box<void>
{
public:
	number_box() = default;
	std::string get() const
	{
		return "void number";
	}
};

// 模板推导向导
template <std::integral type_t>
number_box(const type_t &) -> number_box<type_t>;

// 模板推导向导
template <std::floating_point type_t>
number_box(const type_t &) -> number_box<type_t>;

int main()
{
	number_box n1{400};
	std::cout << n1.get() << std::endl;	// Integral: 400

	number_box n2{400.23};
	std::cout << n2.get() << std::endl;	// floating: 400.23

	number_box<void> n3;
	std::cout << n3.get() << std::endl;	// void number

	// number_box n4{"c++"};	// 没有定义
	// number_box n5{};	// 没有定义
}

