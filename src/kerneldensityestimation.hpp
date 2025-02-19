#pragma once

#include <vector>
#include <numeric>
#include <limits>
#include <iostream>
#include <algorithm>
#include "../extern/mixlightlib/include/integrator.hpp"


constexpr double infinity = std::numeric_limits<double>::infinity();

template<typename Function>
class KernelDensityEstimation{

private:
	Function func_;
	const std::vector<double> values_;
	double bandwidth_;
	double a_, b_;
	double Zinv_;

public:
	// constructors
	KernelDensityEstimation(const double * ptr, size_t N, double bandwidth=1, double a=-infinity, double b=infinity) : func_(), values_(ptr, ptr+N), bandwidth_(bandwidth), a_(a), b_(b), Zinv_(computeZinv(a,b)) {};
	
	KernelDensityEstimation(std::vector<double> values, double bandwidth=1, double a=-infinity, double b=infinity) : func_(), values_(values), bandwidth_(bandwidth), a_(a), b_(b), Zinv_(computeZinv(a,b)) {};

	KernelDensityEstimation(Function f, std::vector<double> values, double bandwidth=1, double a=-infinity, double b=infinity) : func_(f), values_(values), bandwidth_(bandwidth), a_(a), b_(b), Zinv_(computeZinv(a,b)) {};

	// call operator
	double operator()(double x) const{
		if (x < a_ || x > b_){
			return 0;
		}
		return Zinv_ * unnormalizeEval(x);
	};

private:

	double computeZinv(double a, double b){
		double max_element = *std::max_element(values_.begin(), values_.end());
		double min_element = *std::min_element(values_.begin(), values_.end());
		double scale = 0.5 * (max_element - min_element);
		double loc = 0.5 * (max_element + min_element);
		Integrator integrator([this](double x){ return unnormalizeEval(x); }, a, b, 1e-10, scale, loc);
		if (!integrator.success()){
			std::cerr << "The normalization of the KernelDensityEstimation at " << this << " failed" << std::endl;
		}
		return 1 / integrator.result();
	};

	double unnormalizeEval(double x) const{
		double result = std::accumulate(values_.begin(), values_.end(), 0., [this, x](double acc, double v){ return acc + func_((x - v) / bandwidth_); });
		return result / bandwidth_;
	};
};
