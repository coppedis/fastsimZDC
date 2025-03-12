#ifndef DRIFTELE_H
#define DRIFTELE_H

#include "OpticEle.h"
#include <TString.h>
#include <TVectorT.h>

class DriftEle : public OpticEle {
  // class which implements propagation in free space

 public:

  DriftEle();
  // getters
  virtual void Propagate(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor, Double_t /* pmom */);
  virtual void PrintStatus() const;
  //setters
  virtual void SetParEle(Double_t val0, Double_t val1, Bool_t val2, Double_t val3 /*, Double_t val4 */);
  
 protected:

//  ClassDef(DriftEle,1)
};

#endif
