#include "ExpSuperpositionDistribution.h"


ExpSuperpositionDistribution::ExpSuperpositionDistribution(const std::vector<double>& coefficients, const std::vector<int> mus)
	: mus_{ mus }
{
	assert(coefficients.size() == mus.size());

	for ( int i{ 0 }; i < mus.size(); ++i ) {
		probabilities_.push_back(coefficients.at(i) / mus.at(i));
	}
}


double ExpSuperpositionDistribution::getValue() const {
	double gamma{ getGamma() };

	double accumulator{ 0.0 };

	for ( int i{ 0 }; i < mus_.size(); ++i ) {
		if ( (accumulator += probabilities_.at(i)) > gamma ) {
			return - std::log(getGamma()) / (mus_.at(i));
		}
	}

	// return last value just in case
	return -1.0 / (*(mus_.rbegin())) * std::log(gamma);

}

