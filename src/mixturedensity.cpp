#include "mixturedensity.hpp"
#include <stdexcept>
#include "typedefs.hpp"
#include "../hyperparameters.hpp"
#include "kernels.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mixturedensity, m){
	py::class_<MixtureDensity<KernelTypeMixture>>(m, "MixtureDensity")
		
		.def(py::init<>())

		.def("nComponents", &MixtureDensity<KernelTypeMixture>::nComponents)

		.def("nParams", &MixtureDensity<KernelTypeMixture>::nParams)

		.def("setParams", [](MixtureDensity<KernelTypeMixture> & self, const np_array<double> & params){
			if (params.shape(0) != self.nParams() + self.nComponents()){
				throw std::runtime_error("The number of parameters must be " + std::to_string(self.nParams()) );
			}
			for (unsigned i = 0; i < self.nComponents(); ++i){
				if (params.at(i) <= 0){
					throw std::runtime_error("The weights must be positive");
				}
			}
			self.setWeights(params.data());
			self.renormalizeWeights();
			self.setParameters(params.data()+self.nComponents());
		}, py::arg("params"))

		.def("getParams", [](const MixtureDensity<KernelTypeMixture> & self){
			np_array<double> params(self.nComponents()+self.nParams());
			unsigned i = 0;
			for (auto & w : self.getWeights()){
				params.mutable_at(i) = w;
				++i;
			}
			for (auto & p : self.getParameters()){
				params.mutable_at(i) = p;
				++i;
			}
			return params;
		})

		.def("__call__", py::vectorize(&MixtureDensity<KernelTypeMixture>::operator()), py::arg("x"))
		
		.def("evalWithParams", [](const MixtureDensity<KernelTypeMixture> & self, double x, const np_array<double> & params){
			if (params.shape(0) != self.nParams() + self.nComponents()){
				throw std::runtime_error("The number of parameters must be " + std::to_string(self.nParams()) );
			}
			for (unsigned i = 0; i < self.nComponents(); ++i){
				if (params.at(i) <= 0){
					throw std::runtime_error("The weights must be positive");
				}
			}
			return self.evalWithParams(x, params.data(), params.data()+self.nComponents());
		}, py::arg("x"), py::arg("params"))

	;



	py::class_<HomogeneousMixtureDensity<KernelTypeHomoMixture>>(m, "HomogeneousMixtureDensity")
		
		.def(py::init<>())

		.def("nComponents", &HomogeneousMixtureDensity<KernelTypeHomoMixture>::nComponents)

		.def("nParams", &HomogeneousMixtureDensity<KernelTypeHomoMixture>::nParams)

		.def("addGaussian", &HomogeneousMixtureDensity<KernelTypeHomoMixture>::addFunction<double,double>, py::arg("w"), py::arg("mu"), py::arg("sigma"))

		.def("setParams", [](HomogeneousMixtureDensity<KernelTypeHomoMixture> & self, const np_array<double> & params){
			if (params.shape(0) != self.nParams() + self.nComponents()){
				throw std::runtime_error("The number of parameters must be " + std::to_string(self.nParams()) );
			}
			for (unsigned i = 0; i < self.nComponents(); ++i){
				if (params.at(i) <= 0){
					throw std::runtime_error("The weights must be positive");
				}
			}
			self.setWeights(params.data());
			self.renormalizeWeights();
			self.setParameters(params.data()+self.nComponents());
		}, py::arg("params"))

		.def("getParams", [](const HomogeneousMixtureDensity<KernelTypeHomoMixture> & self){
			np_array<double> params(self.nComponents()+self.nParams());
			unsigned i = 0;
			for (auto & w : self.getWeights()){
				params.mutable_at(i) = w;
				++i;
			}
			for (auto & p : self.getParameters()){
				params.mutable_at(i) = p;
				++i;
			}
			return params;
		})

		.def("__call__", py::vectorize(&HomogeneousMixtureDensity<KernelTypeHomoMixture>::operator()), py::arg("x"))
		
		.def("evalWithParams", [](const HomogeneousMixtureDensity<KernelTypeHomoMixture> & self, double x, const np_array<double> & params){
			if (params.shape(0) != self.nParams() + self.nComponents()){
				throw std::runtime_error("The number of parameters must be " + std::to_string(self.nParams()) );
			}
			for (unsigned i = 0; i < self.nComponents(); ++i){
				if (params.at(i) <= 0){
					throw std::runtime_error("The weights must be positive");
				}
			}
			return self.evalWithParams(x, params.data(), params.data()+self.nComponents());
		}, py::arg("x"), py::arg("params"))

	;
}