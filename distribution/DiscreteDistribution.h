#pragma once
#include <map>
#include <functional>
#include "DistributionInterface.h"


template <typename T>
class DiscreteDistribution : public DistributionInterface<T> {
public:
	using probability_t = double;
	using table_t = std::map<T, probability_t, std::greater<probability_t>>;
private:
	table_t table_;

public:
	DiscreteDistribution(const table_t& table);

	virtual T getValue() const override;

};


// there's gotta be a better way
#include "DiscreteDistribution.inl"
	

	
