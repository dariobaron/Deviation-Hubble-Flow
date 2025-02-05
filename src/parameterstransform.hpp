#pragma once

#include <tuple>
#include <cmath>
#include "kernels.hpp"


class WeightTransform{
private:
	unsigned n_;
public:
	WeightTransform(unsigned n) : n_(n) {};
	double* operator()(double * ptr) const{
		double sum = 0;
		for (unsigned i = 0; i < n_; ++i){
			ptr[i] = std::exp(ptr[i]);
			sum += ptr[i];
		}
		for (unsigned i = 0; i < n_; ++i){
			ptr[i] /= sum;
		}
		return &ptr[n_];
	}
};


template<typename KernelType>
class Transformer{
public:
	Transformer() = default;
	double* operator()(double * ptr) const{
		static_assert(false, "The kernel type is not supported");
		return ptr;
	}
};


template<>
class Transformer<Gaussian>{
public:
	Transformer() = default;
	double* operator()(double * ptr) const{
		ptr[1] *= ptr[1];
		return &ptr[2];
	}
};


template<>
class Transformer<Rayleigh>{
public:
	Transformer() = default;
	double* operator()(double * ptr) const{
		ptr[0] = std::exp(ptr[0]);
		return &ptr[1];
	}
};


template<typename TupleType>
class ParametersTransform{
private:
	WeightTransform wt_;
public:
	ParametersTransform() : wt_(std::tuple_size<TupleType>::value) {};

	void operator()(double * ptr) const{
		ptr = wt_(ptr);
		std::apply(
			[&ptr](auto ...f){
				((ptr = Transformer<decltype(f)>()(ptr)), ...);
			}, TupleType()
		);
	}
};