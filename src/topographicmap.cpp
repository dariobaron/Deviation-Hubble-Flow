#include "topographicmap.hpp"


PYBIND11_MODULE(topographicmap, m) {
	m.doc() = "Topographic map module";

	py::class_<TopographicMap>(m, "TopographicMap")
		.def(py::init<double, double, double, double, unsigned, unsigned>(), py::arg("inf_x"), py::arg("sup_x"), py::arg("inf_y"), py::arg("sup_y"), py::arg("N_x"), py::arg("N_y"))
		.def("__call__", &TopographicMap::call, py::arg("x"), py::arg("y"))
		.def("addFunction", py::overload_cast<double,double,double,double,double>(&TopographicMap::addFunction), py::arg("mu_x"), py::arg("mu_y"), py::arg("sigma_x"), py::arg("sigma_y"), py::arg("rho"))
	;
}