#include "ExpDistribution.h"


ExpDistribution::ExpDistribution(double mu) 
	: mu_{ mu } {}

double ExpDistribution::getValue() const {
	return -std::log(getGamma()) / mu_;
}

double ExpDistribution::getValue(double mu) {
	return -std::log(getGamma()) / mu;
}
