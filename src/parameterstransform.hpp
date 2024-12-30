#pragma once

#include <vector>
#include <variant>


class WeightTransform{
private:
	unsigned n_;
public:
	WeightTransform() : n_(0) {};
	void addFunction(){
		++n_;
	}
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


class GaussTransform{
public:
	GaussTransform() = default;
	double* operator()(double * ptr) const{
		ptr[1] *= ptr[1];
		return &ptr[2];
	}
};


using Transformers = std::variant<GaussTransform>;


class ParametersTransform{
private:
	std::vector<Transformers> transformers_;
	WeightTransform wt_;
public:
	ParametersTransform() = default;

	void addFunction(const Gaussian & ){
		transformers_.push_back(GaussTransform());
		wt_.addFunction();
	}

	void operator()(double * ptr) const{
		ptr = wt_(ptr);
		for (auto & t : transformers_){
			ptr = std::visit([ptr](auto && f){ return f(ptr); }, t);
		}
	}
};