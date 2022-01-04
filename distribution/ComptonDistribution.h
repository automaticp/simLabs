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

	virtual double getValue() const override;

	void setE(const double E);

private:
	double g(double x) const;

};


