#pragma once

#include <array>
#include <vector>
#include <stdexcept>
#include <tuple>
#include <numeric>
#include <utility>


template<typename TupleType>
class MixtureDensity{
private:
	TupleType funcs_;
	std::array<double,std::tuple_size<TupleType>::value> weights_;
public:
	MixtureDensity() {};

	constexpr unsigned nComponents() const{
		return weights_.size();
	}

	constexpr unsigned nParams() const{
		unsigned n = 0;
		std::apply([&n](auto && ...f){ ((n += f.n_params), ...); }, funcs_);
		return n;
	}

	void renormalizeWeights(){
		double sum = std::accumulate(weights_.begin(), weights_.end(), 0.);
		for (auto & w : weights_){
			w /= sum;
		}
	}

	void setWeights(const double * ptr_w){
		for (unsigned i = 0; i < nComponents(); ++i){
			weights_[i] = ptr_w[i];
		}
	}

	void setParameters(const double * ptr_par){
		std::apply(
			[&ptr_par](auto && ...f){
				((f.setParams(ptr_par), ptr_par += f.n_params), ...);
			}, funcs_
		);
	}

	std::vector<double> getWeights() const{
		return std::vector<double>(weights_.begin(), weights_.end());
	}

	std::vector<double> getParameters() const{
		std::vector<double> params;
		params.reserve(nParams());
		std::vector<std::vector<double>> paramVecs;
		paramVecs.reserve(nComponents());
		std::apply(
			[&paramVecs](auto && ...f){
				((paramVecs.push_back(f.getVecParams())), ...);
			}, funcs_
		);
		for (auto & vec : paramVecs){
			for (auto & p : vec){
				params.push_back(p);
			}
		}
		return params;
	}
	
	double operator()(double x) const{
		std::vector<double> evaluations(nComponents());
		unsigned i = 0;
		std::apply(
			[&evaluations, x, &i](auto && ...f){
				((evaluations[i] = f(x), ++i), ...);
			}, funcs_
		);
		return std::inner_product(weights_.begin(), weights_.end(), evaluations.begin(), 0.);
	};

	double evalWithParams(double x, const double * ptr_w, const double * ptr_par) const{
		double result = 0;
		unsigned i = 0;
		std::make_index_sequence<std::tuple_size<TupleType>::value> indices;
		auto compute = [&result, &i, x, ptr_w, ptr_par, this]<size_t ...I>(std::index_sequence<I...>){
			((result += ptr_w[I] * std::get<I>(funcs_)(x, ptr_par+i), i += std::tuple_element<I,TupleType>::type::n_params), ...);
		};
		compute(indices);
		return result;
	}

};


template<typename KernelType>
class HomogeneousMixtureDensity{
private:
	std::vector<KernelType> funcs_;
	std::vector<double> weights_;
public:
	HomogeneousMixtureDensity() {};

	unsigned nComponents() const{
		return weights_.size();
	}

	unsigned nParams() const{
		unsigned n = 0;
		for (auto & f : funcs_){
			n += f.n_params;
		}
		return n;
	}

	template<typename ...Args>
	void addFunction(double w, Args && ...args){
		funcs_.emplace_back(std::forward<Args>(args)...);
		weights_.push_back(w);
	}

	void renormalizeWeights(){
		double sum = std::accumulate(weights_.begin(), weights_.end(), 0.);
		for (auto & w : weights_){
			w /= sum;
		}
	}

	void setWeights(const double * ptr_w){
		for (unsigned i = 0; i < nComponents(); ++i){
			weights_[i] = ptr_w[i];
		}
	}

	void setParameters(const double * ptr_par){
		for (auto & f : funcs_){
			f.setParams(ptr_par);
			ptr_par += f.n_params;
		}
	}

	std::vector<double> getWeights() const{
		return std::vector<double>(weights_.begin(), weights_.end());
	}

	std::vector<double> getParameters() const{
		std::vector<double> params;
		for (auto & f : funcs_){
			auto p = f.getVecParams();
			params.insert(params.end(), p.begin(), p.end());
		}
		return params;
	}
	
	double operator()(double x) const{
		std::vector<double> evaluations(nComponents());
		for (unsigned i = 0; i < nComponents(); ++i){
			evaluations[i] = funcs_[i](x);
		}
		return std::inner_product(weights_.begin(), weights_.end(), evaluations.begin(), 0.);
	};

	double evalWithParams(double x, const double * ptr_w, const double * ptr_par) const{
		double result = 0;
		for (unsigned i = 0; i < nComponents(); ++i){
			result += ptr_w[i] * funcs_[i](x, ptr_par);
			ptr_par += funcs_[i].n_params;
		}
		return result;
	}

};