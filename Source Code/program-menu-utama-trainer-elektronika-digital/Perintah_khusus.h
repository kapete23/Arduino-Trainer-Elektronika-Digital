String KonBIL(char* str,byte bs1,byte bs2) { //Fungsi konversi bilangan
  bool skip = true;
  String Tmp;
  byte a,b;
  int Val;
  if ((bs1 == DEC)&&((bs2 == BIN)||(bs2 == OCT)||(bs2 == HEX))) {        //Bilangan DEC to BIN,OCT, HEX
    Tmp = (String)&str[0];
    Val = Tmp.toInt();
    Tmp = String(Val,bs2);
    skip = false;
  }else if (((bs1 == BIN)||(bs1 == OCT)||(bs1 == HEX))&&(bs2 == DEC)) {  //Bilangan BIN,OCT, HEX to DEC
    switch(bs1) {
      case BIN: {//Bilangan Biner
        Val = strtol(&str[1], NULL, bs1);
        break;}
      case OCT: {//Bilangan Oktal
        Val = strtol(&str[0], NULL, bs1);
        break;}
      case HEX: {//Bilangan Heksadesimal
        Val = strtol(&str[2], NULL, bs1); 
        break;}
    }
    Tmp = String(Val);
    skip = false;
  } else {
    Tmp = (String)&str[0];
    b = Tmp.length();
    switch(bs1) {
      case BIN:  {//Bilangan Biner
        if ((b > 0)&&(b <= 16)) skip = false;
        break;}
      case OCT:  {//Bilangan Oktal
        if ((b > 0)&&(b <= 6)) skip = false;
        break;}
      case DEC:  {//Bilangan Desimal
        if ((b > 0)&&(b <= 6)) {
          Val = Tmp.toInt();
          skip = false;}
        break;}
      case HEX: {//Bilangan Heksadesimal
        if ((b > 0)&&(b <= 4)) skip = false;
        break;}
    }
  }

  if (!skip) {
    b = Tmp.length();
    switch(bs2) {
      case BIN:  {//Bilangan Biner
        for(a = 16; a > b; a--) Tmp = '0' + Tmp;
        Tmp = 'B' + Tmp;
        break;}
      case OCT:  {//Bilangan Oktal
        for(a = 6; a > b; a--) Tmp = '0' + Tmp;
        Tmp += " (Oktal)";
        break;}
      case DEC:  {//Bilangan Biner
        if (Val < 0) { //Bilangan bertanda negatif
          Tmp = (String)&Tmp[1];
          for(a = 6; a > b; a--) Tmp = '0' + Tmp;
          Tmp = '-' + Tmp;
        }else {
          for(a = 5; a > b; a--) Tmp = '0' + Tmp;
          Tmp = ' ' + Tmp;}
        Tmp += " (Desimal)";
        break;}
      case HEX: {//Bilangan Heksadesimal
        Tmp.toUpperCase();
        for(a = 4; a > b; a--) Tmp = '0' + Tmp;
        Tmp = "0x" + Tmp;
        Tmp += " (Heksa)";
        break;}
    }
  }
  return Tmp;
}

