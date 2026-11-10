#ifndef PARTICLE
#define PARTICLE
#include<iostream>
#include "Particle.h"
#include <map>
#include <cmath>  // for M_PI
#include <cstdlib> //for RAND_MAX
using namespace std;

//dichiaro tutti i metodi del file di intestazione



int Particle::fNParticleType = 0;

//se non ci sono errori il metodo aggiunge una particella all'array, se la larghezza è 0 a ParticleType se diversa da 0 a ResonanceType

map<int, map<string, ParticleType*>> Particle :: fParticleType;

// dichiaro il metodo che cerca corrispondenza tra il nome di input della particella e quello di ParticleType, scorrendo tra gli elementi dell'array 
void Particle::AddParticleType(const char*name, double mass, int charge, double width) {
    if(FindParticle(name, false) != -1)
       TypeFailure();
    else if (fNParticleType > fMaxNumParticleType)      
       NumberFailure();
    else{
        map<string, ParticleType*>particle;
        if (width > 0)
        particle.insert (pair<string, ParticleType*>(name, new ResonanceType(name, mass, charge, width)));
        else //(width<0)
        particle.insert(pair<string, ParticleType*>(name, new ParticleType(name, mass, charge) ));    
        fParticleType.insert(pair<int, map<string, ParticleType *>>(fNParticleType, particle));
      fNParticleType++;
        }   
}

int Particle::FindParticle(string name, bool errorMessage)
{
    for (auto i : fParticleType)
    {
        for (auto j : i.second)
        {
            if (j.first == name)
            return i.first;
        }
    }
    if (errorMessage)
    
        ParticleFailure();
        return -1 ;
   
}
// metodi per trasformare i nomi delle particelle in indici numerici
void Particle::SetIParticle(int i)
{
 bool found = false;
    for (auto n : fParticleType)
    {
        if (n.first == i)
        {
            found = true;
            fIParticle = i;
        }
    }
    if (found == false)
    {
        ParticleFailure();
        fIParticle = -1;
    }
}
void Particle::SetIParticle(std::string name)
{
    fIParticle = FindParticle(name, true);
}


// metodo che stampa le informazioni sulla particella 
void Particle::PrintParticleInfo() const
{
    cout<<"\nParticles Index "<< fIParticle << " : " << (*(fParticleType[fIParticle].begin())).first << " Px = " << fPx << " Py = " << fPy << " Pz = " << fPz << "\n";
}

// metodo che stampa il tipo di particella
void Particle::PrintParticleType()
{
    cout<<"\nParticles Type\n";
    for (auto i : fParticleType)
    {
        for (auto j : i.second)
        {
            j.second->Print();
        }
    }
}

// metodi che stampano gli errori 

void Particle:: ParticleFailure()
{
    cout<< "NO Particles with the name\n";
}
void Particle:: NumberFailure()
{
    cout<< "Too many Particles\n";
}
void Particle:: TypeFailure()
{
    cout<<"Particle already in \n";
}



// metodi che ritornano le componenti dell'impulso, l'impulso, l'energia e la masas invariante
int Particle::GetIParticle() const
{
    return fIParticle;
}
double Particle:: GetPx() const
{
    return fPx;
}
double Particle:: GetPy() const
{
    return fPy;
}
double Particle:: GetPz() const
{
    return fPz;
}
double Particle:: GetP() const
{
    return sqrt(fPx*fPx + fPy*fPy + fPz*fPz);
}

const char * Particle::GetName() const
{
    return (*(fParticleType[fIParticle].begin())).second->GetName();
}
double Particle:: GetMass() const
{
    return(*(fParticleType[fIParticle].begin())).second->GetMass();
}
int Particle::GetCharge() const
{
    return (*(fParticleType[fIParticle].begin())).second->GetCharge();
}

double Particle:: GetEnergy() const
{
    return sqrt(GetMass()*GetMass() + (fPx*fPx + fPy*fPy + fPz*fPz));
}

double Particle:: InvMass(Particle & p) const
{
    return sqrt(pow(GetEnergy() + p.GetEnergy(), 2) - (fPx + p.GetPx()) * (fPx + p.GetPx()) - (fPy + p.GetPy()) * (fPy + p.GetPy()) - (fPz + p.GetPz()) * (fPz + p.GetPz()));
}






void Particle::SetP(double px, double py, double pz)
{   fPx=px;
    fPy=py;
    fPz=pz;
}





int Particle::Decay2Body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIParticle > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1, y2;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    massMot += (*(fParticleType[fIParticle].begin())).second->GetWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx*fPx + fPy*fPy + fPz*fPz + massMot*massMot);

  double bx = fPx/energy;
  double by = fPy/energy;
  double bz = fPz/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx + by*fPy + bz*fPz;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx += gamma2*bp*bx + gamma*bx*energy;
  fPy += gamma2*bp*by + gamma*by*energy;
  fPz += gamma2*bp*bz + gamma*bz*energy;
}

#endif
