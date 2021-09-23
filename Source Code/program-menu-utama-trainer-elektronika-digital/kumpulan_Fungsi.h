#include "Perintah_khusus.h"

//#include <plugin/userMenu.h>

/*struct TargetMenu:UserMenu{
  using UserMenu::UserMenu;

  // override sz() function to have variable/custom size
  //inline idx_t sz() const override {return dataku.c_str().length;}

  //customizing the print of user menu item (len is the availabe space)
  Used printItem(menuOut& out, int idx,int len) override {
    //just printing the string name to the menu output device
    //as an item representative
    return len?out.printText(dataku[idx].c_str(),len):0;
  }

  Used printTo(navRoot &root,bool sel,menuOut& out, idx_t idx,idx_t len,idx_t p) override {
    Used r=UserMenu::printTo(root,sel,out,idx,len,p);
    if (this==root.navFocus) {
      out.setCursor(15,0);
      out.write(root.node().sel==0?byte(0):byte(1));
      out.setCursor(15,1);
      out.write((root.node().sel<(root.node().sz()-1))?byte(2):byte(3));
    }
    return r;
  }
};*/

void tampilanAwal(){
  if (st[0] == 0) lcd.blink();
  else if (((const char*)pgm_read_word(&pesan[st[1]]))[st[0]] == '\0') {
    lcd.noBlink();
    st[0]=0;
    st[1]++;
    if (st[2]==1) {
      st[2]--; //Baris
      ST[0] = true;
    }
    else st[2]++;
  }
  
  if ((ST[0])&&(TimeD3.update())) {
    lcd.noBlink();
    if (ST[1] == false) lcd.scrollDisplayRight();
    else lcd.scrollDisplayLeft();
    st[3]++;
    if (st[3]==20) {
      if (st[1]%2==0) {
        if (ST[1]==ST[1]) ST[1]=!ST[1]; 
      }
      lcd.clear();
      ST[0] = false;
      if (st[1]==4) for(int b = 0; b < 4; b++) st[b]=0;
      st[3]=0;
    }
  }
  else if ((TimeD1.update())&&(((const char*)pgm_read_word(&pesan[st[1]]))[st[0]] != '\0')&&(!ST[0])) {
    lcd.setCursor(st[0],st[2]);
    lcd.write(((const char*)pgm_read_word(&pesan[st[1]]))[st[0]]);
    st[0]++;
    if (((const char*)pgm_read_word(&pesan[st[1]]))[st[0]] == '\0') lcd.noBlink();
  }
}

/*void showPath(navRoot& root) {
  Serial.println();
  Serial.println("========");
  Serial.print("nav level:");
  Serial.print(root.level);
  Serial.print(" path:[");
  for(int n=0;n<=root.level;n++) {
    Serial.print(n?",":"");
    Serial.print(root.path[n].sel);
  }
  Serial.println("]");
}*/

bool findRepeatChar(char* s, char b) { 
//Temukan karakter ganda pada char array dan cari karakter tertentu
//Jika karakter ganda ditemukan atau karakter tertentu ditemukan maka mengembalikan nilai true.
    // this is optimized method 
    int p = -1, i, k;
    byte n = strlen(s);
    bool m = false; 
  
    // initialized counts of occurrences of 
    // elements as zero 
    int hash[MAX_CHAR] = { 0 }; 
  
    // initialized positions 
    int pos[MAX_CHAR]; 

//Temukan karakter ganda pada char array
    for (i = 0; i < n; i++) { 
        k = (int)s[i]; 
        if (hash[k] == 0) { 
            hash[k]++; 
            pos[k] = i; 
        } else if (hash[k] == 1) 
            hash[k]++; 
    } 
  
    for (i = 0; i < MAX_CHAR; i++) { 
        if (hash[i] == 2) { 
            if (p == -1) // base case 
                p = pos[i]; 
            else if (p > pos[i]) 
                p = pos[i]; 
        } 
    }

    //Cari karakter tertentu
    for (i = 0; i < n; i++) { 
        if (s[i] == b) { 
            m = true;
            break; 
        }
    } 
    return ((p > -1)||(m)) ? true:false; 
}

