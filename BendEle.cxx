#include "BendEle.h"
#include <TMatrixT.h>
#include <Riostream.h>

//ClassImp(BendEle)

//____________________________________________________________________
BendEle::BendEle() : OpticEle(){
  // Default constructor
  fBField = 0.;
  fHorBend = kFALSE;
  fSignDefl = 1.;
}

//____________________________________________________________________
void BendEle::Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t pmom){
// propagation in the dipole
  Double_t bl = fZoverA * 0.1 * TMath::Abs(fBField) * fLength;
  Double_t ptkick = 0.29979 * bl;
  Double_t theta0 = 1000.0  * ptkick/pmom;
  Drift(xcoor,ycoor);
  if(fHorBend){
    fSignDefl = -1.0*TMath::Sign(1.0,fBField);
    theta0 *= fSignDefl;
    (*xcoor)(0) += theta0*fLength/2.;
    (*xcoor)(1) += theta0;
  }
  else {
    fSignDefl = TMath::Sign(1.0,fBField);
    theta0 *= fSignDefl;
    (*ycoor)(0) += theta0*fLength/2.;
    (*ycoor)(1) += theta0;
  }
}

//____________________________________________________________________
void BendEle::PrintStatus() const {
  // prints out the data members
  std::cout<<"======================================================\n";
  std::cout<<" BendElement object\n";
  std::cout<<"Starting Z coordinate "<<fZpos<<"; length "<<fLength<<std::endl;
  std::cout<<"B Field "<<fBField<<std::endl;
  if(fHorBend){
    std::cout<<"Bending plane: Horizontal \n";
  }
  else {
    std::cout<<"Bending plane: Vertical \n";
  }
  std::cout<<"Aperture type is radial - aperture radius =  "<<fAperture1<<std::endl;
  std::cout<<"======================================================\n";
}
//____________________________________________________________________
void BendEle::SetParEle(Double_t val0, Double_t val1 ,Double_t val2, Double_t val3, Bool_t val4, Double_t val5)  {
  // set the data members
  fLength = val0;
  fZpos = val1;
  fBField = val2;
  if(val3==0) fHorBend = kFALSE;
  else fHorBend = kTRUE;
  fRadial = val4;
  fAperture1 = val5;
  fAperture2 = val5;
}

