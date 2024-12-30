#pragma once

#include <cmath>
#include <numbers>


class Gaussian{
private:
	double mu_;
	double sigma_;
	double Zinv_;
public:
	struct ParamsType{	double mu, sigma;	};
	static constexpr unsigned n_params = 2;
	
	Gaussian(double mu=0, double sigma=1) : mu_(mu), sigma_(std::abs(sigma)), Zinv_(1/sigma/std::sqrt(2*std::numbers::pi)) {};

	Gaussian(const double * ptr_params) : Gaussian(ptr_params[0], ptr_params[1]) {};

	Gaussian(const ParamsType & params) : Gaussian(params.mu, params.sigma){};

	void setParams(double mu, double sigma){
		mu_ = mu;
		sigma_ = std::abs(sigma);
		Zinv_ = 1/sigma_/std::sqrt(2*std::numbers::pi);
	}

	void setParams(const double * ptr_params){
		this->setParams(ptr_params[0], ptr_params[1]);
	}

	void setParams(const ParamsType & params){
		this->setParams(params.mu, params.sigma);
	}

	double operator()(double x) const {
		return Zinv_ * std::exp(-0.5 * std::pow((x - mu_)/sigma_, 2));
	}

	double operator()(double x, double mu, double sigma) const {
		sigma = std::abs(sigma);
		return 1 / sigma / std::sqrt(2*std::numbers::pi) * std::exp(-0.5 * std::pow((x - mu)/sigma, 2));
	}

	double operator()(double x, const double * ptr_params) const {
		return this->operator()(x, ptr_params[0], ptr_params[1]);
	}

	double operator()(double x, const ParamsType & params) const {
		return this->operator()(x, params.mu, params.sigma);
	}
};