#pragma once
#include <random>
#include <memory>

class GammaGenerator {
private:
	std::unique_ptr<std::mt19937_64> generator_;
	std::uniform_real_distribution<double> gamma_{ 0.0, 1.0 };

public:
	GammaGenerator() {
		generator_ = std::make_unique<std::mt19937_64>();
	}

	double getGamma() {
		return gamma_(*generator_);
	}

};


template <typename T>
class DistributionInterface : protected GammaGenerator {
public:
	virtual T getValue() = 0;

};
