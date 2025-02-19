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
	ParametersTransform<KernelTypeMixture> pt_;
	arma::mat W_;
public:
	Model(TopographicMap tm) : tm_(tm), md_(), pt_() {};

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
	}

	auto evalOnThetas(std::vector<double> thetas) {
		double * ptr = thetas.data();
		pt_(ptr);
		md_.setWeights(ptr);
		md_.setParameters(ptr+md_.nComponents());
		return md_;
	};

	auto evalOnInput(double rproj, double vlos) {
		arma::colvec thetas_tmp = W_ * arma::mat(tm_(rproj, vlos));
		std::vector<double> thetas(thetas_tmp.begin(), thetas_tmp.end());
		return evalOnThetas(thetas);
	};
};