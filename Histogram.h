#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "DistributionInterface.h"

template <typename T>
class Histogram {
private:
	std::vector<T> data_{};
	std::vector<double> binEdges_{};
	std::vector<size_t> counts_{};
	const size_t canvasHeight_{ 64 };

public:
	Histogram() {}

	Histogram(const std::vector<T>& data, const std::vector<double> binEdges) 
		: data_{ data }, binEdges_{ binEdges } {}

	void setData(const std::vector<T>& data) { data_ = data; }
	void setBinEdges(const std::vector<double> binEdges) { binEdges_ = binEdges; }
	const std::vector<T>& getData() const { return data_; }
	const std::vector<double>& getBinEdges() const { return binEdges_; }

	void reserve(size_t size) { data_.reserve(size);}
	void fill(T entry) { data_.push_back(entry); }

	void fillFromDistribution(DistributionInterface<T>& dist, size_t sampleSize) {
		reserve(sampleSize);
		for ( size_t i{ 0 }; i < sampleSize; ++i ) {
			fill(dist.getValue());
		}
	}

	void compute();

	const std::vector<size_t>& getCounts() const { return counts_; }
	const std::vector<size_t>& computeAndGetCounts() {
		compute();
		return counts_;
	}
	
	void draw(bool normalize = false); 
	void computeAndDraw(bool normalize = false) {
		compute();
		draw(normalize);
	}

};


template <typename T>
void Histogram<T>::compute() {
	assert(binEdges_.size() > 0);

	counts_.resize((binEdges_.size() - 1), 0);
	for ( auto value : data_ ) {

		for ( size_t i{ 0 }; i < (binEdges_.size() - 1); ++i ) {
			if ( value >= binEdges_.at(i) && value < binEdges_.at(i + 1) ) {
				++(counts_.at(i));
			}
		}
	
	}
}


template <typename T>
void Histogram<T>::draw(bool normalize) {
	// it's a mess, sorry
	constexpr char fillChar{ '#' };
	constexpr size_t valueHeight{ 18 };

	auto maxHeight{ *std::max_element(counts_.cbegin(), counts_.cend()) };
	double multiplier{ 1.0 };
	
	std::string histHead{ "Histogram" };
	std::string countsHead{ normalize ? "Probability:" : "Counts:" };
	
	if ( maxHeight > canvasHeight_ ) {
		multiplier = static_cast<double>(canvasHeight_) / maxHeight;
		histHead += " (approximate)";
	}
	histHead += ":";

	std::cout << std::left << std::setw(canvasHeight_) << histHead << '|' << std::setw(valueHeight + 1) << "Bin:" << '|' << countsHead << '\n';
	
	size_t i{ 0 };
	for ( size_t count : counts_ ) {
		
		size_t height{ static_cast<size_t>((count * multiplier) + 0.5) };
		std::string bar(height, fillChar);
		
		std::cout << std::left
			<< std::setw(canvasHeight_) << bar << '|'
			<< '[' << std::left << std::setw(valueHeight / 2 - 1) << binEdges_.at(i) << ','
			<< std::right << std::setw(valueHeight / 2 - 1) << binEdges_.at(i + 1) << ')' << '|'
			<< (normalize ? static_cast<double>(count) / data_.size() : static_cast<double>(count))
			<< '\n';
		
		++i;
	}

}