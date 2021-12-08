#pragma once
#include <random>
#include <memory>

class GammaGenerator {
private:
	std::unique_ptr<std::mt19937_64> generator_;
	std::uniform_real_distribution<double> gamma_{ 0.0, 1.0 };

public:
	GammaGenerator();

	double getGamma();
	
};


template <typename T>
class DistributionInterface : protected GammaGenerator {
public:
	virtual T getValue() = 0;

};
