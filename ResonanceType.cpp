#ifndef RESONANCE_TYPE
#define RESONANCE_TYPE
#include "ResonanceType.h"
#include <iostream>
using namespace std;

//dichiaro tutti i metodi del file di intestazione
double ResonanceType::GetWidth()const
{
    return fWidth;
}

void ResonanceType::Print() const
{ 
cout<<"\nParticleName: "<< GetName() << "\nMass: " << GetMass() << "\nCharge: " << GetCharge() << "\nWidth: " << GetWidth() << "\n";

}


#endif


