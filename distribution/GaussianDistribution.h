#pragma once
#include <cmath>
#include "DistributionInterface.h"


class GaussianDistribution : public DistributionInterface<double> {
public:
	double mu_, sigma_;

	GaussianDistribution(double mu = 0.0, double sigma = 1.0);


public:
	virtual double getValue() const override;

};

