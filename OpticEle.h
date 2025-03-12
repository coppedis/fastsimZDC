#ifndef OPTICELE_H
#define OPTICELE_H

#include <Rtypes.h>
#include <TVectorT.h>

   class TString;


class OpticEle : public TObject {
  // abstract base class for bending magnets (dipoles), quadrupoles and
  // empty space (straight propagation)

 public:

  OpticEle();
  virtual ~OpticEle();
  // getters
  virtual Double_t GetLength() const {return fLength;}
  virtual Double_t GetZPos() const {return fZpos;}
  virtual Bool_t GetApertType() const {return fRadial;}
  virtual Double_t GetAperture1() const {return fAperture1;}
  virtual Double_t GetAperture2() const {return fAperture2;}
  virtual Double_t GetZoverA() const {return fZoverA;}
  //setters
  virtual void SetZoverA(Double_t val0); 
  // abstract methods
  virtual void Propagate(TVectorT<Double_t> *x, TVectorT<Double_t> *y,Double_t pmom) = 0;
  virtual void PrintStatus() const = 0;

  void Drift(TVectorT<Double_t> *xcoor, TVectorT<Double_t> *ycoor); // drift with B=0

 protected:

  Double_t fLength; // length of the Element (along z direction)
  Double_t fZpos;   // Z coord. of the Element (fZpos<Ele<fZpos+fLength)
  Bool_t  fRadial;  // Aperture type : if fRadial = TRUE aperture is radial
  Double_t fAperture1; // aperture radial (or horizontal (in mm)
  Double_t fAperture2; // aperture radial (same as before or vertictal (in mm))
  Double_t fZoverA; // Z/A of the ion
  
//  ClassDef(OpticEle,1)
};

#endif
