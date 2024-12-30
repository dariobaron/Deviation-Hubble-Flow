#include "model.hpp"


PYBIND11_MODULE(model, m) {
	m.doc() = "Model module";

	py::module_::import("project.mixturedensity");
	py::module_::import("project.topographicmap");

	py::class_<Model>(m, "Model")
		.def(py::init<double, double, double, double, unsigned, unsigned>(), py::arg("inf_x"), py::arg("sup_x"), py::arg("inf_y"), py::arg("sup_y"), py::arg("N_x"), py::arg("N_y"))
		.def("addGaussian", [](Model & m, double mu, double sigma, double weight){
				m.addFunction(Gaussian(mu, sigma), weight);
			}, py::arg("mu"), py::arg("sigma"), py::arg("weight")
		)
		.def("initParameters", &Model::initParameters)
		.def("setParameters", py::overload_cast<const np_array<double>&>(&Model::setParameters))
		.def("getDensity", &Model::getDensity)
	;
}