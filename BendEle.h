#ifndef BENDELE_H
#define BENDELE_H

#include "OpticEle.h"
#include <TString.h>
#include <TVectorT.h>
#include <TMath.h>

class BendEle : public OpticEle {
  // class which implements propagation in dipoles 

 public:

  BendEle();
  // getters
  virtual Double_t GetB() const {return fBField;}
  virtual Bool_t GetHorBend() const {return fHorBend;}
  virtual void Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t pmom);
  virtual void PrintStatus() const;
  virtual void SetParEle(Double_t val0, Double_t val1, Double_t val2, Double_t val3, Bool_t val4, Double_t val5);

 protected:

  Double_t fBField;    // B in kGauss
  Bool_t fHorBend;     // opening of the quadrupole 
  Double_t fSignDefl;  // Sign==1 if fHorBend==false, -1 if fHorBend==true
//  ClassDef(BendEle,1)
};

#endif
