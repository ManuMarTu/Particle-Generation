#ifndef PARTICLE_H
#define PARTICLE_H
#include "ResonanceType.h"
#include <map>
using namespace std;

class Particle 
{
public:
// costruttore, il metodo FindParticle è dichiarato rpivato e scorre sull'array di ParticleType e ritorna l'indice per cui avviene corrispedenza fra nome imput e nome oggetto dell'array
Particle(std::string name, double px = 0, double py = 0, double pz = 0) : fPx(px), fPy(py), fPz(pz), fIParticle(FindParticle(name, true)) {}
    

//Metodi
int GetIParticle() const;
static void AddParticleType(const char*name, double mass, int charge, double width=0);

//2 metodi Setter uno con argomento un intero, e uno con argomento il nome nella particella
void SetIParticle(int i);
void SetIParticle(string name);


static void PrintParticleType();
void PrintParticleInfo() const;

double GetPx() const;
double GetPy() const;
double GetPz() const;
double GetP() const;
double GetMass() const;
double GetEnergy() const;
double InvMass(Particle & p)const ;
int GetCharge() const;
const char*GetName() const;

//metodo che serve per simulare il decadimento di una particella in  2 particelle
void SetP(double px,double py,double pz);
int Decay2Body(Particle &dau1,Particle &dau2) const ;


private:

//Membri

//membro statico che punta al tipo di particella, punta Resonnace Type se width>0
static map<int, map<string,  ParticleType*>>fParticleType;

static int FindParticle(string name, bool errorMessage);

//metodi che segnalano il caso in cui non ci sia corrispondenza
static void ParticleFailure();
static void NumberFailure();
static void TypeFailure();

//variabili dichiarate static che contiene informazioni sui tipi, sul numero e sul massimo numero di tipi di particella generate
static const int fMaxNumParticleType = 10;
static int fNParticleType;
int fIParticle;
// attributi non sono dichiarati const perché variano da particella a particella
  double fPx;   
    double fPy;
    double fPz;

// metodo necessario per mandare in esecuzione il decadimento del metodo pubblico Decay2Body
void Boost(double bx, double by, double bz);


};

#endif
