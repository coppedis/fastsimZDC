#ifndef QUADELE_H
#define QUADELE_H

#include "OpticEle.h"
#include <TString.h>
#include <TVectorT.h>

class QuadEle : public OpticEle {
  // class which implements propagation in quadrupoles 

 public:

  QuadEle();
  // getters
  virtual Double_t GetBtip() const {return fBtip;}
  virtual Double_t GetOpening() const {return fOpening;}
  virtual void Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t pmom);
  virtual void PrintStatus() const;
  //setters
  virtual void SetParEle(Double_t val0, Double_t val1, Double_t val2, Double_t val3, Bool_t val4, Double_t val5);

 protected:

  Double_t fBtip;    // B at pole tip kGauss
  Double_t fOpening; // opening of the quadrupole  cm 

//  ClassDef(QuadEle,1)
};

#endif
