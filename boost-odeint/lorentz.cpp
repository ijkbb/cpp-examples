#include <boost/numeric/odeint.hpp>
#include <vector>
#include <iostream>
#include <stdfloat>

// 洛伦兹吸引子

namespace odeint = boost::numeric::odeint;

using value_type = std::float64_t;
using time_type = value_type;
using state_type = std::vector<value_type>;

constexpr value_type sigma = 10;
constexpr value_type rho = 25;
constexpr value_type beta = 8.0/3;

class lorentz_class
{
public:
	void operator()(const state_type & in, state_type & diff, const time_type t) const
	{
		// 微分方程组 
		diff[0] = sigma * (in[1] - in[0]);	// x' = sigma (y-x)
		diff[1] = in[0] * (rho - in[2]) - in[1];	// y' = x * (rho - z) - y
		diff[2] = in[0] * in[1] - beta * in[2];	// z' = x*y - beta * z
	}

	// 观察员
	void operator()(const state_type & result, const time_type t) const
	{
		std::cout
			<< std::setw(15) << result[0]
			<< std::setw(15) << result[1]
			<< std::setw(15) << result[2]
			<< std::endl;
	}
};

int main()
{
	auto lorentz = lorentz_class{};
	auto xyz = state_type{-1,-1,-1};
	odeint::integrate_const(
		odeint::runge_kutta4<state_type, value_type>{},
		lorentz,
		xyz,
		time_type{0},
		time_type{10},
		time_type{0.1},
		lorentz
	);
}

