#pragma once

#include <vector>
#include <stdexcept>
#include <variant>
#include <numeric>


template<typename VariantType>
class MixtureDensity{
private:
	std::vector<VariantType> funcs_;
	std::vector<double> weights_;
public:
	MixtureDensity() {};

	unsigned nComponents() const{
		return funcs_.size();
	}

	unsigned nParams() const{
		unsigned n = 0;
		for (unsigned i = 0; i < funcs_.size(); ++i){
			n += std::visit([](auto && f){ return f.n_params; }, funcs_[i]);
		}
		return n;
	}
	
	template<typename FuncType>
	void addFunction(FuncType func, double weight){
		funcs_.push_back(VariantType(func));
		weights_.push_back(weight);
	}

	void renormalizeWeights(){
		double sum = std::accumulate(weights_.begin(), weights_.end(), 0.);
		for (unsigned i = 0; i < weights_.size(); ++i){
			weights_[i] /= sum;
		}
	}

	void setParameters(const double * ptr_w, const double * ptr_par){
		for (unsigned i = 0; i < funcs_.size(); ++i){
			std::visit([ptr_par](auto && f){ f.setParams(ptr_par); }, funcs_[i]);
			weights_[i] = *ptr_w;
			++ptr_w;
			ptr_par += std::visit([](auto && f){ return f.n_params; }, funcs_[i]);
		}
	}
	
	double operator()(double x) const{
		double result = 0;
		for (unsigned i = 0; i < funcs_.size(); ++i){
			result += weights_[i] * std::visit([](auto && f){ return f; }, funcs_[i])(x);
		}
		return result;
	};

	double evalWithParams(double x, const double * ptr_w, const double * ptr_par) const{
		double result = 0;
		for (auto & func : funcs_){
			result += (*ptr_w) * std::visit([ptr_par](auto && f){ return decltype(f)(ptr_par); }, func)(x);
			++ptr_w;
			ptr_par += std::visit([](auto && f){ return f.n_params; }, func);
		}
		return result;
	}
};