cmake_minimum_required (VERSION 3.16...3.22)

project (simLabs)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_executable (SimulationLabs "main.cpp"  "DistributionInterface.h" "DiscreteDistribution.h" "Histogram.h"
        "ExpSuperpositionDistribution.h" "GaussianDistribution.h" "ComptonDistribution.h" "Geant5.h" "ExpDistribution.h")

