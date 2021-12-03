#include <iostream>
#include <vector>
#include <cassert>
#include "DiscreteDistribution.h"
#include "ExpSuperpositionDistribution.h"
#include "GaussianDistribution.h"
#include "ComptonDistribution.h"
#define  HISTOGRAM_IMPLEMENTATION
#include "Histogram.h"
#include "Simulation.h"


std::vector<double> poorRange(double a, double b, double step = 1.0) {
	assert(b > a);
	std::vector<double> vec{};
	size_t length{ static_cast<size_t>((b - a) / step) };
	vec.reserve(length);
	for ( size_t i{ 0 }; i <= length; ++i ) {
		vec.push_back(a + i * step);
	}
	return vec;
}


template <typename T>
void drawDistribution(DistributionInterface<T>& dist, 
					  const std::vector<double>& binEdges, 
					  size_t sampleSize, bool normalized = false) {
	assert(!binEdges.empty());
	Histogram<T> hist;
	hist.setBinEdges(binEdges);
	hist.fillFromDistribution(dist, sampleSize);
	hist.computeAndDraw(normalized);
}


void drawSimRunDistribution(Simulation& sim,
							const std::vector<double>& binEdges,
							size_t sampleSize, bool normalized = false) {
	assert(!binEdges.empty());
	Histogram<double> hist;
	hist.setBinEdges(binEdges);
	hist.reserve(sampleSize);
	for ( size_t i{0}; i < sampleSize; ++i ) {
		hist.fill(sim.run());
	}
	hist.computeAndDraw(normalized);
}


int main() {
	
	constexpr size_t defSample{ 100000 };

	DiscreteDistribution<int> dist1({ {2, 3. / 8.}, {0, 1. / 3.}, {1, 1. / 6.}, {3, 1. / 8.} });
	drawDistribution(dist1, poorRange(-0.5, 3.5), defSample, true);

	ExpSuperpositionDistribution dist2({ 1. / 2, 3. / 2, 1.0 }, { 2, 3, 4 });
	drawDistribution(dist2, poorRange(0.0, 2.0, 0.05), defSample);

	GaussianDistribution dist3(2.0, 2.0);
	drawDistribution(dist3, poorRange(-10.0, 10.0, 0.5), defSample, true);

	ComptonDistribution dist4(3.5);
	drawDistribution(dist4, poorRange(0.0, 4.0, 0.1), defSample);

	Simulation sim(8.0 * units::eMass, 3.0 * units::cm);
	drawSimRunDistribution(sim, poorRange(-0.1, 8.9, 0.2), defSample);


	return 0;
}
