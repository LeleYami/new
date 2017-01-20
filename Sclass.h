#include <iostream>
#include "/home/luole/root/include/TObject.h"
class Sclass:public TObject{
  private:
    Float_t fX;
    Float_t fY;
  public:
    Sclass()   { fX = fY = 0; }
    void Print(Option_t* opt="") const;
    void SetX(float x)  { fX=x; }
    void SetY(float y)  { fY=y; }

ClassDef(Sclass,1)
};
