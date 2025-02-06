#pragma once

#include <cmath>
#include <numbers>
#include <stdexcept>
#include <vector>


class Gaussian{
private:
	double mu_;
	double sigma_;
	double Zinv_;
public:
	struct ParamsType{	double mu, sigma;	};
	static constexpr unsigned n_params = 2;
	
	Gaussian(double mu=0, double sigma=1) : mu_(mu), sigma_(std::abs(sigma)), Zinv_(computeZinv(sigma_)) {};

	Gaussian(const double * ptr_params) : Gaussian(ptr_params[0], ptr_params[1]) {};

	Gaussian(const ParamsType & params) : Gaussian(params.mu, params.sigma){};

	void setParams(double mu, double sigma){
		mu_ = mu;
		sigma_ = std::abs(sigma);
		Zinv_ = computeZinv(sigma_);
	}

	void setParams(const double * ptr_params){
		this->setParams(ptr_params[0], ptr_params[1]);
	}

	void setParams(const ParamsType & params){
		this->setParams(params.mu, params.sigma);
	}

	ParamsType getParams() const{
		return {mu_, sigma_};
	}
	std::vector<double> getVecParams() const{
		return {mu_, sigma_};
	}

	double operator()(double x) const {
		return Zinv_ * std::exp(-0.5 * std::pow((x - mu_)/sigma_, 2));
	}

	double operator()(double x, double mu, double sigma) const {
		sigma = std::abs(sigma);
		double Zinv = computeZinv(sigma);
		return Zinv * std::exp(-0.5 * std::pow((x - mu)/sigma, 2));
	}

	double operator()(double x, const double * ptr_params) const {
		return this->operator()(x, ptr_params[0], ptr_params[1]);
	}

	double operator()(double x, const ParamsType & params) const {
		return this->operator()(x, params.mu, params.sigma);
	}

private:
	double computeZinv(double sigma) const{
		return 1 / sigma / std::sqrt(2*std::numbers::pi);
	}
};



class GaussianFixedMean{
private:
	double mu_;
	double sigma_;
	double Zinv_;
public:
	struct ParamsType{	double sigma;	};
	static constexpr unsigned n_params = 1;
	
	GaussianFixedMean(double mu=0, double sigma=1) : mu_(mu), sigma_(std::abs(sigma)), Zinv_(computeZinv(sigma_)) {};

	GaussianFixedMean(const double * ptr_params) : GaussianFixedMean(ptr_params[0]) {};

	GaussianFixedMean(const ParamsType & params) : GaussianFixedMean(params.sigma){};

	void setParams(double sigma){
		sigma_ = std::abs(sigma);
		Zinv_ = computeZinv(sigma_);
	}

	void setParams(const double * ptr_params){
		this->setParams(ptr_params[0]);
	}

	void setParams(const ParamsType & params){
		this->setParams(params.sigma);
	}

	ParamsType getParams() const{
		return {sigma_};
	}
	std::vector<double> getVecParams() const{
		return {sigma_};
	}

	double operator()(double x) const {
		return Zinv_ * std::exp(-0.5 * std::pow((x - mu_)/sigma_, 2));
	}

	double operator()(double x, double sigma) const {
		sigma = std::abs(sigma);
		double Zinv = computeZinv(sigma);
		return Zinv * std::exp(-0.5 * std::pow((x - mu_)/sigma, 2));
	}

	double operator()(double x, const double * ptr_params) const {
		return this->operator()(x, ptr_params[0]);
	}

	double operator()(double x, const ParamsType & params) const {
		return this->operator()(x, params.sigma);
	}

private:
	double computeZinv(double sigma) const{
		return 1 / sigma / std::sqrt(2*std::numbers::pi);
	}
};