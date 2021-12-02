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
	DiscreteDistribution(const table_t& table) : table_{ table } {}

	
	virtual T getValue() override {
		// why do I need to access getGamma() through 'this'???
		double gamma{ this->getGamma() };
		double accumulator{ 0.0 };
		for ( const typename table_t::value_type& entry : table_ ) {
			
			if ( (accumulator += entry.second) > gamma ) {
				return entry.first;
			}
		}
		
		// in case of floating point error
		// giving sum of probabilities below gamma
		// return last value
		return (table_.rbegin())->first;
	}


};