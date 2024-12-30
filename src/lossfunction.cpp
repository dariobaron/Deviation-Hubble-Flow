#include "lossfunction.hpp"
#include "typedefs.hpp"


PYBIND11_MODULE(lossfunction, m) {
	m.doc() = "Loss function module";

	py::module_::import("project.model");
	py::module_::import("project.dataholder");

	py::class_<MaximizeLikelihood>(m, "MaximizeLikelihood")
		.def(py::init<DataHolder*, Model*>())
		.def("Evaluate", &MaximizeLikelihood::Evaluate)
	;
}