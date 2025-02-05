#pragma once

#include <vector>
#include "typedefs.hpp"
#include "kernels/gaussian2d.hpp"


class TopographicMap{
private:
	std::vector<Gaussian2D> funcs_;
//	double inf_x_, sup_x_, inf_y_, sup_y_;
public:
	TopographicMap(double inf_x, double sup_x, double inf_y, double sup_y, unsigned N_x, unsigned N_y, double sigma_sep) /*: inf_x_(inf_x), sup_x_(sup_x), inf_y_(inf_y), sup_y_(sup_y)*/ {
		double step_x = (sup_x - inf_x) / N_x;
		double step_y = (sup_y - inf_y) / N_y;
		for (unsigned i = 0; i < N_x; ++i){
			for (unsigned j = 0; j < N_y; ++j){
				funcs_.emplace_back(inf_x + i * step_x, inf_y + j * step_y, step_x*sigma_sep, step_y*sigma_sep, 0);
			}
		}
	};

	TopographicMap(const std::vector<Gaussian2D> & funcs/*, double inf_x, double sup_x, double inf_y, double sup_y*/) : funcs_(funcs)/*, inf_x_(inf_x), sup_x_(sup_x), inf_y_(inf_y), sup_y_(sup_y)*/ {};

	std::vector<double> operator()(double x, double y) const{
		std::vector<double> result(funcs_.size());
		for (unsigned i = 0; i < funcs_.size(); ++i){
			result[i] = funcs_[i](x, y);
		}
		return result;
	}

	np_array<double> call(double x, double y) const{
		np_array<double> result(funcs_.size());
		for (unsigned i = 0; i < funcs_.size(); ++i){
			result.mutable_at(i) = funcs_[i](x, y);
		}
		return result;
	}

	void addFunction(const Gaussian2D & f){
		funcs_.push_back(f);
	}
	
	void addFunction(double mu_x, double mu_y, double sigma_x, double sigma_y, double rho){
		funcs_.emplace_back(mu_x, mu_y, sigma_x, sigma_y, rho);
	}
};