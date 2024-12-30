#pragma once

#include "typedefs.hpp"


class Progress{
private:
	unsigned every_n_;
public:
	Progress(unsigned every_n = 1) : every_n_(every_n) {};

	template<typename OptimizerType, typename FunctionType, typename ParametersType>
	void BeginOptimization(const OptimizerType & opt, const FunctionType & func, const ParametersType & p0){
		py::print("Optimization started");
		
	}

	template<typename OptimizerType, typename FunctionType, typename ParametersType>
	bool Evaluate(const OptimizerType & opt, const FunctionType & func, const ParametersType & p, const double objective){
		if (opt.Iteration() % every_n_ == 0){
			py::print("Iteration ", opt.Iteration(), " - Objective function value = ", func.Evaluate(p), py::arg("end")="\r", py::arg("flush")=true);
		}
		return false;
	}
};