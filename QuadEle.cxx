#include "QuadEle.h"
#include <TMatrixT.h>
#include <Riostream.h>
#include <TMath.h>

//ClassImp(QuadEle)

//____________________________________________________________________
QuadEle::QuadEle() : OpticEle(){
  // Default constructor
  fBtip = 0.;
  fOpening = 0.;
}

//____________________________________________________________________
void QuadEle::Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t pmom){
  // propagation in the quadrupole
  Double_t bl = fZoverA * 100*fLength*fBtip/fOpening;  // field integral Tm
  //  Double_t focl = pmom/bl/0.29979;       // focal length (m)

  Double_t qk=100.*TMath::Abs(fZoverA * 0.29979*fBtip/fOpening/pmom); // quad. strength

  qk=TMath::Sqrt(qk);
  Double_t qkl=qk*fLength;

  TMatrixT<Double_t> rX(2,2),rY(2,2),focus(2,2),defocus(2,2);
  //     focussing plane
  focus(0,0) = TMath::Cos(qkl);
  focus(0,1) = TMath::Sin(qkl)/qk;
  focus(1,0) = -TMath::Sin(qkl)*qk;
  focus(1,1) = TMath::Cos(qkl);
	//     defocussing plane
  defocus(0,0) = TMath::CosH(qkl);
  defocus(0,1) = TMath::SinH(qkl)/qk;
  defocus(1,0) = TMath::SinH(qkl)*qk;
  defocus(1,1) = TMath::CosH(qkl);
  if (bl >0.){ // lente convergente (in x)
    rX = focus;
    rY = defocus;
  }
  else { // lente divergente (in x)
    rX = defocus;
    rY = focus;
  }

  //     apply matrix to input vector

  *xcoor *=rX;
  *ycoor *=rY;
}

//____________________________________________________________________
void QuadEle::PrintStatus() const {
  // prints out the data members
  std::cout<<"======================================================\n";
  std::cout<<" QuadEle object\n";
  std::cout<<"Starting Z coordinate "<<fZpos<<"; length "<<fLength<<std::endl;
  std::cout<<"B tip "<<fBtip<<"; opening "<<fOpening<<std::endl;
  std::cout<<"Radial aperture : opening = "<<fAperture1<<std::endl;
  std::cout<<"======================================================\n";
}
//____________________________________________________________________
void QuadEle::SetParEle(Double_t val0, Double_t val1, Double_t val2, Double_t val3, Bool_t val4, Double_t val5)  {
  // set the data members
  fLength = val0;
  fZpos = val1;
  fBtip = val2;
  fOpening = val3;
  fRadial = val4;
  fAperture1 = val5;
}

