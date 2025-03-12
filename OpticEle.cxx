#include <TMatrixT.h>
#include "OpticEle.h"

//ClassImp(OpticEle)

//____________________________________________________________________
OpticEle::OpticEle() {
// Default constructor
  fLength = 0.;
  fZpos = 0.;
  fRadial = kTRUE;
  fAperture1 = 3.0 ; // radial aperture in mm or horiz. aperture for collimators
  fAperture2 = 3.0 ; // vertical aperture in mm for collimators
  fZoverA = 1.0;     // Z/A of the ions
}


//____________________________________________________________________
OpticEle::~OpticEle(){
// destructor
}

//____________________________________________________________________
void OpticEle::Drift(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor) {
// transport in free space without a magnetic field
  TMatrixT<Double_t> trasf(2,2);
  trasf(0,0) = 1.;
  trasf(0,1) = fLength;
  trasf(1,0) = 0.;
  trasf(1,1) = 1.;

  //     apply matrix to input vector

  *xcoor *=trasf;
  *ycoor *=trasf;
}
//____________________________________________________________________
void OpticEle::SetZoverA(Double_t val0)  {
// set the data members
  fZoverA = val0;
}

