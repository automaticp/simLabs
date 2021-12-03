#include "Simulation.h"


void Photon::move(double dz) {
	z_ += dz * (isDirectedForward_ ? 1.0 : -1.0);
}


Simulation::energy_t Simulation::run() {

	energy_t dE{ tracePhoton({true, true, initialEnergy_, 0.0}) };
	
	// apply PMT noise
	gaussDist_.mu_ = dE;
	gaussDist_.sigma_ = getPMTResolution(dE);
	dE = gaussDist_.getValue();
	
	return dE;
}


Simulation::energy_t Simulation::tracePhoton(Photon photon) {
	energy_t dE{ 0.0 };
	
	// this is ugly af, but i'd rather already get it working
	while ( photon.isAlive_ ) {
		Mu mu{ getLinearCoeffs(photon.energy_) };

		length_t zPE = expDist_.getValue(mu.photoEffect);
		length_t zCE = expDist_.getValue(mu.comptonEffect);
		length_t zPP = expDist_.getValue(mu.pairProduction);
		
		if ( zPP < zPE && zPP < zCE && photon.energy_ >= 2.0 * units::eMass ) {
			// case for pair production
			photon.move(zPP);
			if ( isPhotonInDetector(photon) ) {
				dE += interactPairProduction(photon);
			}
			else {
				photon.isAlive_ = false;
			}
		
		}
		else {
			// cases for photo and compton effect
			if ( zPE < zCE ) {
				// case for photo
				photon.move(zPE);

				if ( isPhotonInDetector(photon) ) {
					dE += interactPhotoEffect(photon);
				}
				else {
					photon.isAlive_ = false;
				}
			}
			else {
				// case for compton
				photon.move(zCE);

				if ( isPhotonInDetector(photon) ) {
					dE += interactComptonEffect(photon);
				}
				else {
					photon.isAlive_ = false;
				}
			}
		}
	}
	
	return dE;
}


Simulation::energy_t Simulation::interactPhotoEffect(Photon& photon) {
	photon.isAlive_ = false;
	return photon.energy_;
}


Simulation::energy_t Simulation::interactComptonEffect(Photon& photon) {
	comptonDist_.setE(photon.energy_);
	energy_t dE{ photon.energy_ - comptonDist_.getValue() };
	photon.energy_ -= dE;
	return dE;
}


Simulation::energy_t Simulation::interactPairProduction(Photon& photon) {
	// original photon loses 2*eMass; electron and positron carry (E - 2) kinetic energy
	// and lose it all. dE = E - 2.
	energy_t dE{ photon.energy_ - 2.0 * units::eMass };
	// positron annihilates, total energy from this is 2*eMass
	// create and trace 2 photons: 1 forwards and 1 backwards
	dE += tracePhoton({ true, true, 1.0 * units::eMass, photon.z_ });
	dE += tracePhoton({ true, false, 1.0 * units::eMass, photon.z_ });
	photon.isAlive_ = false;
	return dE;
}


bool Simulation::isPhotonInDetector(const Photon& photon) {
		return (photon.z_ >= 0.0) && (photon.z_ <= zMax_);
}


Mu Simulation::getLinearCoeffs(energy_t E) {
	return {
		0.1 / E * units::eMass,
		0.05 * E * units::eMass,
		(E >= 2.0 * units::eMass) ? 0.03 * (E - 2.0 * units::eMass) : 0.0 
	};
}


Simulation::energy_t Simulation::getPMTResolution(energy_t E) { 
	return 0.1 * std::sqrt(E * units::eMass ); 
}