void Perintah(byte z,byte i,byte j,byte k,byte m,byte n,byte p) {
  byte a;
  switch(z) {
  //Fungsi untuk setting pin input/output
    case 1: {//Sebagai pin input di trainer elektronika digital
        for(a = 0; a < 27; a++){
          if (DataPinEdit[i][j] == ((const char*)pgm_read_word(&Pin_IO[a][0]))[0]){
            bil[k][0] = ((const byte*)pgm_read_word(&Pin_IO[a][1]));
            pinMode(bil[k][0],OUTPUT);
            break; 
          }
        }
        break;}
    case 2: {//Sebagai pin output di trainer elektronika digital
        for(a = 0; a < 27; a++){
          if (DataPinEdit[i][j] == ((const char*)pgm_read_word(&Pin_IO[a][0]))[0]){
            bil[k][0] = ((const byte*)pgm_read_word(&Pin_IO[a][1]));
            pinMode(bil[k][0],INPUT_PULLUP);
            break;
          }
        }
        break;}
  //Fungsi untuk kontrol logic pin (HIGH or LOW)
    case 3: {//Perintah digitalWrite(pin,logic state) -> Sebagai input trainer elektronika digital
        for(a = 0; a < (i*p); a+=p){ digitalWrite(bil[j==0?(a/p):j==1?((a/p)+k):k][0],bil[j==0?(a/p):j==1?((a/p)+k):k][1]);}
        break;}
    case 4: {
        for(a = 0; a < (i*p); a+=p){
          bil[j==0?(a/p):j==1?((a/p)+k):k][1] = String(DataPinLogic[m][a+n]).toInt();
          digitalWrite(bil[j==0?(a/p):j==1?((a/p)+k):k][0],bil[j==0?(a/p):j==1?((a/p)+k):k][1]);
        }
        break;}
    case 5: {//Perintah digitalRead(pin) -> Sebagai output trainer elektronika digital
        for(a = 0; a < (i*p); a+=p){ bil[j==0?(a/p):j==1?((a/p)+k):k][1]= digitalRead(bil[j==0?(a/p):j==1?((a/p)+k):k][0]);}
        break;}
    case 6: {
        for(a = 0; a < (i*p); a+=p){
          bil[j==0?(a/p):j==1?((a/p)+k):k][1]= digitalRead(bil[j==0?(a/p):j==1?((a/p)+k):k][0]);
          *(*(DPL + m) + (a+n)) = bil[j==0?(a/p):j==1?((a/p)+k):k][1]+'0';
        }
        break;}
  }
}

void fungsi_Tanda(menuNode& target) {
  String TMP;
  int val;
  switch(base1) {
    case BIN:  {//Bilangan Biner
        TMP = KonBIL(TxtBil[3],base1,DEC);
        break;}
    case OCT:  {//Bilangan Oktal
        TMP = KonBIL(TxtBil[0],base1,DEC);
        break;}
    case DEC: {//Bilangan Desimal
        TMP = KonBIL(TxtBil[1],base1,DEC);
        break;}
    case HEX: {//Bilangan Heksadesimal
        TMP = KonBIL(TxtBil[2],base1,DEC);
        break;}
  }
  val = TMP.toInt();
  if (((val < 0)&&(!Sign))||((val >= 0)&&(Sign))) {
    val = (~val) + 1;  //Komplemen kedua
    TMP = String(val);
    TMP = KonBIL(&TMP[0],DEC,base1);
    target.dirty = true; //Refresh layar
  }else TMP = KonBIL(&TMP[0],DEC,base1);
  switch(base1) {
    case BIN:  {//Bilangan Biner
        TMP.toCharArray(*(TBl + 3),(TMP.length()+1));
        break;}
    case OCT:  {//Bilangan Oktal
        TMP.toCharArray(*(TBl + 0),(TMP.length()+1));
        break;}
    case DEC: {//Bilangan Desimal
        TMP.toCharArray(*(TBl + 1),(TMP.length()+1));
        break;}
    case HEX: {//Bilangan Heksadesimal
        TMP.toCharArray(*(TBl + 2),(TMP.length()+1));
        break;}
  }
}

//Fungsi untuk menerjemahkan (encode) ke angka seven segment berdasarkan input logic
/*char Angka_SS(byte (*data)[2], byte x, byte y, byte m) {
  uint8_t value = 0;
  byte i;

  for (i = 0; i < m; ++i) value |= data[x+i][y] << i;
  switch(value) {
    case  64 : {return '0'; break;}
    case 121 : {return '1'; break;}
    case  36 : {return '2'; break;}
    case  48 : {return '3'; break;}
    case  25 : {return '4'; break;}
    case  18 : {return '5'; break;}
    case   2 : {return '6'; break;}
    case 120 : {return '7'; break;}
    case   0 : {return '8'; break;}
    case  16 : {return '9'; break;}
    default  : {return ' '; break;}  
  }
}*/
