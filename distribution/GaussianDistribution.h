#pragma once
#include <cmath>
#include "DistributionInterface.h"


class GaussianDistribution : public DistributionInterface<double> {
public:
	double mu_, sigma_;

	GaussianDistribution(double mu = 0.0, double sigma = 1.0) 
		: mu_{ mu }, sigma_{ sigma } {}


public:
	virtual double getValue() override {
		double gamma1{ getGamma() };
		double gamma2{ getGamma() };
		// kek, I don't remember where PI is in the STL
		static const double pi{ std::acos(-1) }; // this will do
		double xi{ mu_ + sigma_ * std::sqrt(-2 * std::log(gamma1)) * std::cos(2 * pi * gamma2) };
		return xi;
	}

};