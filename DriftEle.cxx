#include "DriftEle.h"
#include <TMatrixT.h>
#include <Riostream.h>

//ClassImp(DriftEle)

//____________________________________________________________________
DriftEle::DriftEle() : OpticEle(){
  // Default constructor
}

//____________________________________________________________________
void DriftEle::Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t /* pmom */){
  // propagation in vacuum without magnetic field
  Drift(xcoor,ycoor);
}

//____________________________________________________________________
void DriftEle::PrintStatus() const {
  // prints out the data members
  std::cout<<"======================================================\n";
  std::cout<<" DriftElement object\n";
  std::cout<<"Starting Z coordinate "<<fZpos<<"; length "<<fLength<<std::endl;
  std::cout<<"======================================================\n";
}
//____________________________________________________________________
void DriftEle::SetParEle(Double_t val0, Double_t val1, Bool_t val2, Double_t val3 /*, Double_t val4*/)  {
  // set the data members
  fLength = val0;
  fZpos = val1;
  fRadial = val2;
  fAperture1 = val3;
//  fAperture2 = val4;
}

