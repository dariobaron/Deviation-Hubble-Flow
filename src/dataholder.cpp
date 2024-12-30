#include "dataholder.hpp"


PYBIND11_MODULE(dataholder, m) {
	m.doc() = "DataHolder module";

	py::class_<DataHolder>(m, "DataHolder")
		.def(py::init<const np_array<double> &>())
		.def("__len__", &DataHolder::size)
		.def("__iter__", [](const DataHolder & dh) { return py::make_iterator(dh.begin(), dh.end()); }, py::keep_alive<0, 1>())
		.def("__getitem__", [](const DataHolder & dh, unsigned i) {
			np_array<double> ret(3);
			ret.mutable_at(0) = dh[i].rproj;
			ret.mutable_at(1) = dh[i].vlos;
			ret.mutable_at(2) = dh[i].r3d;
			return ret;
		}, py::arg("i"))
	;
}