#pragma once
#include <cmath>
#include <array>
#include <algorithm>
#include <iterator>
#include <exception>
#include "ExpDistribution.h"
#include "ComptonDistribution.h"
#include "GaussianDistribution.h"


namespace units {
	const double cm = 1.0;
	const double eMass = 1.0;
}


struct Mu {
	double photoEffect;
	double comptonEffect;
	double pairProduction;
};


class Photon {
public:
	bool isAlive_;
	const bool isDirectedForward_;
	double energy_;
	double z_;

	void move(double dz);
};


class Simulation {
public: 
	using energy_t = double;
	using length_t = double;
private:
	const energy_t initialEnergy_;
	const length_t zMax_;
	
	// reusable distributions
	ExpDistribution expDist_; 
	ComptonDistribution comptonDist_;
	GaussianDistribution gaussDist_;

public:
	Simulation(const energy_t initialEnergy = 8.0 * units::eMass, length_t zMax = 3.0 * units::cm)
		: initialEnergy_{ initialEnergy }, zMax_{ zMax } {}

	// single run that returns total dE with PMT resolution correction
	Simulation::energy_t run();

private:
	energy_t tracePhoton(Photon photon);
	
	energy_t interactPhotoEffect(Photon& photon);
	energy_t interactComptonEffect(Photon& photon);
	energy_t interactPairProduction(Photon& photon);

	bool isPhotonInDetector(const Photon& photon);

	static Mu getLinearCoeffs(energy_t E);
	static energy_t getPMTResolution(energy_t E);
	
};


	
