#include "ComptonDistribution.h"


ComptonDistribution::ComptonDistribution(double E) 
	: E_{ E }, minX_{ E / (1 + 2 * E) }, maxEta_{g(minX_)} {}


double ComptonDistribution::getValue() {
	double xi{}, eta{};
	do {
		// xi could be incorrect
		xi = getGamma() * (E_ - minX_) + minX_;
		// eta as well
		eta = getGamma() * maxEta_;
	} while ( eta >= g(xi) );
	
	return xi;
}


void ComptonDistribution::setE(const double E) {
	E_ = E;
	minX_ = E / (1 + 2 * E);
	maxEta_ = g(minX_);
}


double ComptonDistribution::g(double x) {
	return x / E_ + E_ / x + (1 / E_ - 1 / x) * (2 + 1 / E_ - 1 / x);
}


