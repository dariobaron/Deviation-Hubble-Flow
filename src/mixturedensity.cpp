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

		.def("addGaussian", [](MixtureDensity<KernelTypeMixture> & self, double mu, double sigma, double weight){
			self.addFunction(Gaussian(mu, sigma), weight);
		}, py::arg("mu"), py::arg("sigma"), py::arg("weight"))

		.def("setParams", [](MixtureDensity<KernelTypeMixture> & self, const np_array<double> & params){
			if (params.shape(0) != self.nParams() + self.nComponents()){
				throw std::runtime_error("The number of parameters must be " + std::to_string(self.nParams()) );
			}
			for (unsigned i = 0; i < self.nComponents(); ++i){
				if (params.at(i) <= 0){
					throw std::runtime_error("The weights must be positive");
				}
			}
			self.setParameters(params.data(), params.data()+self.nComponents());
		}, py::arg("params"))

		.def("renormalizeWeights", &MixtureDensity<KernelTypeMixture>::renormalizeWeights)
		
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
}