#pragma once

#include <armadillo>
#include "topographicmap.hpp"
#include "mixturedensity.hpp"
#include "kernels.hpp"
#include "typedefs.hpp"
#include "../hyperparameters.hpp"
#include "parameterstransform.hpp"


class Model{
private:
	TopographicMap tm_;
	MixtureDensity<KernelTypeMixture> md_;
	ParametersTransform pt_;
	arma::mat W_;
public:
	Model(double inf_x, double sup_x, double inf_y, double sup_y, unsigned N_x, unsigned N_y) : tm_(inf_x, sup_x, inf_y, sup_y, N_x, N_y), md_(), pt_() {};

	template<typename FuncType>
	void addFunction(const FuncType & f, double weight){
		md_.addFunction(f, weight);
		pt_.addFunction(f);
	}

	void initParameters(const np_array<double> & params){
		W_ = arma::mat(params.data(), params.shape(0), params.shape(1));
	}

	void setParameters(const arma::mat & params) {
		W_ = params;
	}
	void setParameters(const np_array<double> & params) {
		arma::mat p = arma::mat(params.shape(0), params.shape(1));
		for (unsigned i = 0; i < params.shape(0); ++i){
			for (unsigned j = 0; j < params.shape(1); ++j){
				p(i,j) = params.at(i,j);
			}
		}
		W_ = p;
		std::cout << "W_ = " << W_ << std::endl;
	}

	auto getDensity(double rproj, double vlos) {
		//std::vector<double> thetas = arma::conv_to<std::vector<double>>::from(W_ * arma::mat(tm_(rproj, vlos)));
		////////////////////
		arma::colvec phis = arma::mat(tm_(rproj, vlos));
		arma::colvec tmp = W_ * phis;
		std::cout << "tmp = " << tmp << std::endl;
		std::vector<double> thetas(tmp.begin(), tmp.end());
		/*///////////////////
		py::print("phis = ", py::arg("end")=":");
		for (auto phi : phis){
			py::print(phi, py::arg("end")=",");
		}
		py::print(py::arg("flush")=true);
		*///////////////////
		std::cout << "thetas = ";
		for (auto & t : thetas){
			std::cout << t << ",";
		}
		std::cout << std::endl;
		double * ptr = thetas.data();
//		pt_(ptr);
		/*//////////////////
		py::print("thetrans = ", py::arg("end")=":");
		for (auto & t : thetas){
			py::print(t, py::arg("end")=",");
		}
		py::print("\n", py::arg("flush")=true);
		*///////////////////
		md_.setParameters(ptr, ptr+md_.nComponents());
		return md_;
	};
};