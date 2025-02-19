#include "kerneldensityestimation.hpp"
#include "typedefs.hpp"
#include "../hyperparameters.hpp"
#include "kernels.hpp"

namespace py = pybind11;

PYBIND11_MODULE(kerneldensityestimation, m) {
	py::class_<KernelDensityEstimation<KernelTypeKDE>>(m, "KernelDensityEstimation")
		.def(py::init([](const np_array<double> & values, double bandwidth=1, double a=-infinity, double b=infinity){
			const double * ptr = values.data();
			size_t N = values.size();
			return KernelDensityEstimation<KernelTypeKDE>(ptr, N, bandwidth, a, b);
		}))
		.def("__call__", py::vectorize(&KernelDensityEstimation<KernelTypeKDE>::operator()));
}