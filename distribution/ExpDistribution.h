#pragma once
#include <cmath>
#include "DistributionInterface.h"

// this class was specifically made for task 5
class ExpDistribution : public DistributionInterface<double> {
public:
	double mu_;

public:
	ExpDistribution(double mu = 1.0) : mu_{ mu } {}

	virtual double getValue() override {
		return -std::log(getGamma()) / mu_;
	}

	double getValue(double mu) {
		return -std::log(getGamma()) / mu;
	}

};