result isi_Pin_Manual_Otomatis(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  byte a;
  byte j = root.path[0].sel; //Menu Utama
  byte k = root.path[1].sel; //Menu tingkat satu
  //byte l = root.path[2].sel; //Menu tingkat dua
  //byte m = root.path[3].sel; //Menu tingkat tiga
  //byte n = root.path[4].sel; //Menu tingkat empat

  if (isi) {
    switch(j) {
      case 1: {//Gerbang Logika
          switch(k) {
            case 0: {//2 input logic gate
              strcpy_P(DataPinEdit[1], (const char*)pgm_read_dword(&(DPE_Isi[1])));
              break;}   
            case 1: {//3 input logic gate
              strcpy_P(DataPinEdit[3], (const char*)pgm_read_dword(&(DPE_Isi[3])));
              break;}   
          }
          strcpy_P(DataPinEdit[0], (const char*)pgm_read_dword(&(DPE_Isi[0])));
          break;}
      case 2: {//Adder (IC 74xx283)
          switch(k) {//4 bit adder (1 IC)
            case 0: {
              strcpy_P(DataPinEdit[6], (const char*)pgm_read_dword(&(DPE_Isi[6])));
              strcpy_P(DataPinEdit[7], (const char*)pgm_read_dword(&(DPE_Isi[7])));
              strcpy_P(DataPinEdit[8], (const char*)pgm_read_dword(&(DPE_Isi[8])));
              strcpy_P(DataPinEdit[0], (const char*)pgm_read_dword(&(DPE_Isi[16])));
              strcpy_P(DataPinEdit[16], (const char*)pgm_read_dword(&(DPE_Isi[17])));
              break;}  
            case 1: {//8 bit adder (2 IC)
              strcpy_P(DataPinEdit[9], (const char*)pgm_read_dword(&(DPE_Isi[9])));
              strcpy_P(DataPinEdit[10], (const char*)pgm_read_dword(&(DPE_Isi[10])));
              strcpy_P(DataPinEdit[11], (const char*)pgm_read_dword(&(DPE_Isi[11])));
              strcpy_P(DataPinEdit[0], (const char*)pgm_read_dword(&(DPE_Isi[18])));
              strcpy_P(DataPinEdit[16], (const char*)pgm_read_dword(&(DPE_Isi[19])));
              break;}
          }
          break;}
      case 3: {//Comparator (74xx85)
          switch(k) {
            case 0: {//4 bit comp. (1 IC)
              strcpy_P(DataPinEdit[6], (const char*)pgm_read_dword(&(DPE_Isi[20])));
              strcpy_P(DataPinEdit[7], (const char*)pgm_read_dword(&(DPE_Isi[21])));
              break;}  
            case 1: {//8 bit comp. (2 IC)
              strcpy_P(DataPinEdit[9], (const char*)pgm_read_dword(&(DPE_Isi[9])));
              strcpy_P(DataPinEdit[10], (const char*)pgm_read_dword(&(DPE_Isi[10])));
              break;}  
          }
          strcpy_P(DataPinEdit[15], (const char*)pgm_read_dword(&(DPE_Isi[15])));
          break;}
      case 4: {//Encoder
          switch(k) {
            case 0: {//Enc. 8 → 3 (74xx148)
              strcpy_P(DataPinEdit[12], (const char*)pgm_read_dword(&(DPE_Isi[12])));
              strcpy_P(DataPinEdit[4], (const char*)pgm_read_dword(&(DPE_Isi[4])));
              strcpy_P(DataPinEdit[0], (const char*)pgm_read_dword(&(DPE_Isi[26])));
              break;}  
            case 1: {//Enc. 10 → 4 (74xx147)
              strcpy_P(DataPinEdit[14], (const char*)pgm_read_dword(&(DPE_Isi[14])));
              strcpy_P(DataPinEdit[6], (const char*)pgm_read_dword(&(DPE_Isi[22])));
              break;}  
          }
          break;}
      case 5: {//Decoder
          switch(k) {
            case 0: {//Dec. 3 → 8 (74xx138)
              strcpy_P(DataPinEdit[4], (const char*)pgm_read_dword(&(DPE_Isi[23])));
              strcpy_P(DataPinEdit[12], (const char*)pgm_read_dword(&(DPE_Isi[24])));
              break;}  
            case 1: {//Dec. 4 → 10 (74xx42)
              strcpy_P(DataPinEdit[6], (const char*)pgm_read_dword(&(DPE_Isi[20])));
              strcpy_P(DataPinEdit[5], (const char*)pgm_read_dword(&(DPE_Isi[5])));
              break;}  
          }
          break;}
      //Multiplexer
      case 6: {//Mux 8 → 1 (74xx151)
        strcpy_P(DataPinEdit[12], (const char*)pgm_read_dword(&(DPE_Isi[27])));
        strcpy_P(DataPinEdit[4], (const char*)pgm_read_dword(&(DPE_Isi[25])));
        strcpy_P(DataPinEdit[2], (const char*)pgm_read_dword(&(DPE_Isi[2])));
        break;}        
      //Demultiplexer
      case 7: {//Demux 1→8 (74xx138)
        strcpy_P(DataPinEdit[13], (const char*)pgm_read_dword(&(DPE_Isi[13])));
        strcpy_P(DataPinEdit[4], (const char*)pgm_read_dword(&(DPE_Isi[25])));
        strcpy_P(DataPinEdit[12], (const char*)pgm_read_dword(&(DPE_Isi[24])));
        break;}            
    }
  }
  else {
    for (a = 0; a < 17; a++){strcpy_P(DataPinEdit[a], (const char*)pgm_read_dword(&(DPE_PROG[a])));}
  }

  return proceed;
}

