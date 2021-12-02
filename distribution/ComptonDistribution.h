#pragma once
#include "DistributionInterface.h"

class ComptonDistribution : public DistributionInterface<double> {
private:
	double E_;
	double minX_;
	double maxEta_;

public:
	// compute and set the normalization coeff here also
	ComptonDistribution(double E = 3.5) 
		: E_{ E }, minX_{ E / (1 + 2 * E) }, maxEta_{g(minX_)} {}

	virtual double getValue() override {
		double xi{}, eta{};
		do {
			// xi could be incorrect
			xi = getGamma() * (E_ - minX_) + minX_;
			// eta as well
			eta = getGamma() * maxEta_;
		} while ( eta >= g(xi) );
		
		return xi;
	}

	
	void setE(const double E) {
		E_ = E;
		minX_ = E / (1 + 2 * E);
		maxEta_ = g(minX_);
	}

private:
	double g(double x) {
		return x / E_ + E_ / x + (1 / E_ - 1 / x) * (2 + 1 / E_ - 1 / x);
	}

};