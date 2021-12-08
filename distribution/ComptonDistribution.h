#pragma once
#include "DistributionInterface.h"

class ComptonDistribution : public DistributionInterface<double> {
private:
	double E_;
	double minX_;
	double maxEta_;

public:
	// compute and set the normalization coeff here also
	ComptonDistribution(double E = 3.5);

	virtual double getValue() override;

	void setE(const double E);

private:
	double g(double x);

};


inline ComptonDistribution::ComptonDistribution(double E) 
	: E_{ E }, minX_{ E / (1 + 2 * E) }, maxEta_{g(minX_)} {}


inline double ComptonDistribution::getValue() {
	double xi{}, eta{};
	do {
		// xi could be incorrect
		xi = getGamma() * (E_ - minX_) + minX_;
		// eta as well
		eta = getGamma() * maxEta_;
	} while ( eta >= g(xi) );
	
	return xi;
}


inline void ComptonDistribution::setE(const double E) {
	E_ = E;
	minX_ = E / (1 + 2 * E);
	maxEta_ = g(minX_);
}


inline double ComptonDistribution::g(double x) {
	return x / E_ + E_ / x + (1 / E_ - 1 / x) * (2 + 1 / E_ - 1 / x);
}


