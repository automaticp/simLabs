#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include "DistributionInterface.h"


class ExpSuperpositionDistribution : public DistributionInterface<double> {
private:
	std::vector<int> mus_;
	std::vector<double> probabilities_;

public:
	ExpSuperpositionDistribution(const std::vector<double>& coefficients, const std::vector<int> mus);

	virtual double getValue() const override;

};

