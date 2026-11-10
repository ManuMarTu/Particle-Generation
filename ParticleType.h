#ifndef PARTICLETYPE_H
#define PARTICLETYPE_H

class ParticleType
{
 public:
  // costruttore   

 ParticleType(const char*name, double mass, int charge) : fName(name), fMass(mass), fCharge(charge){}

// metodi pubblici dichiarati const peché non possono variare una volta creata l'istanza, viene dichiarato pure width e reso virtual perché per la particella di questa tipologia  sarà sempre uguale a 0
// viene dichiarato pure il metodo che ritorna la larghezza per implementare il metodo Decay2Body, viene comunque reso virtuale e fornisce sempre 0   

   virtual void Print() const;
   const char* GetName() const;
   double GetMass() const;
   int GetCharge() const;
   virtual double GetWidth() const;
 

 private:
// le proprietà della particella sono dichiarati const perché la definiscono
   const char*fName;
   const double fMass;
   const int fCharge;

};
#endif




