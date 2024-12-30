#pragma once

#include <variant>
#include "src/kernels.hpp"

using KernelTypeKDE = Gaussian;

using KernelTypeMixture = std::variant<Gaussian>;
constexpr unsigned NComponentsMixture = 3;
