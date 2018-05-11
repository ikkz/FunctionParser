#include "function_parsing.h"

namespace fp
{
	//independent_variable
	independent_variable::independent_variable(std::string iv) :m_iv(iv)
	{
	}

	std::string independent_variable::str()
	{
		return m_iv;
	}

	double independent_variable::value(double x)
	{
		return x;
	}

	//constant_function
	constant_function::constant_function(double ac) :c(ac)
	{
	}

	std::string constant_function::str()
	{
		auto str = std::to_string(c);
		while ((!str.empty()) && str.at(str.size() - 1) == '0')
		{
			str.pop_back();
		}
		if (!str.empty() && str.at(str.size() - 1) == '.')
		{
			str.pop_back();
		}
		return str;
	}

	double constant_function::value(double x)
	{
		return c;
	}

	//add_function
	add_function::add_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string add_function::str()
	{
		return "(" + m_lhs->str() + "+" + m_rhs->str() + ")";
	}

	double add_function::value(double x)
	{
		return m_lhs->value(x) + m_rhs->value(x);
	}

	//minus_function
	minus_function::minus_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string minus_function::str()
	{
		return "(" + m_lhs->str() + "-" + m_rhs->str() + ")";
	}

	double minus_function::value(double x)
	{
		return m_lhs->value(x) - m_rhs->value(x);
	}

	//multiply_function
	multiply_function::multiply_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string multiply_function::str()
	{
		return "(" + m_lhs->str() + "*" + m_rhs->str() + ")";
	}

	double multiply_function::value(double x)
	{
		return m_lhs->value(x) * m_rhs->value(x);
	}

	//divide_function
	divide_function::divide_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string divide_function::str()
	{
		return "(" + m_lhs->str() + "/" + m_rhs->str() + ")";
	}

	double divide_function::value(double x)
	{
		if (m_rhs->value(x) == 0)
			throw std::invalid_argument("the diviser cannot be 0!");
		return  m_lhs->value(x) / m_rhs->value(x);
	}

	//power_function
	power_function::power_function(base_function_ptr lhs, base_function_ptr rhs) :m_lhs(lhs), m_rhs(rhs)
	{
	}

	std::string power_function::str()
	{
		return "(" + m_lhs->str() + "^" + m_rhs->str() + ")";
	}

	double power_function::value(double x)
	{
		return pow(m_lhs->value(x), m_rhs->value(x));
	}
}//namespace fp
