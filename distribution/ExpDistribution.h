#pragma once
#include <cmath>
#include "DistributionInterface.h"

// this class was specifically made for task 5
class ExpDistribution : public DistributionInterface<double> {
public:
	double mu_;

public:
	ExpDistribution(double mu = 1.0);

	virtual double getValue() override;

	double getValue(double mu);
	
};


inline ExpDistribution::ExpDistribution(double mu) 
	: mu_{ mu } {}

inline double ExpDistribution::getValue() {
	return -std::log(getGamma()) / mu_;
}

inline double ExpDistribution::getValue(double mu) {
	return -std::log(getGamma()) / mu;
}
