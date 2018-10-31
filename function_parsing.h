#ifndef _FP_H_
#define _FP_H_

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>

namespace fp
{
	class BaseFunction;
	using BaseFunctionPtr = std::shared_ptr<BaseFunction>;
	BaseFunctionPtr function_parse(std::string func_str);
	std::ostream& operator<<(std::ostream& os, BaseFunctionPtr& func);


	enum FunctionType
	{
		T_BASE_FUNCTION,
		T_INDEPENDENT_VARIABLE,
		T_CONSTANT_FUNCTION,
		T_ADD_FUNCTION,
		T_MINUS_FUNCTION,
		T_MULTIPLY_FUNCTION,
		T_DIVIDE_FUNCTION,
		T_POWER_FUNCTION,
		T_LN_FUNCTION,
		T_SIN_FUNCTION,
		T_COS_FUNCTION,
		T_TAN_FUNCTION
	};

	class BaseFunction
	{
	public:
		virtual std::string str() = 0;
		virtual double value(double x) = 0;
		virtual BaseFunctionPtr derivative() = 0;
		virtual BaseFunctionPtr derivative(unsigned int n);
		const FunctionType _type;
		BaseFunction(FunctionType type) :_type(type) {}
	};

	class IndependentVariable :public BaseFunction
	{
	private:
		std::string _iv;
	public:
		IndependentVariable(std::string iv);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class ConstantFunction :public BaseFunction
	{
	private:
		double _c;
	public:
		ConstantFunction(double c);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class AddFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _lhs;
		BaseFunctionPtr _rhs;
	public:
		AddFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class MinusFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _lhs;
		BaseFunctionPtr _rhs;
	public:
		MinusFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class MultiplyFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _lhs;
		BaseFunctionPtr _rhs;
	public:
		MultiplyFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class DivideFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _lhs;
		BaseFunctionPtr _rhs;
	public:
		DivideFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class PowerFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _lhs;
		BaseFunctionPtr _rhs;
	public:
		PowerFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class LnFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _arg;
	public:
		LnFunction(BaseFunctionPtr arg);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class SinFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _arg;
	public:
		SinFunction(BaseFunctionPtr arg);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class CosFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _arg;
	public:
		CosFunction(BaseFunctionPtr arg);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	class TanFunction :public BaseFunction
	{
	private:
		BaseFunctionPtr _arg;
	public:
		TanFunction(BaseFunctionPtr arg);
		std::string str() override;
		double value(double x) override;
		BaseFunctionPtr derivative() override;
	};

	//for piecewise function
	class SegmentPoint
	{
	private:
		double _value;
		bool _contain;
	public:
		SegmentPoint(double value = 0, bool contain = false)
			: _value(value), _contain(contain)
		{
		}

		double value() const
		{
			return _value;
		}

		void set_value(double v)
		{
			_value = v;
		}

		bool contain() const
		{
			return _contain;
		}

		void set_contain(bool c)
		{
			_contain = c;
		}

		bool operator<(const SegmentPoint& rhs) const
		{
			return _value < rhs._value;
		}

		bool operator>(const SegmentPoint& rhs) const
		{
			return _value > rhs._value;
		}
	};

	class Segment
	{
	private:
		SegmentPoint _left;
		SegmentPoint _right;
	public:
		Segment()
		{
		}

		Segment(const SegmentPoint& lp, const SegmentPoint& rp)
		{
			set_point(lp, rp);
		}

		void set_point(const SegmentPoint& lp, const SegmentPoint& rp)
		{
			if (lp < rp)
			{
				_left = lp;
				_right = rp;
			}
			else
			{
				_left = rp;
				_right = lp;
			}
		}

		void set_left_point(const SegmentPoint& lp)
		{
			set_point(lp, _right);
		}

		void set_right_point(const SegmentPoint& rp)
		{
			set_point(_left, rp);
		}

	};

	class PiecewiseFunction :public BaseFunction
	{
	private:
	};
}//namespace fp

#endif