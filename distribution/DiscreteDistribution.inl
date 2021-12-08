#include "DiscreteDistribution.h"

	
template <typename T>
inline DiscreteDistribution<T>::DiscreteDistribution(const table_t& table) 
	: table_{ table } {}
	

template <typename T>
inline T DiscreteDistribution<T>::getValue() {
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