result Inisialisasi_Input(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  byte a = root.path[0].sel; //Menu Utama
  byte b = root.path[1].sel; //Menu tingkat satu
  byte c = root.path[2].sel; //Menu tingkat dua
  String str;
  switch(a) {
    //Tetapkan basis (base) konversi bilangan
    case 0: {//Konversi Bilangan
        switch(c) {
          case 0: {//Bilangan Biner
            base1 = BIN;
            base2 = OCT; 
            break;}   
          case 1: {//Bilangan Oktal
            base1 = OCT;
            base2 = BIN;
            break;}
          case 2: {//Bilangan Desimal
            base1 = DEC;
            base2 = BIN;
            break;}   
          case 3: {//Bilangan Heksadesimal
            base1 = HEX;
            base2 = BIN;
            break;} 
        }
        break;}
    //Tetapkan jumlah input untuk rangkaian
    case 1: {//Gerbang Logika
        switch(b) {
          case 0: {Jlh_Char = 3; break;}   //2 input logic gate
          case 1: {Jlh_Char = 4; break;}   //3 input logic gate
        }
        str = bil[3][1]?" 1 (HIGH)":" 0 (LOW)";
        break;}
    case 2: {//Adder (IC 74xx283)
        switch(b) {//4 bit adder (1 IC)
          case 0: {
            Jlh_Char = 14;
            str = &DataPinLogic[6][0]; 
            break;}  
          case 1: {//8 bit adder (2 IC)
            Jlh_Char = 26;
            str = &DataPinLogic[9][0];
            break;}
        }
        break;}
    case 3: {//Comparator (74xx85)
        switch(b) {
          case 0: {Jlh_Char = 12; break;}  //4 bit comp. (1 IC)
          case 1: {Jlh_Char = 19; break;}  //8 bit comp. (2 IC)
        }
        str = &DataPinLogic[13][0];
        break;}
    case 4: {//Encoder
        switch(b) {
          case 0: {//Enc. 8 → 3 (74xx148)
            Jlh_Char = 12;
            str = &DataPinLogic[2][0]; 
            break;}  
          case 1: {//Enc. 10 → 4 (74xx147)
            Jlh_Char = 13; 
            str = &DataPinLogic[4][0];
            break;}  
        }
        break;}
    case 5: {//Decoder
        switch(b) {
          case 0: {//Dec. 3 → 8 (74xx138)
            Jlh_Char = 11; 
            str = &DataPinLogic[10][0];
            break;}  
          case 1: {//Dec. 4 → 10 (74xx42)
            Jlh_Char = 14; 
            str = &DataPinLogic[3][0];
            break;}  
        }
        break;}
    //Multiplexer
    case 6: {//Mux 8 → 1 (74xx151)
      Jlh_Char = 13;
      str = &DataPinLogic[1][0]; 
      break;}        
    //Demultiplexer
    case 7: {//Demux 1→8 (74xx138)
      Jlh_Char = 14;
      str = &DataPinLogic[10][0]; 
      break;}            
  }

  str.toCharArray(*(DPL + 14),(str.length()+1));
  return proceed;
}

