#include "ParticleType.h"
#include "ResonanceType.h"
#include "Particle.h"
#include <iostream>
#include "TRandom.h"
#include "TFile.h"
#include "TH1F.h"
#include "TBenchmark.h"
#include <vector>
using namespace std;

int GenerateParticles(int n= 100000)
{
    gBenchmark->Start("Time to execute");

//viene creato un file root su cui salvare le particelle generate    
    TFile *file = new TFile("particlesinfo.root","RECREATE");

//vengono aggiunti, col metodo AddParticleType, 7 tipi di particelle, di cui vengono dichiarati nome, massa, e carica. Solo per K* anche la larghezza

Particle::AddParticleType ("pi+", 0.13957, +1);
Particle::AddParticleType ("pi-", 0.13957, -1);
Particle::AddParticleType ("K+", 0.49367, +1);
Particle::AddParticleType ("K-", 0.49367, -1);
Particle::AddParticleType ("P+", 0.93827, +1);
Particle::AddParticleType ("P-", 0.93827, -1);
Particle::AddParticleType ("K*", 0.89166, 0, 0.050);
vector<Particle> particles;
vector<Particle> resonanceParticles;


// sono definiti 11 istogrammi 1-D

TH1F *h_ParticleType = new TH1F("h_ParticleType", "Particle distribution", 7, 0., 7.);
TH1F *h_PolarAngle = new TH1F("h_PolarAngle", "Polar angle distribution", 250, 0, M_PI);
TH1F *h_AzimuthAngle = new TH1F("h_AzimuthAngle", "Azimuthal Angle distribution", 500, 0, 2*M_PI);
TH1F *h_Momentum = new TH1F("h_Momentum", "Momentum distribution", 1000, 0., 5.);
TH1F *h_TransverseMomentum = new TH1F("h_TransverseMomentum", "Trasverse Momentum distribution", 1000 , 0., 5.);
TH1F *h_Energy = new TH1F("h_Energy", "Energy distribution", 1000, 0, 4);
TH1F *h_DiscordInvMass = new TH1F("h_DiscordInvMass", "Invariant Mass of discordant particles distribution", 1000, 0., 5.);
TH1F *h_ConcordInvMass = new TH1F("h_ConcordInvMass", "Invariant Mass of concordant particles distribution", 1000, 0., 5.);
TH1F *h_piKDiscordInvMass = new TH1F("h_piKDiscordInvMass", "Invariant Mass of discordant particles pi and K distribution", 1000, 0., 5.);
TH1F *h_piKConcordInvMass = new TH1F("h_piKConcordInvMass", "Invariant Mass of concordant particles pi and K distribution", 1000, 0., 5.);
TH1F *h_ResInvMass = new TH1F("h_ResInvMass", "Invariant Mass of K*resonance distribution", 200, 0.5, 1.5);

h_DiscordInvMass->Sumw2();
h_ConcordInvMass->Sumw2();
h_piKDiscordInvMass->Sumw2();
h_piKConcordInvMass->Sumw2();


double gen;
double phi;
double theta;
double p;
double px;
double py;
double pz;

gRandom->SetSeed();

for (int i=0; i<n; i++)
{
    //genero 100 particelle composte 80% pioni, 10% kaoni, 9% protoni e 1% K*
     for (int k = 0; k < 100; k++)
    //per ogni particella devo anche generare coordinata azimutale(phi), polare(theta) e impulso
    { 
        //genero secondo una distribuzione esponenziale per l'impulso e uniforme per le componenti angolari
        phi=gRandom->Rndm()*M_PI*2;
        theta=gRandom->Rndm()*M_PI;
        p=gRandom->Exp(1);

    


px = p * sin(theta) * cos(phi);
py = p * sin(theta) * sin(phi);
pz = p * cos(theta);

gen=gRandom->Rndm()*100;

if(gen < 40)
   particles.push_back(Particle("pi+", px, py, pz));
else if (gen >=40 && gen < 80)
   particles.push_back(Particle("pi-", px, py, pz));
else if( gen>=80 && gen< 85)
particles.push_back(Particle("K+", px, py, pz));
else if( gen>=85 && gen< 90)
particles.push_back(Particle("K-", px, py , pz));
else if( gen>=90 && gen< 94.5)
particles.push_back(Particle("P+", px, py , pz));
else if( gen>=94.5 && gen<99)
particles.push_back(Particle("P-", px, py , pz));
else if( gen>=99)
{ 
    particles.push_back(Particle("K*", px, py , pz));
    resonanceParticles.push_back(Particle("K*", px, py, pz));
} 



h_ParticleType->Fill(particles[k].GetIParticle()+0.5);
h_AzimuthAngle->Fill(phi);
h_PolarAngle->Fill(theta);
h_Momentum->Fill(p);
h_TransverseMomentum->Fill(sqrt(px*px+py*py));
h_Energy->Fill(particles[k].GetEnergy());

}

// descrizione del comportamento di una particella in caso di instabilità  quindi decadimento, attraveso il metodo decay2body
int nProd=0;
for (auto rp:resonanceParticles)
{
    gen=gRandom->Rndm();
    if (gen>0.5)
    {
        particles.push_back(Particle("pi+"));
        particles.push_back(Particle("K-"));
        rp.Decay2Body(particles[100+nProd], particles[100+nProd+1]);
    }
    else 
    {
        particles.push_back(Particle("pi-"));
        particles.push_back(Particle("K+"));
        rp.Decay2Body(particles[100+nProd], particles[100+nProd+1]);
    }
    nProd +=2;
}

//creo un ciclo per mettere nell'istogramma opportuno il valore della massa invariante, secondo le possibilità, di ciascuna coppia di particelle

for ( unsigned int part = 0; part < particles.size(); part++)
{
    for(unsigned int part2=0; part2 < part; part2++)
    {
        if (particles[part].GetCharge() !=0 
&& 
        particles[part2].GetCharge() !=0)
    {
        if(particles[part].GetCharge() == particles[part2].GetCharge() )

        {
            h_ConcordInvMass->Fill(particles[part].InvMass(particles[part2]));
            if(  
            ((particles[part].GetMass() > 0.1395 && particles[part].GetMass()<0.1396)&& (particles[part2].GetMass() > 0.4936 && particles[part2].GetMass() < 0.4937)) ||
           ((particles[part2].GetMass() > 0.1395 && particles[part2].GetMass() < 0.1396) && (particles[part].GetMass() > 0.4936 && particles[part].GetMass() < 0.4937))
              ) 
         h_piKConcordInvMass->Fill(particles[part].InvMass(particles[part2]));
        }
        else 
        {h_DiscordInvMass->Fill(particles[part].InvMass(particles[part2]));

        if (
              ((particles[part].GetMass() > 0.1395 && particles[part].GetMass() < 0.1396) && (particles[part2].GetMass() > 0.4936 && particles[part2].GetMass() < 0.4937)) ||
           ((particles[part2].GetMass() > 0.1395 && particles[part2].GetMass() < 0.1396) && (particles[part].GetMass() > 0.4936 && particles[part].GetMass() < 0.4937))
              ) 
     
        h_piKDiscordInvMass->Fill(particles[part].InvMass(particles[part2]));   
     }
    }
   }
}

if(particles.size()%2 !=0)
cout<<"Error\n";
else 
{
    vector<Particle>::iterator iterator= particles.begin() +100;
    for(; iterator !=particles.end(); iterator+=2)
    {
        h_ResInvMass->Fill((*iterator).InvMass(*(iterator+1)));
    }
}

particles.clear();
particles.shrink_to_fit();
resonanceParticles.clear();
resonanceParticles.shrink_to_fit();
}



file->Write(); 
file->Close();

    
    gBenchmark->Show("Time to execute the program"); 
    
  return 1;  
} 

