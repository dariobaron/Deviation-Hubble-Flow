#pragma once

#include <tuple>
#include "src/kernels.hpp"

using KernelTypeKDE = Gaussian;

//using KernelTypeMixture = std::variant<Gaussian>;
//constexpr unsigned NComponentsMixture = 3;

using KernelTypeMixture = std::tuple<Rayleigh, Gaussian, Gaussian>;