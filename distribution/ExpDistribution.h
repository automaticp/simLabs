#pragma once
#include <cmath>
#include "DistributionInterface.h"


class ExpDistribution : public DistributionInterface<double> {
public:
	double mu_;

public:
	ExpDistribution(double mu = 1.0);

	virtual double getValue() const override;

	double getValue(double mu);
	
};
