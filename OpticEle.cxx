#include <TMatrixT.h>
#include <TNamed.h>
#include "OpticEle.h"
#include <iostream>

using namespace std;

//ClassImp(OpticEle)

//____________________________________________________________________
OpticEle::OpticEle() : TNamed(){
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
  //printf(" >>>> OpticEle::Drift INPUT: %1.3f %1.3f   \n", (*xcoor)(0), (*ycoor)(0));

  TMatrixT<Double_t> trasf(2,2);
  trasf(0,0) = 1.;
  trasf(0,1) = fLength;
  trasf(1,0) = 0.;
  trasf(1,1) = 1.;

  //     apply matrix to input vector

  *xcoor *= trasf;
  *ycoor *= trasf;
  //printf(" >>>> OpticEle::Drift OUTPUT: %1.3f %1.3f   \n", (*xcoor)(0), (*ycoor)(0));
}
//____________________________________________________________________
void OpticEle::SetZoverA(Double_t val0)  {
// set the data members
  fZoverA = val0;
}
