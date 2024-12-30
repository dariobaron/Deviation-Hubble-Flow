#pragma once

#include <vector>

template<typename Function>
class KernelDensityEstimation{

private:
	Function func_;
	const std::vector<double> values_;
	double bandwidth_;

public:
	// constructors
	KernelDensityEstimation() {};

	KernelDensityEstimation(const double * ptr, size_t N, double bandwidth=1) : func_(), values_(ptr, ptr+N), bandwidth_(bandwidth) {};
	
	KernelDensityEstimation(std::vector<double> values, double bandwidth=1) : func_(), values_(values), bandwidth_(bandwidth) {};

	KernelDensityEstimation(Function f, std::vector<double> values, double bandwidth=1) : func_(f), values_(values), bandwidth_(bandwidth) {};

	// call operator
	double operator()(double x) const{
		double result = 0;
		for (auto v : values_){
			result += func_((x - v) / bandwidth_);
		}
		return result / bandwidth_ / values_.size();
	};
};
