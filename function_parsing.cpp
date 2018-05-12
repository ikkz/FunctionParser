#include "function_parsing.h"

//调试输出
#include <iostream>
using namespace std;

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

	int get_matching_bracket(std::string expr, unsigned int first_pos)
	{
		unsigned int tag = 0;
		for (unsigned int i = first_pos; i < expr.size(); i++)
		{
			if (expr.at(i) == '(')
				tag++;
			else if (expr.at(i) == ')')
				tag--;
			if (tag == 0)
				return i;
		}
		return 0;
	}

	bool is_add_or_minus(char c)
	{
		return c == '+' || c == '-';
	}

	bool include_operators(std::string str)
	{
		for (auto c : str)
		{
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
			{
				return true;
			}
		}
		return false;
	}

	bool is_number(std::string str)
	{
		for (auto c : str)
		{
			if (c<'0' || c>'9')
			{
				return false;
			}
		}
		return true;
	}

	bool is_multiply_or_divide(char c)
	{
		return c == '*' || c == '/';
	}

	bool is_power(char c)
	{
		return c == '^';
	}

	base_function_ptr function_parse(std::string func_str)
	{
		func_str.erase(std::remove_if(func_str.begin(), func_str.end(),
			[](char c) {return c == ' '; }), func_str.end());
		if ((!func_str.empty()) && func_str.at(0) == '('&&get_matching_bracket(func_str, 0) == (func_str.size() - 1))
		{
			func_str.erase(func_str.begin());
			func_str.pop_back();
		}

		if (!include_operators(func_str))
		{
			if (is_number(func_str))
			{
				return make_shared<constant_function>(atoi(func_str.c_str()));
			}
			else
			{
				return make_shared<independent_variable>(func_str);
			}
		}


		unsigned int i = 0;
		std::vector<unsigned int> add_minus;
		while (i < func_str.size())
		{
			if (func_str.at(i) == '(')
			{
				auto next_br = get_matching_bracket(func_str, i);
				if (next_br != -1)
				{
					i = next_br + 1;
					continue;
				}
			}
			if (is_add_or_minus(func_str.at(i)))
			{
				add_minus.push_back(i);
			}
			i++;
		}
		if (!add_minus.empty())
		{
			auto pPre = function_parse(func_str.substr(0, add_minus[0]));
			for (i = 0; i < add_minus.size(); i++)
			{
				switch (func_str.at(add_minus.at(i)))
				{
				case '+':
					if (i != add_minus.size() - 1)
					{
						pPre = make_shared<add_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, add_minus.at(i + 1) - add_minus.at(i) - 1)));
					}
					else
					{
						pPre = make_shared<add_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, func_str.size() - add_minus.at(i) - 1)));
					}
					break;
				case '-':
					if (i != add_minus.size() - 1)
					{
						pPre = make_shared<minus_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, add_minus.at(i + 1) - add_minus.at(i) - 1)));
					}
					else
					{
						pPre = make_shared<minus_function>(pPre, function_parse(func_str.substr(add_minus.at(i) + 1, func_str.size() - add_minus.at(i) - 1)));
					}
					break;
				}
			}
			return pPre;
		}
		else
		{
			std::vector<unsigned int> multiply_divide;
			i = 0;
			while (i < func_str.size())
			{
				if (func_str.at(i) == '(')
				{
					auto next_br = get_matching_bracket(func_str, i);
					if (next_br != -1)
					{
						i = next_br + 1;
						continue;
					}
				}
				if (is_multiply_or_divide(func_str.at(i)))
				{
					multiply_divide.push_back(i);
				}
				i++;
			}
			if (!multiply_divide.empty())
			{
				auto pPre = function_parse(func_str.substr(0, multiply_divide[0]));
				for (i = 0; i < multiply_divide.size(); i++)
				{
					switch (func_str.at(multiply_divide.at(i)))
					{
					case '*':
						if (i != multiply_divide.size() - 1)
						{
							pPre = make_shared<multiply_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, multiply_divide.at(i + 1) - multiply_divide.at(i) - 1)));
						}
						else
						{
							pPre = make_shared<multiply_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, func_str.size() - multiply_divide.at(i) - 1)));
						}
						break;
					case '/':
						if (i != multiply_divide.size() - 1)
						{
							pPre = make_shared<divide_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, multiply_divide.at(i + 1) - multiply_divide.at(i) - 1)));
						}
						else
						{
							pPre = make_shared<divide_function>(pPre, function_parse(func_str.substr(multiply_divide.at(i) + 1, func_str.size() - multiply_divide.at(i) - 1)));
						}
						break;
					}
				}
				return pPre;
			}
			else
			{
				std::vector<unsigned int> power_operator;
				i = 0;
				while (i < func_str.size())
				{
					if (func_str.at(i) == '(')
					{
						auto next_br = get_matching_bracket(func_str, i);
						if (next_br != -1)
						{
							i = next_br + 1;
							continue;
						}
					}
					if (is_power(func_str.at(i)))
					{
						power_operator.push_back(i);
					}
					i++;
				}
				if (!power_operator.empty())
				{
					auto pPre = function_parse(func_str.substr(0, power_operator[0]));
					for (i = 0; i < power_operator.size(); i++)
					{
						if (i != power_operator.size() - 1)
						{
							pPre = make_shared<power_function>(pPre, function_parse(func_str.substr(power_operator.at(i) + 1, power_operator.at(i + 1) - power_operator.at(i) - 1)));
						}
						else
						{
							pPre = make_shared<power_function>(pPre, function_parse(func_str.substr(power_operator.at(i) + 1, func_str.size() - power_operator.at(i) - 1)));
						}
					}
					return pPre;
				}
			}
		}
		return nullptr;
	}


}//namespace fp
