#include "model.hpp"


PYBIND11_MODULE(model, m) {
	m.doc() = "Model module";

	py::module_::import("project.mixturedensity");
	py::module_::import("project.topographicmap");

	py::class_<Model>(m, "Model")

		.def(py::init<TopographicMap>(), py::arg("topographic_map"))
	
		.def("initParameters", &Model::initParameters)
	
		.def("setParameters", py::overload_cast<const np_array<double>&>(&Model::setParameters))
	
		.def("evalOnInput", &Model::evalOnInput)
	
		.def("evalOnThetas", [](Model & self, const np_array<double> & thetas){
			std::vector<double> thetas_v(thetas.shape(0));
			for (unsigned i = 0; i < thetas.shape(0); ++i){
				thetas_v[i] = thetas.at(i);
			}
			return self.evalOnThetas(thetas_v);
		}, py::arg("thetas"))
	
	;

	py::class_<OtherModel>(m, "OtherModel")

		.def(py::init<TopographicMap,HomogeneousMixtureDensity<KernelTypeHomoMixture>>(), py::arg("topographic_map"), py::arg("mixture_density"))
	
		.def("initParameters", &OtherModel::initParameters)
	
		.def("setParameters", py::overload_cast<const np_array<double>&>(&OtherModel::setParameters))
	
		.def("evalOnInput", &OtherModel::evalOnInput)
	
		.def("evalOnThetas", [](OtherModel & self, const np_array<double> & thetas){
			std::vector<double> thetas_v(thetas.shape(0));
			for (unsigned i = 0; i < thetas.shape(0); ++i){
				thetas_v[i] = thetas.at(i);
			}
			return self.evalOnThetas(thetas_v);
		}, py::arg("thetas"))
	
	;
}