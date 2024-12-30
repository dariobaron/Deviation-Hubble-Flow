#pragma once

#include "armadillo"
#include "dataholder.hpp"
#include "model.hpp"

////////////
#include <sstream>
////////////


class MaximizeLikelihood{
private:
	DataHolder * holder_;
	Model * model_;
public:
	MaximizeLikelihood(DataHolder * holder, Model * model) : holder_(holder), model_(model) {};
	
	double Evaluate(const arma::mat & x) const{
		/*//////////////
		std::stringstream ss;
		ss << x;
		py::print("\nW = ", ss.str(), py::arg("flush")=true);
		*///////////////
		model_->setParameters(x);
		double result = 0;
		for (auto & data : *holder_){
			/*//////////////////////
			py::print("rproj = ", data.rproj, "\tvproj = ", data.vlos, py::arg("end")="\t");
			*///////////////////////
			auto P = model_->getDensity(data.rproj, data.vlos);
			/*//////////////////////
			py::print("P(r3d) = ", P(data.r3d), py::arg("flush")=true);
			*///////////////////////
			result += std::log(std::max(P(data.r3d),1e-100));
		}
		/*//////////////////////
		py::print("result = ", result, py::arg("flush")=true);
		*///////////////////////
		return -result;
	}
};