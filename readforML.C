#if !defined(__CINT__) || defined(__MAKECINT__)

#include <stdio.h>
#include <stdlib.h>
#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TClassTable.h>
#include <TStyle.h>
#include <TGrid.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TLatex.h>
#include <TNtuple.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLegend.h>
#include <TString.h>
#include <TMath.h>
#include <TF1.h>

#endif
void readforML(TString filename = "nspec.root")
{      
    TFile *f = TFile::Open(filename.Data(), "READ");
    if(!f || f->IsZombie()) {
        printf("Error opening file %s\n", filename.Data());
        return;
    }
    printf("\n ---- Opening file %s\n\n", filename.Data());
  
    TTree *zdctreein = (TTree*) (f->Get("zdct"));

    typedef struct {
            int EventNum;
            int ParticleNum;
            int ParticleCode;
            int IdCalo;
            int iSide;
            int kacc;
            double pvx;
            double pvy;
            double pvz;
            double pv;
            double xvrt;
            double yvrt;
            double zvrt;
            double xcalo;
            double ycalo;
            double uxcalo;
            double uycalo;
            double Enecalo;
      } ACC;
      static ACC acc;
      zdctreein->SetBranchAddress("acc",&acc);
      
      int pdg = 0;
      double px = 0;
      double py = 0;
      double pz = 0;
      double pxcalo = 0;
      double pycalo = 0;
      double ene = 0;
      double eneoutput = 0;
      double xspot = 0;
      double yspot = 0;
      int idcalo = 0;

      TFile *fout = TFile::Open("ml_output.root", "RECREATE");
      TTree *mltree = new TTree("mltree", "ML Tree");
      mltree->Branch("pdg", &pdg, "pdg/I");
      mltree->Branch("px", &px, "px/D");
      mltree->Branch("py", &py, "py/D");
      mltree->Branch("pz", &pz, "pz/D");
      mltree->Branch("pxcalo", &pxcalo, "pxcalo/D");
      mltree->Branch("pycalo", &pycalo, "pycalo/D");
      mltree->Branch("ene", &ene, "ene/D");
      mltree->Branch("eneoutput", &eneoutput, "eneoutput/D");
      mltree->Branch("xspot", &xspot, "xspot/D");
      mltree->Branch("yspot", &yspot, "yspot/D");
      mltree->Branch("idcalo", &idcalo, "idcalo/I");

      for(int i=0; i<zdctreein->GetEntries(); i++) {
         zdctreein->GetEntry(i);
         if(acc.kacc != 1) continue;
         
         pdg = acc.ParticleCode;
         px = acc.pvx; // px as generated
         py = acc.pvy; // py as generated
         pz = acc.pvz; // pz as generated
         pxcalo = acc.uxcalo*acc.pvz; // px at calo
         pycalo = acc.uycalo*acc.pvz; // py at calo
         ene = acc.pv; // energy hitting the calorimeter
         eneoutput = acc.Enecalo; // parametrized energy reconstructed in the calorimeter
         xspot = acc.xcalo; // x position at calorimeter front face
         yspot = acc.ycalo; // y position at calorimeter front face
         idcalo = acc.IdCalo; // = 1 for ZN, = 2 for ZP

         mltree->Fill();
      }

      fout->cd();
        mltree->Write();    
      fout->Close();
      f->Close();
}