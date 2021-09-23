class displayKonversi:public prompt { //Tampilan untuk konversi bilangan
public:
  displayKonversi(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    len-=print_P(out,getText(),len);
    len-=out.print(TxtBil[4]);
  }
};

class outLogic:public prompt { //Tampilan untuk Output Logic psda pin I/O
public:
  outLogic(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    len-=print_P(out,getText(),len);
    len-=out.print(DataPinLogic[14]);
  }
};

class tampilan_carryOut:public prompt { //Tampilan untuk Carry Out rangkaian adder
public:
  tampilan_carryOut(constMEM promptShadow& p):prompt(p) {}
  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t) override {
    len-=print_P(out,getText(),len);
    len-=out.print(DataPinLogic[15]);
  }
};
