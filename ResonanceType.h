#ifndef RESONANCE_TYPE_H
#define RESONANCE_TYPE_H
#include "ParticleType.h"

class ResonanceType : public ParticleType
{
public:
//costruttore

ResonanceType(const char * name, double mass, int charge, double width) : ParticleType(name, mass, charge), fWidth(width) {}

// metodi della classe, il getter adesso ritorna anche valori diversi da 0 
//sono anche in questo caso dichiarati const
double GetWidth() const; 
void Print() const;

private: 

//Membro, che viene dichiarato const essendo proprietà
const double fWidth;  

};

#endif
