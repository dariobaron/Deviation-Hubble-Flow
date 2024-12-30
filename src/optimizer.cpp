#include "optimizer.hpp"


PYBIND11_MODULE(optimizer, m) {
	m.doc() = "Optimizer module";

	py::module_::import("project.lossfunction");

	py::class_<SPSA>(m, "SPSA")
		.def(py::init<>())
		.def("optimize", &SPSA::optimize<MaximizeLikelihood>)
		.def_property("alpha", py::overload_cast<>(&SPSA::alpha, py::const_), py::overload_cast<double>(&SPSA::alpha))
		.def_property("gamma", py::overload_cast<>(&SPSA::gamma, py::const_), py::overload_cast<double>(&SPSA::gamma))
		.def_property("stepSize", py::overload_cast<>(&SPSA::stepSize, py::const_), py::overload_cast<double>(&SPSA::stepSize))
		.def_property("evaluationStepSize", py::overload_cast<>(&SPSA::evaluationStepSize, py::const_), py::overload_cast<double>(&SPSA::evaluationStepSize))
		.def_property("maxIterations", py::overload_cast<>(&SPSA::maxIterations, py::const_), py::overload_cast<size_t>(&SPSA::maxIterations))
		.def_property("tolerance", py::overload_cast<>(&SPSA::tolerance, py::const_), py::overload_cast<double>(&SPSA::tolerance))
	;

	py::class_<SA>(m, "SA")
		.def(py::init<>())
		.def("optimize", &SA::optimize<MaximizeLikelihood>)
		.def_property("maxIterations", py::overload_cast<>(&SA::maxIterations, py::const_), py::overload_cast<unsigned>(&SA::maxIterations))
		.def_property("temperature", py::overload_cast<>(&SA::temperature, py::const_), py::overload_cast<double>(&SA::temperature))
		.def_property("initialMoves", py::overload_cast<>(&SA::initialMoves, py::const_), py::overload_cast<unsigned>(&SA::initialMoves))
		.def_property("moveCtrlSweep", py::overload_cast<>(&SA::moveCtrlSweep, py::const_), py::overload_cast<unsigned>(&SA::moveCtrlSweep))
		.def_property("tolerance", py::overload_cast<>(&SA::tolerance, py::const_), py::overload_cast<double>(&SA::tolerance))
		.def_property("maxToleranceSweep", py::overload_cast<>(&SA::maxToleranceSweep, py::const_), py::overload_cast<unsigned>(&SA::maxToleranceSweep))
		.def_property("maxMoveCoef", py::overload_cast<>(&SA::maxMoveCoef, py::const_), py::overload_cast<double>(&SA::maxMoveCoef))
		.def_property("initMoveCoef", py::overload_cast<>(&SA::initMoveCoef, py::const_), py::overload_cast<double>(&SA::initMoveCoef))
		.def_property("gain", py::overload_cast<>(&SA::gain, py::const_), py::overload_cast<double>(&SA::gain))
	;
}