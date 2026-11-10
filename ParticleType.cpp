#ifndef PARTICLETYPE
#define PARTICLETYPE
#include <iostream>
#include "ParticleType.h"
using namespace std;

//dichiaro tutti i metodi del file di intestazione 

void ParticleType::Print() const
{ cout<<"\nParticle name: " << fName << "\nMass: "<< fMass << "\nCharge" << fCharge << "\n";
}
 const char* ParticleType::GetName() const {
     return fName;
 }
 double ParticleType::GetMass() const {
     return fMass;
 }
int ParticleType::GetCharge() const {
    return fCharge;
}
// come detto nel file di intestazione faccio in modo che GetWidth per la particella ritorni 0
double ParticleType:: GetWidth() const {
    return 0;
}

#endif
