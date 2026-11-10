#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TROOT.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Analyze()

{
    cout<<"\n______ANALYSIS OF GENERATED PARTICLES__\n\n";
    gStyle->SetOptStat(10);
    gStyle->SetOptFit(1111);

// riapro il  file root definito pe GeneratedParticle
    
    TFile *file= new TFile("particlesinfo.root", "READ");
  // Definisco gli istrogrammi lavorando con un array, e definendo per ogni suo elemento a quale istogramma è riferito

   TH1F ** histos = new TH1F*[11];

    histos[0] = (TH1F*)file->Get("h_ParticleType");
    histos[1] = (TH1F*)file-> Get("h_AzimuthAngle");
    histos[2] = (TH1F*)file-> Get("h_PolarAngle");
    histos[3] = (TH1F*)file-> Get("h_Momentum");
    histos[4] = (TH1F*)file-> Get("h_TransverseMomentum");
    histos[5] = (TH1F*)file-> Get("h_Energy");
    histos[6] = (TH1F*)file-> Get("h_DiscordInvMass");
    histos[7] = (TH1F*)file-> Get("h_ConcordInvMass");
    histos[8] = (TH1F*)file-> Get("h_piKDiscordInvMass");
    histos[9] = (TH1F*)file-> Get("h_piKConcordInvMass");
    histos[10] = (TH1F*)file-> Get("h_ResInvMass");

// cosmetica degli istogrammi, utilizzo un ciclo for per settare il titolo sull'asse x degli istogrammi di massa invariante

    for(int i = 6; i < 11; i++)
        histos[i]->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");

histos[0]->GetXaxis()->SetTitle("Particle type");
histos[1]->GetXaxis()->SetTitle("Angle (degrees)");
histos[2]->GetXaxis()->SetTitle("Angle (degrees)");
histos[3]->GetXaxis()->SetTitle("Momentum(GeV/c)");
histos[4]->GetXaxis()->SetTitle("Transverse Momentum(GeV/c)");
histos[5]->GetXaxis()->SetTitle("Energy(GeV)");

// creo la prima canvas, che fa riferimento a Particle Type

TCanvas *c=new TCanvas("c","particles histo");
c->Divide(1);
c->cd(1);
gPad->Divide(3,1);

gPad->cd(1);
gPad->SetFrameFillColor(25);
gPad->SetGrid();


histos[0]->GetXaxis()->SetBinLabel(1,"pi+");
histos[0]->GetXaxis()->SetBinLabel(2,"pi-");
histos[0]->GetXaxis()->SetBinLabel(3,"K+");
histos[0]->GetXaxis()->SetBinLabel(4,"K-");
histos[0]->GetXaxis()->SetBinLabel(5,"P+");
histos[0]->GetXaxis()->SetBinLabel(6,"P-");
histos[0]->GetXaxis()->SetBinLabel(7,"K*");
histos[0]->SetFillColor(22);
histos[0]->SetTitle("Particle");
histos[0]->Draw("bar1");
histos[0]->SetStats(1);

cout.setf(ios::scientific, ios::floatfield);

cout<<"\n1) Particle Type Distribution\n\n"
     <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(1)
     <<" = " 
     <<histos[0]->GetBinError(1)
     <<" +/- "
     <<histos[0]->GetBinError(1)
     <<((histos[0]->GetBinContent(1)/100000<(40+histos[0]->GetBinError(1))
&& 
         histos[0] ->GetBinContent(1)/100000>(40-histos[0]->GetBinError(1))) ?" yes\n":" no\n")

       <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(2)
     <<histos[0]->GetBinError(2)
     <<" +/- "
     <<histos[0]->GetBinError(2)
     <<((histos[0]->GetBinContent(2)/100000<(40+histos[0]->GetBinError(2))
        && 
        histos[0] ->GetBinContent(2)/100000>(40-histos[0]->GetBinError(2))) ?" yes\n":" no\n")

       <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(3)
<<" = "
     <<histos[0]->GetBinError(3)
     <<" +/- "
     <<histos[0]->GetBinError(3)
     <<((histos[0]->GetBinContent(3)/100000<(5+histos[0]->GetBinError(3))
&& 
        histos[0] ->GetBinContent(3)/100000>(5-histos[0]->GetBinError(3))) ?" yes\n":" no\n")

     <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(4)
     <<" = " 
     <<histos[0]->GetBinError(4)
     <<" +/- "
     <<histos[0]->GetBinError(4)
     <<((histos[0]->GetBinContent(4)/100000<(5+histos[0]->GetBinError(4))
&& 
       histos[0] ->GetBinContent(4)/100000>(5-histos[0]->GetBinError(4))) ?" yes\n":" no\n")

     <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(5)
     <<" = " 
     <<histos[0]->GetBinError(5)
     <<" +/- "
     <<histos[0]->GetBinError(5)
     <<((histos[0]->GetBinContent(5)/100000<(4.5+histos[0]->GetBinError(5))
&& 
        histos[0] ->GetBinContent(5)/100000>(4.5-histos[0]->GetBinError(5))) ?" yes\n":" no\n")

     <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(6)
     <<" = " 
     <<histos[0]->GetBinError(6)
     <<" +/- "
     <<histos[0]->GetBinError(6)
     <<((histos[0]->GetBinContent(6)/100000<(4.5+histos[0]->GetBinError(6))
&& 
       histos[0] ->GetBinContent(6)/100000>(4.5-histos[0]->GetBinError(6))) ?" yes\n":" no\n")

     <<setw(4)
     <<histos[0]->GetXaxis()->GetBinLabel(7)
     <<" = " 
     <<histos[0]->GetBinError(7)
     <<" +/- "
     <<histos[0]->GetBinError(7)
     <<((histos[0]->GetBinContent(7)/100000<(1+histos[0]->GetBinError(7))
&& 
        histos[0] ->GetBinContent(7)/100000>(1-histos[0]->GetBinError(7))) ?" yes \n":" no \n");

// definisco una funzione esponenziale che mi servirà per verificare la distribuzione dell'impulso
TF1 *f1 = new TF1("f1", "expo(0)", 0, 5);
    f1->FixParameter(0, 0);
    f1->SetParameter(1, -1);
    
    c->cd(1);

// Istogramma dell'impulso
cout<<"\n\n2) Momentum Distribution\n\n";
gPad->cd(2);
gPad->SetFrameFillColor(33);
histos[3]->Fit(f1,"Q");
TF1*expfit=histos[3]->GetFunction("f1");
histos[3]->SetFillColor(47);
histos[3]->Draw();
cout.setf(ios::scientific, ios::floatfield);
         cout << setprecision(1) 
              <<  "The slope of the best fit exponential function is "
              << setprecision(4) 
              << expfit->GetParameter(1) 
              << " +/- " << expfit->GetParError(1)
              << setprecision(1) 
              << ".\nChi square = " 
              << expfit->GetChisquare() 
              << " / " << expfit->GetNDF() << "\n";
c->cd(1);


//Energia


gPad->cd(3);
gPad->SetFrameFillColor(45);
histos[5]->SetFillColor(8);
histos[5]->SetLineColor(1);
histos[5]->Draw();
gPad->Update();
TPaveStats* energystats=(TPaveStats*)histos[5]->FindObject("stats");
energystats->SetOptStat(2210);

// creo una nuova canvas per le distribuzoni angolari

TCanvas*c1= new TCanvas("c1", "angle histo");
c1->Divide(2);


// definisco una funzione con cui verificare che la distribuzione angolare sia compatibile con quella uniforme 



// angolo polare
c1->cd(2);
TF1*f2=new TF1("f2","pol0(0)", 0, 2*M_PI);
f2->SetParameter(0, (10000000/histos[2]->GetNbinsX()));
gPad->SetFrameFillColor(36);
histos[2]->Fit(f2, "Q","", 0, M_PI);
TF1*linfit=histos[2]->GetFunction("f2");
histos[2]->SetFillColorAlpha(22, 0.25);
histos[2]->Draw();

cout << "\n\n3) ANGLE DISTRIBUTION \n\n";
  cout.setf(ios::fixed, ios::floatfield);
  cout << setprecision(1) 
              << "---->Polar Angle\n"
              << "Uniform distribution: the parameter of the grade 0 best fit polinomial function is " 
              << linfit->GetParameter(0) 
              << " +/- " 
              << linfit->GetParError(0)
              << ".\nChi square = " 
              << linfit->GetChisquare() 
              << " / " << linfit->GetNDF() 
              << "\n\n";

//angolo azimutale 

c1->cd(1);
gPad->SetFrameFillColor(36);
f2->SetParameter(0 ,(10000000/histos[1]->GetNbinsX()));

TFitResultPtr res = histos[1]->Fit(f2,"S Q R");

histos[1]->SetFillColorAlpha(22, 0.55);
histos[1]->Draw();

cout<<setprecision(1)
    <<" Azimuthal Angle\n"
 << "Uniform dirtribution: the parameter of the grade 0 best fit polinomial function is "
    <<res->Parameter(0) << " +/- "
    <<res->ParError(0)
    <<".\nChi square= " << res->Chi2()
    << " / " 
    <<res->Ndf()
    <<"\n";


// Creo una terza canvas 

TCanvas *c2= new TCanvas("c2","InvMass Histo");
c2->Divide(2,2);
TPaveStats*stats;

c2->cd(1);
//Mass Invariante discorde
histos[6]->Draw();
gPad->SetFrameFillColor(48);
gPad->Update();
stats= (TPaveStats*)histos[6]->FindObject("stats");
stats->SetOptStat(2210);

//Massa Invariante concorde

c2->cd(2);
histos[7]->Draw();
gPad->SetFrameFillColor(66);
gPad->Update();
stats= (TPaveStats*)histos[7]->FindObject("stats");
stats->SetOptStat(2210);

//pi e K conocord InvMass

c2->cd(3);
histos[8]->Draw();
gPad->SetFrameFillColor(46);
gPad->Update();
stats= (TPaveStats*)histos[8]->FindObject("stats");
stats->SetOptStat(2210);

//pi e K discordi InvMass 

c2->cd(4);
histos[9]->Draw();
gPad->SetFrameFillColor(40);
gPad->Update();
stats= (TPaveStats*)histos[9]->FindObject("stats");
stats->SetOptStat(2210);

// creo una quarta canvas

TCanvas*c3= new TCanvas("c3","InvMass of K*");
c3->Divide(3);


//Massa Invariante prodotto di risonanza 

cout<<"\n\n4) Inv Mass\n\n";

c3->cd(1);
gPad->SetFrameFillColor(20);
histos[10]->Fit("gaus","Q");
histos[10]->SetFillColorAlpha(50, 0.25);
histos[10]->Draw();
gPad->Update();
stats= (TPaveStats*)histos[10]->FindObject("stats");
stats->SetOptStat(0);
TF1*gauss= histos[10]->GetFunction("gaus");
cout<<"the result of K* decay:\n"
    <<setprecision(5) <<"(+) mass = "<<gauss->GetParameter(1) << " +/- " <<gauss->GetParError(1)
    <<"\n (+) resonance = " << gauss->GetParameter(2) << " +/- " <<gauss->GetParError(2)
    <<setprecision(1)<<"\n (+) amplitude = "<< gauss->GetParameter(0)<< " +/- " << gauss->GetParError(0)
    <<"\n (+) chisqaure/NDOF = "<< gauss->GetChisquare() <<" / " <<gauss->GetNDF() <<"\n\n";

TH1F*S= new TH1F("S","K*resonance ", 1000, 0., 5.);
S->GetXaxis()->SetTitle("Inv Mass(GeV/c^2)");
S->GetYaxis()->SetTitle("entries");
S->Add(histos[8], histos[9], 1, -1);
S->GetXaxis()->SetRange(100,300);

//segnale di K* risonanza da particelle InvMass


c3->cd(2);
gPad->SetFrameFillColor(20);
S->Fit("gaus", "Q");
S->SetFillColorAlpha(50, 0.25);
S->Draw();
gPad->Update();
TF1*fitgaus= S->GetFunction("gaus");
   cout << "The resulting signal from the combinations of Pions and Kaons gives the following K* parameters:\n"
        << setprecision(5) << " (+) mass = " << fitgaus->GetParameter(1) << " +/- " << fitgaus->GetParError(1)
        << "\n (+) resonance = " << fitgaus->GetParameter(2) << " +/- " << fitgaus->GetParError(2)
        << setprecision(1) << "\n (+) amplitude = " << fitgaus->GetParameter(0) << " +/- " << fitgaus->GetParError(0)
        << "\n (+) chisquare / NDOF = " << fitgaus->GetChisquare() << " / " << fitgaus->GetNDF() << "\n\n";

//Segnale di K*risonanza da pi e K InvMass

c3->cd(3);
 TH1F * PSub = new TH1F("PSub", "K* resonance signal from particles invariant mass", 1000, 0., 5.);
    PSub->GetXaxis()->SetTitle("Invariant mass (GeV/c^2)");
    PSub->GetYaxis()->SetTitle("Entries");
    PSub->Add(histos[6], histos[7], 1, -1);
    PSub->GetXaxis()->SetRange(100, 300);
    gPad->SetFrameFillColor(20);
    PSub->Fit("gaus", "Q", "", 0.5, 1.4);
    PSub->SetFillColorAlpha(50, 0.25);
    PSub->Draw();
    gPad->Update();
    stats = (TPaveStats*)PSub->FindObject("stats");
    stats->SetOptStat(0);
    TF1 * fitgaus2 = PSub->GetFunction("gaus");
    cout << "The resulting signal from the combinations of all the particles gives the following K* parameters:\n"
        << setprecision(5) << " (+) mass = " << fitgaus2->GetParameter(1) << " +/- " << fitgaus2->GetParError(1)
        << "\n (+) resonance = " << fitgaus2->GetParameter(2) << " +/- " << fitgaus2->GetParError(2)
        << setprecision(1) << "\n (+) amplitude = " << fitgaus2->GetParameter(0) << " +/- " << fitgaus2->GetParError(0)
        << "\n (+) chisquare / NDOF = " << fitgaus2->GetChisquare() << " / " << fitgaus2->GetNDF() << "\n\n";

    return 1;    
}