result checkInput(eventMask e,navNode& nav,prompt& item) {
  extern menu SP1,SP11,SP2,SP21,SP3,SP31,SP4,SP41,SP5,SP51,SP6,SP7;
  navRoot& root = *nav.root;
  byte j = root.path[0].sel; //Menu Utama
  byte k = root.path[1].sel; //Menu tingkat satu
  //byte l = root.path[2].sel; //Menu tingkat dua
  //byte m = root.path[3].sel; //Menu tingkat tiga
  //byte n = root.path[4].sel; //Menu tingkat empat
  char InChar[Jlh_Char];
  byte a;

  switch(j) {
    case 1: {//Gerbang Logika
        switch(k) {
          case 0: {//2 input logic gate
            for(a = 0; a < 4; a+=2) {InChar[a/2] = DataPinEdit[1][a+3];}
            InChar[2] = DataPinEdit[0][0];
    
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya" 
            SP11[2].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus; 
            break;}   
          case 1: {//3 input logic gate
            for(a = 0; a < 6; a+=2) {InChar[a/2] = DataPinEdit[3][a+3];}
            InChar[3] = DataPinEdit[0][0];
    
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP1[2].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}   
        }
        break;}
    case 2: {//Adder (IC 74xx283)
        switch(k) {//4 bit adder (1 IC)
          case 0: {
            for(a = 0; a < 8; a+=2) {
              InChar[a/2] = DataPinEdit[6][a+3];
              InChar[(a/2)+4] = DataPinEdit[7][a+3];
              InChar[(a/2)+8] = DataPinEdit[8][a+3];
            }
            InChar[12] = DataPinEdit[0][0];
            InChar[13] = DataPinEdit[16][0];
    
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP21[5].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
          case 1: {//8 bit adder (2 IC)
            for(a = 0; a < 8; a++) {
              InChar[a] = DataPinEdit[9][a+3];
              InChar[a+8] = DataPinEdit[10][a+3];
              InChar[a+16] = DataPinEdit[11][a+3];
            }
            InChar[24] = DataPinEdit[0][0];
            InChar[25] = DataPinEdit[16][0];

            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP2[5].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}
        }
        break;}
    case 3: {//Comparator (74xx85)
        switch(k) {
          case 0: {//4 bit comp. (1 IC)
            for(a = 0; a < 8; a+=2) {
              InChar[a/2] = DataPinEdit[6][a+3];
              InChar[(a/2)+4] = DataPinEdit[7][a+3];
            }
            for(a = 0; a < 18; a+=6) InChar[(a/6)+8] = DataPinEdit[15][a+4];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP31[3].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
          case 1: {//8 bit comp. (2 IC)
            for(a = 0; a < 8; a++) {
              InChar[a] = DataPinEdit[9][a+3];
              InChar[a+8] = DataPinEdit[10][a+3];
            }
            for(a = 0; a < 18; a+=6) InChar[(a/6)+16] = DataPinEdit[15][a+4];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP3[3].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
        }
        break;}
    case 4: {//Encoder
        switch(k) {
          case 0: {//Enc. 8 → 3 (74xx148)
            InChar[0] = DataPinEdit[0][0];
            for(a = 0; a < 8; a++) InChar[a+1] = DataPinEdit[12][a+3];
            for(a = 0; a < 6; a+=2) InChar[(a/2)+9] = DataPinEdit[4][a+3];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP41[3].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
          case 1: {//Enc. 10 → 4 (74xx147)
            for(a = 0; a < 9; a++) InChar[a] = DataPinEdit[14][a+3];
            for(a = 0; a < 8; a+=2) InChar[(a/2)+9] = DataPinEdit[6][a+3];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP4[2].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
        }
        break;}
    case 5: {//Decoder
        switch(k) {
          case 0: {//Dec. 3 → 8 (74xx138)
            for(a = 0; a < 6; a+=2) InChar[a/2] = DataPinEdit[4][a+3];
            for(a = 0; a < 8; a++) InChar[a+3] = DataPinEdit[12][a+3];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP51[2].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
          case 1: {//Dec. 4 → 10 (74xx42)
            for(a = 0; a < 8; a+=2) InChar[a/2] = DataPinEdit[6][a+3];
            for(a = 0; a < 10; a++) InChar[a+4] = DataPinEdit[5][a+3];
            
            //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
            SP5[2].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
            break;}  
        }
        break;}
    //Multiplexer
    case 6: {//Mux 8 → 1 (74xx151)
      for(a = 0; a < 8; a++) InChar[a] = DataPinEdit[12][a+3];
      for(a = 0; a < 6; a+=2) InChar[(a/2)+8] = DataPinEdit[4][a+3];
      for(a = 0; a < 8; a+=4) {InChar[(a/4)+11] = DataPinEdit[2][a+3];}
      
      //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
      SP6[3].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
      break;}        
    //Demultiplexer
    case 7: {//Demux 1→8 (74xx138)
      InChar[0] = DataPinEdit[13][3];
      for(a = 0; a < 4; a+=2) InChar[(a/5)+1] = DataPinEdit[13][a+10];
      for(a = 0; a < 6; a+=2) InChar[(a/2)+3] = DataPinEdit[4][a+3];
      for(a = 0; a < 8; a++) InChar[a+6] = DataPinEdit[12][a+3];
      
      //Jika input karakter ganda dan terdapat karakter '-' maka disable submenu "> Selanjutnya"
      SP7[3].enabled = findRepeatChar(InChar,'-')?disabledStatus:enabledStatus;
      break;}            
  }
  
  Serial.println(F("                                                                             "));
  Serial.println(F("                                                                             "));
  Serial.println(F("-----------------------------------------------------------------------------"));
  Serial.println(F("// |-X-|  Periksa semua input huruf atau karakter....                      //"));
  Serial.println(F("// |-X-|  Jika ditemukan karakter ganda dan karakter '-' (tidak diisi).... //"));
  Serial.println(F("// |-X-|  Maka disable submenu (> Selanjutnya) ....                        //"));
  Serial.println(F("-----------------------------------------------------------------------------"));
  Serial.println(InChar);
  return proceed;
}

result setPin(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  byte j = root.path[0].sel; //Menu Utama
  byte k = root.path[1].sel; //Menu tingkat satu
  //byte l = root.path[2].sel; //Menu tingkat dua
  //byte m = root.path[3].sel; //Menu tingkat tiga
  //byte n = root.path[4].sel; //Menu tingkat empat
  char InChar[Jlh_Char];
  String str;
  byte a;

  switch(j) {
    case 1: {//Gerbang Logika
        Perintah(2,0,0,3,0,0,1);
        switch(k) {
          case 0: {//2 input logic gate
            for(a = 0; a < 4; a+=2)Perintah(1,1,(a+3),(a/2),0,0,1);
            break;}   
          case 1: {//3 input logic gate
            for(a = 0; a < 6; a+=2)Perintah(1,3,(a+3),(a/2),0,0,1);
            break;}   
        }
        str = bil[3][1]?" 1 (HIGH)":" 0 (LOW)";
        break;}
    case 2: {//Adder (IC 74xx283)
        Perintah(1,0,0,24,0,0,1);
        Perintah(2,16,0,25,0,0,1);
        str = bil[25][1]?" 1 (HIGH)":" 0 (LOW)";
        str.toCharArray(*(DPL + 15),(str.length()+1));
        switch(k) {//4 bit adder (1 IC)
          case 0: {
            for(a = 0; a < 8; a+=2){
              Perintah(1,6,(a+3),(a/2),0,0,1);
              Perintah(1,7,(a+3),((a/2)+4),0,0,1);
              Perintah(2,8,(a+3),((a/2)+8),0,0,1);
            }
            str = &DataPinLogic[6][0];
            break;}  
          case 1: {//8 bit adder (2 IC)
            for(a = 0; a < 8; a++){
              Perintah(1,9,(a+3),a,0,0,1);
              Perintah(1,10,(a+3),(a+8),0,0,1);
              Perintah(2,11,(a+3),(a+16),0,0,1);
            }
            str = &DataPinLogic[9][0];
            break;}
        }
        break;}
    case 3: {//Comparator (74xx85)
        for(a = 0; a < 18; a+=6) Perintah(2,15,(a+4),((a/6)+16),0,0,1);
        switch(k) {
          case 0: {//4 bit comp. (1 IC)
            for(a = 0; a < 8; a+=2){
              Perintah(1,6,(a+3),(a/2),0,0,1);
              Perintah(1,7,(a+3),((a/2)+4),0,0,1);
            }
            break;}  
          case 1: {//8 bit comp. (2 IC)
            for(a = 0; a < 8; a++){
              Perintah(1,9,(a+3),a,0,0,1);
              Perintah(1,10,(a+3),(a+8),0,0,1);
            }
            break;}  
        }
        str = &DataPinLogic[13][0];
        break;}
    case 4: {//Encoder
        switch(k) {
          case 0: {//Enc. 8 → 3 (74xx148)
            for(a = 0; a < 8; a++)Perintah(1,12,(a+3),a,0,0,1);
            for(a = 0; a < 6; a+=2)Perintah(2,4,(a+3),((a/2)+8),0,0,1);
            Perintah(1,0,0,11,0,0,1);
            str = &DataPinLogic[2][0];
            break;}  
          case 1: {//Enc. 10 → 4 (74xx147)
            for(a = 0; a < 9; a++)Perintah(1,14,(a+3),a,0,0,1);
            for(a = 0; a < 8; a+=2)Perintah(2,6,(a+3),((a/2)+9),0,0,1);
            str = &DataPinLogic[4][0];
            break;}  
        }
        break;}
    case 5: {//Decoder
        switch(k) {
          case 0: {//Dec. 3 → 8 (74xx138)
            for(a = 0; a < 6; a+=2)Perintah(1,4,(a+3),(a/2),0,0,1);
            for(a = 0; a < 8; a++)Perintah(2,12,(a+3),(a+3),0,0,1);
            str = &DataPinLogic[10][0];
            break;}  
          case 1: {//Dec. 4 → 10 (74xx42)
            for(a = 0; a < 8; a+=2)Perintah(1,6,(a+3),(a/2),0,0,1);
            for(a = 0; a < 10; a++)Perintah(2,5,(a+3),(a+4),0,0,1);
            str = &DataPinLogic[3][0];
            break;}  
        }
        break;}
    //Multiplexer
    case 6: {//Mux 8 → 1 (74xx151)
      for(a = 0; a < 8; a++)Perintah(1,12,(a+3),a,0,0,1);
      for(a = 0; a < 6; a+=2)Perintah(1,4,(a+3),((a/2)+8),0,0,1);
      for(a = 0; a < 8; a+=4)Perintah(2,2,(a+3),((a/4)+11),0,0,1);
      str = &DataPinLogic[1][0];
      break;}        
    //Demultiplexer
    case 7: {//Demux 1→8 (74xx138)
      Perintah(1,13,3,0,0,0,1);
      for(a = 0; a < 4; a+=2)Perintah(1,13,(a+10),((a/2)+1),0,0,1);
      for(a = 0; a < 6; a+=2)Perintah(1,4,(a+3),((a/2)+3),0,0,1);
      for(a = 0; a < 8; a++)Perintah(2,12,(a+3),(a+6),0,0,1);
      str = &DataPinLogic[10][0];
      break;}            
  }

  str.toCharArray(*(DPL + 14),(str.length()+1));
  return proceed;
}

result logicControl(eventMask e,navNode& nav,prompt& item) {
  menuNode& target = *nav.target;
  navRoot& root = *nav.root;
  byte j = root.path[0].sel; //Menu Utama
  byte k = root.path[1].sel; //Menu tingkat satu
  //byte l = root.path[2].sel; //Menu tingkat dua
  //byte m = root.path[3].sel; //Menu tingkat tiga
  byte n = root.path[4].sel; //Menu tingkat empat
  byte a;
  String str;

  //Tukar Nilai A dan B pada rangkaian adder dan comparator
  if ((n == 2)&&((j == 2)||(j == 3))) {
    switch(k) {
      case 0: {//4 bit
        char tmp[4];
        for(a = 0; a < 8; a+=2){
          tmp[a/2] = DataPinLogic[4][a+3];
          DataPinLogic[4][a+3] = DataPinLogic[5][a+3];
          DataPinLogic[5][a+3] = tmp[a/2];
        }
        break;}   
      case 1: {//8 bit
        char tmp[8];
        for(a = 0; a < 8; a++){
          tmp[a] = DataPinLogic[7][a+3];
          DataPinLogic[7][a+3] = DataPinLogic[8][a+3];
          DataPinLogic[8][a+3] = tmp[a];
        }
        break;}   
    }
  }
  //Set semua nilai input menjadi HIGH
  else if ((n == 0)&&(j == 4)) {
    switch(k) {
      case 0: {//Enc. 8 → 3 (74xx148)
        for(a = 0; a < 8; a++) *(*(DPL + 10) + (a+3)) = '1';
        bil[11][1] = 1;
        break;}   
      case 1: {//Enc. 10 → 4 (74xx147)
        for(a = 0; a < 9; a++) *(*(DPL + 12) + (a+3)) = '1';
        break;}   
    }
  }

  switch(j) {
    case 1: {//Gerbang Logika
        Perintah(5,1,2,3,0,0,1);
        switch(k) {
          case 0: {//2 input logic gate
            Perintah(3,2,0,0,0,0,2);
            break;}   
          case 1: {//3 input logic gate
            Perintah(3,3,0,0,0,0,2);
            break;}   
        }
        str = bil[3][1]?" 1 (HIGH)":" 0 (LOW)";
        break;}
    case 2: {//Adder (IC 74xx283)
        Perintah(3,1,2,24,0,0,1);
        Perintah(6,1,2,25,15,0,1);
        str = bil[25][1]?" 1 (HIGH)":" 0 (LOW)";
        str.toCharArray(*(DPL + 15),(str.length()+1));
        switch(k) {//4 bit adder (1 IC)
          case 0: {
            Perintah(4,4,0,0,4,3,2);
            Perintah(4,4,1,4,5,3,2);
            Perintah(6,4,1,8,6,3,2);
            str = &DataPinLogic[6][0];
            break;}  
          case 1: {//8 bit adder (2 IC)
            Perintah(4,8,0,0,7,3,1);
            Perintah(4,8,1,8,8,3,1);
            Perintah(6,8,1,16,9,3,1);
            str = &DataPinLogic[9][0];
            break;}
        }
        break;}
    case 3: {//Comparator (74xx85)
        Perintah(6,3,1,16,13,4,7);
        switch(k) {
          case 0: {//4 bit comp. (1 IC)
            Perintah(4,4,0,0,4,3,2);
            Perintah(4,4,1,4,5,3,2);
            break;}  
          case 1: {//8 bit comp. (2 IC)
            Perintah(4,8,0,0,7,3,1);
            Perintah(4,8,1,8,8,3,1);
            break;}  
        }
        str = &DataPinLogic[13][0];
        break;}
    case 4: {//Encoder
        switch(k) {
          case 0: {//Enc. 8 → 3 (74xx148)
            Perintah(4,8,0,0,10,3,1);
            Perintah(6,3,1,8,2,3,2);
            Perintah(3,1,2,11,0,0,1);
            str = &DataPinLogic[2][0];
            break;}  
          case 1: {//Enc. 10 → 4 (74xx147)
            Perintah(4,9,0,0,12,3,1);
            Perintah(6,4,1,9,4,3,2);
            str = &DataPinLogic[4][0];
            break;}  
        }
        break;}
    case 5: {//Decoder
        switch(k) {
          case 0: {//Dec. 3 → 8 (74xx138)
            Perintah(4,3,0,0,2,3,2);
            Perintah(6,8,1,3,10,3,1);
            str = &DataPinLogic[10][0];
            break;}  
          case 1: {//Dec. 4 → 10 (74xx42)
            Perintah(4,4,0,0,4,3,2);
            Perintah(6,10,1,4,3,3,1);
            str = &DataPinLogic[3][0];
            break;}  
        }
        break;}
    //Multiplexer
    case 6: {//Mux 8 → 1 (74xx151)
      Perintah(4,8,0,0,10,3,1);
      Perintah(4,3,1,8,16,3,2);
      Perintah(6,2,1,11,1,3,4);
      str = &DataPinLogic[1][0];
      break;}        
    //Demultiplexer
    case 7: {//Demux 1→8 (74xx138)
      Perintah(3,3,0,0,0,0,2);
      Perintah(4,3,1,3,16,3,2);
      Perintah(6,8,1,6,10,3,1);
      str = &DataPinLogic[10][0];
      break;}            
  }
  
  str.toCharArray(*(DPL + 14),(str.length()+1));
  target.dirty = true; //Refresh layar
  return proceed;
}

result Konversi_Bilangan(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  //byte a = root.path[0].sel; //Menu Utama
  //byte b = root.path[1].sel; //Menu tingkat satu
  byte c = root.path[2].sel; //Menu tingkat dua
  byte d = root.path[3].sel; //Menu tingkat tiga
  String tmp;
  long value;
  
  //Jika terdapat bilangan biner "-00000 (Desimal)" maka ubah menjadi " 00000 (Desimal)"
  if ((d == 0)&&(c == 2)) {
    if (strcmp_P(&TxtBil[1][0], TB_PROG[5]) == 0){
      strcpy_P(TxtBil[1], (const char*)pgm_read_dword(&(TB_PROG[1])));
    }
  }
  //Ubah tanda bilangan dengan cara komplemen kedua
  else if (d == 1) fungsi_Tanda(*nav.target);
  
  //Input Bilangan
  switch(base1) {
    case BIN:  {//Bilangan Biner
        tmp = KonBIL(TxtBil[3],base1,DEC);
        if ((tmp.toInt() < 0)&&(!Sign)) Sign = 1;
        else if ((tmp.toInt() >= 0)&&(Sign)) Sign = 0;
        //Konversi ke Bilangan.......
        switch(base2) {
          case OCT: {//Bilangan Oktal
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
          case DEC: {//Bilangan Desimal
            tmp = KonBIL(TxtBil[3],base1,DEC);
            break;}
          case HEX: {//Bilangan Heksadesimal
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
        }
        break;}
    case OCT:  {//Bilangan Oktal
        tmp = (String)&TxtBil[0][0];
        value = tmp.toInt();
        tmp = String(value);
        if ((value > 177777)&&(d == 0)) { //(i == "a") ===> (d == 0) 
          tmp = "177777";
          tmp += " (Oktal)";
          tmp.toCharArray(*(TBl + 0), (tmp.length()+1));
          Sign = 1;
        } else tmp = KonBIL(TxtBil[0],base1,DEC);
        if ((tmp.toInt() < 0)&&(!Sign)) Sign = 1;
        else if ((tmp.toInt() >= 0)&&(Sign)) Sign = 0;
        //Konversi ke Bilangan.......
        switch(base2) {
          case BIN: {//Bilangan Biner
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
          case DEC: {//Bilangan Desimal
            tmp = KonBIL(TxtBil[0],base1,DEC);
            break;}
          case HEX: {//Bilangan Heksadesimal
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
        }
        break;}
    case DEC: {//Bilangan Desimal
        tmp = (String)&TxtBil[1][0];
        value = tmp.toInt();
        tmp = String(value);
        if (d == 0) { //(i == "14") ===> (d == 0)
          if (value > 32767) {
            tmp = " 32767";
            tmp += " (Desimal)";
            tmp.toCharArray(*(TBl + 1), (tmp.length()+1));
            Sign = 0;
          }else if (value < -32768) {
            tmp = "-32768";
            tmp += " (Desimal)";
            tmp.toCharArray(*(TBl + 1), (tmp.length()+1));
            Sign = 1;
          }
        }
        if ((value < 0)&&(!Sign)) Sign = 1;
        else if ((value >= 0)&&(Sign)) Sign = 0;
        //Konversi ke Bilangan.......
        switch(base2) {
          case BIN: {//Bilangan Biner
            tmp = KonBIL(TxtBil[1],DEC,base2);
            break;}
          case OCT: {//Bilangan Oktal
            tmp = KonBIL(TxtBil[1],DEC,base2);
            break;}
          case HEX: {//Bilangan Heksadesimal
            tmp = KonBIL(TxtBil[1],DEC,base2);
            break;}
        }
        break;}
    case HEX: {//Bilangan Heksadesimal
        tmp = KonBIL(TxtBil[2],base1,DEC);
        if ((tmp.toInt() < 0)&&(!Sign)) Sign = 1;
        else if ((tmp.toInt() >= 0)&&(Sign)) Sign = 0;
        //Konversi ke Bilangan.......
        switch(base2) {
          case BIN: {//Bilangan Biner
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
          case OCT: {//Bilangan Oktal
            tmp = KonBIL(&tmp[0],DEC,base2);
            break;}
          case DEC: {//Bilangan Desimal
            tmp = KonBIL(TxtBil[2],base1,DEC);
            break;}
        }
        break;}
  }
  
  tmp.toCharArray(*(TBl + 4), (tmp.length()+1));
  return proceed;
}

result keMenuUtama(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  byte a = root.path[0].sel; //Menu Utama
  //byte b = root.path[1].sel; //Menu tingkat satu
  //byte c = root.path[2].sel; //Menu tingkat dua
  //byte d = root.path[3].sel; //Menu tingkat tiga
  byte f;
  nav.root->level = 0; // go to mainMenu
  if (a == 0) { 
    for (f = 0; f < 5; f++){strcpy_P(TxtBil[f], (const char*)pgm_read_dword(&(TB_PROG[f])));}  //Reset text bilangan ke nilai awal (karakter '0')
    Sign = LOW;
  }
  else {
    for (f = 0; f < 17; f++){
      strcpy_P(DataPinEdit[f], (const char*)pgm_read_dword(&(DPE_PROG[f])));  //Reset input Pin Edit ke nilai awal (karakter '-')
      strcpy_P(DataPinLogic[f], (const char*)pgm_read_dword(&(DPL_PROG[f]))); //Reset input Pin Logic ke nilai awal (karakter '0')
    }
    for (f = 0; f < 26; f++){ //Set seluruh nilai variabel bil[26][2] ke nol
      bil[f][0] = 0;
      bil[f][1] = 0;
    }
    for (f = 1; f < 27; f++){ //Set Pin ke default
      digitalWrite(((const byte*)pgm_read_word(&Pin_IO[f][1])),LOW);
      pinMode(((const byte*)pgm_read_word(&Pin_IO[f][1])),INPUT);
    }
    isi = 0;
  }
  return proceed;
}

result keluar_kembali(eventMask e,navNode& nav,prompt& item) {
  navRoot& root = *nav.root;
  //byte j = root.path[0].sel; //Menu Utama
  //byte k = root.path[1].sel; //Menu tingkat satu
  //byte l = root.path[2].sel; //Menu tingkat dua
  byte m = root.path[3].sel; //Menu tingkat tiga
  //byte n = root.path[4].sel; //Menu tingkat empat
  byte rt = nav.root->level; // tingkat menu
  byte a;
  //Keluar dari Menu Utama
  if (rt == 0) { //(i == "8")                                      
    for (a = 0; a < 3; a++) ST[a] = false;
    for (a = 0; a < 4; a++) st[a] = 0;
  }
  //Keluar dari Submenu konversi bilangan
  else if ((rt == 3)&&(m == 5)) {                              
    for (a = 0; a < 5; a++){strcpy_P(TxtBil[a], (const char*)pgm_read_dword(&(TB_PROG[a])));}  //Reset text bilangan ke nilai awal (karakter '0')
    Sign = 0;
  }
  //Keluar dari Submenu Pin Edit
  else if (rt == 3) { 
    for (a = 0; a < 17; a++){strcpy_P(DataPinEdit[a], (const char*)pgm_read_dword(&(DPE_PROG[a])));}  //Reset input Pin Edit ke nilai awal (karakter '-')
    isi = 0;
  }
  //Keluar dari Submenu Pin Logic
  else if (rt == 4) { 
    for (a = 0; a < 17; a++){strcpy_P(DataPinLogic[a], (const char*)pgm_read_dword(&(DPL_PROG[a])));} //Reset input Pin Logic ke nilai awal (karakter '0')
    for (a = 0; a < 26; a++){ //Set seluruh nilai variabel bil[26][2] ke nol
      bil[a][0] = 0;
      bil[a][1] = 0;
    }
    for (a = 1; a < 27; a++){ //Set Pin ke default
      digitalWrite(((const byte*)pgm_read_word(&Pin_IO[a][1])),LOW);
      pinMode(((const byte*)pgm_read_word(&Pin_IO[a][1])),INPUT);
    }
    isi = 0;
  }
  if(isi) {//Jika perintah "keluar dari Submenu Pin Edit" tidak dilaksanakan langsung reset kembali
    for (a = 0; a < 17; a++){strcpy_P(DataPinEdit[a], (const char*)pgm_read_dword(&(DPE_PROG[a])));}  //Reset input Pin Edit ke nilai awal (karakter '-')
    isi = 0;
  }
  return quit;
}
