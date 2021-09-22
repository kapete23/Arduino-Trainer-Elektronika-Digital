#include <Wire.h>
#include <menu.h>                                 //menu macros and objects
#include <LiquidCrystal.h>
#include <NoDelay.h>                              //library (class) delay non-blocking menggunakan millis()

//Library sistem menu di download disini : https://github.com/neu-rah/ArduinoMenu
#include <menuIO/keyIn.h>                         //keyboard driver and fake stream (for the encoder button)
#include <menuIO/serialIn.h>
#include <menuIO/serialOut.h>
#include <menuIO/encoderIn.h>                     //quadrature encoder driver and fake stream
#include <menuIO/chainStream.h>                   //concatenate multiple input streams (this allows adding a button to the encoder)
#include <menuIO/liquidCrystalOut.h>
#include "inisialisasi_LCD_Serial_rotaryEncoder.h"
#include "deklarasi_Variabel.h"
#include "kumpulan_Fungsi.h"
#include "Kumpulan_Class_Custom_Prompt.h"

using namespace Menu;

//Isi dari menu utama
//Konversi bilangan
TOGGLE(Sign,SGN,"Ubah tanda bil ke ",Konversi_Bilangan,anyEvent,wrapStyle
  ,VALUE("+",1,Konversi_Bilangan,enterEvent)
  ,VALUE("-",0,Konversi_Bilangan,enterEvent)
);
  
SELECT(base2,kon8,"Konversi ke",Konversi_Bilangan,noEvent,wrapStyle
  ,VALUE("Biner",BIN,Konversi_Bilangan,anyEvent)
  ,VALUE("Oktal",OCT,Konversi_Bilangan,anyEvent)
  ,VALUE("Desimal",DEC,Konversi_Bilangan,anyEvent)
);

MENU(kon4,"Bilangan Heksadesimal",Inisialisasi_Input,enterEvent,noStyle
  ,EDIT("\x0F",TxtBil[2],hexNr,Konversi_Bilangan,anyEvent,noStyle)
  ,SUBMENU(SGN)
  ,SUBMENU(kon8)
  ,altOP(displayKonversi,"= ",Konversi_Bilangan,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

SELECT(base2,kon7,"Konversi ke",Konversi_Bilangan,noEvent,wrapStyle
  ,VALUE("Biner",BIN,Konversi_Bilangan,anyEvent)
  ,VALUE("Oktal",OCT,Konversi_Bilangan,anyEvent)
  ,VALUE("Heksa",HEX,Konversi_Bilangan,anyEvent)
);

MENU(kon3,"Bilangan Desimal",Inisialisasi_Input,enterEvent,noStyle
  ,EDIT("\x0F",TxtBil[1],decNr,Konversi_Bilangan,anyEvent,noStyle)
  ,SUBMENU(SGN)
  ,SUBMENU(kon7)
  ,altOP(displayKonversi,"= ",Konversi_Bilangan,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

SELECT(base2,kon6,"Konversi ke",Konversi_Bilangan,noEvent,wrapStyle
  ,VALUE("Biner",BIN,Konversi_Bilangan,anyEvent)
  ,VALUE("Desimal",DEC,Konversi_Bilangan,anyEvent)
  ,VALUE("Heksa",HEX,Konversi_Bilangan,anyEvent)
);

MENU(kon2,"Bilangan Oktal",Inisialisasi_Input,enterEvent,noStyle
  ,EDIT("\x0F",TxtBil[0],octNr,Konversi_Bilangan,anyEvent,noStyle)
  ,SUBMENU(SGN)
  ,SUBMENU(kon6)
  ,altOP(displayKonversi,"= ",Konversi_Bilangan,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

SELECT(base2,kon5,"Konversi ke",Konversi_Bilangan,noEvent,wrapStyle
  ,VALUE("Oktal",OCT,Konversi_Bilangan,anyEvent)
  ,VALUE("Desimal",DEC,Konversi_Bilangan,anyEvent)
  ,VALUE("Heksa",HEX,Konversi_Bilangan,anyEvent)
);

MENU(kon1,"Bilangan Biner",Inisialisasi_Input,enterEvent,noStyle
  ,EDIT("\x0F",TxtBil[3],binNr,Konversi_Bilangan,anyEvent,noStyle)
  ,SUBMENU(SGN)
  ,SUBMENU(kon5)
  ,altOP(displayKonversi,"= ",Konversi_Bilangan,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(kon0,"Pilih Input Bilangan",doNothing,anyEvent,noStyle
  ,SUBMENU(kon1)  //Bilangan biner
  ,SUBMENU(kon2)  //Bilangan oktal
  ,SUBMENU(kon3)  //Bilangan desimal
  ,SUBMENU(kon4)  //Bilangan heksadesimal
  ,EXIT("< Kembali")
);

MENU(kon,"Konversi Bilangan",doNothing,anyEvent,noStyle
  ,SUBMENU(kon0)
  ,EXIT("< Kembali")
);

//Fungsi submenu untuk memilih mengisi pin edit secara manual atau otomatis
SELECT(isi,isi_PIN_Menu,"Input Pin \x7F",doNothing,noEvent,wrapStyle
  ,VALUE("Kosong",0,isi_Pin_Manual_Otomatis,enterEvent)
  ,VALUE("Terisi",1,isi_Pin_Manual_Otomatis,enterEvent)
);

//Gerbang Logika
//3 Input
PADMENU(inLgc,"In",logicControl,anyEvent,noStyle
  ,FIELD(bil[0][1],"S0","",0,1,1,0,logicControl,anyEvent,wrapStyle)
  ,FIELD(bil[1][1],"S1","",0,1,1,0,logicControl,anyEvent,wrapStyle)
  ,FIELD(bil[2][1],"S2","",0,1,1,0,logicControl,anyEvent,wrapStyle)
);

MENU(next1,"> Selanjutnya",setPin,enterEvent,noStyle
  ,SUBMENU(inLgc)
  ,altOP(outLogic,"Output Y :",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP1,"Setting pin in/out",doNothing,anyEvent,noStyle
  ,EDIT("Input \x7F",DataPinEdit[3],TxtPEdit3,checkInput,anyEvent,noStyle)
  ,EDIT("Output Y\x7F",DataPinEdit[0],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,SUBMENU(next1)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

//2 Input
PADMENU(InLgc,"Input",logicControl,anyEvent,noStyle
  ,FIELD(bil[0][1],"S0\x7F","",0,1,1,0,logicControl,anyEvent,wrapStyle)
  ,FIELD(bil[1][1],"S1\x7F","",0,1,1,0,logicControl,anyEvent,wrapStyle)
);

MENU(next11,"> Selanjutnya",setPin,enterEvent,noStyle
  ,SUBMENU(InLgc)
  ,altOP(outLogic,"Output Y :",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP11,"Setting pin in/out",doNothing,anyEvent,noStyle
  ,EDIT("Input   \x7F",DataPinEdit[1],TxtPEdit1,checkInput,anyEvent,noStyle)
  ,EDIT("Output Y\x7F",DataPinEdit[0],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,SUBMENU(next11)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(oP2,"3 input logic gate",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP1)
  ,EXIT("< Kembali")
);

MENU(oP1,"2 input logic gate",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP11)
  ,EXIT("< Kembali")
);

MENU(gLogic,"Gerbang Logika",doNothing,anyEvent,noStyle
  ,SUBMENU(oP1)
  ,SUBMENU(oP2)
  ,EXIT("< Kembali")
);

//Adder
//8 Bit
TOGGLE(bil[24][1],Cin,"Carry In \x7F ",logicControl,anyEvent,noStyle
  ,VALUE("1 (HIGH)",1,logicControl,updateEvent)
  ,VALUE("0 (LOW)",0,logicControl,updateEvent)
);
  
MENU(next21,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("bn_A",DataPinLogic[7],TxtPLogic6,logicControl,anyEvent,noStyle)
  ,EDIT("bn_B",DataPinLogic[8],TxtPLogic7,logicControl,anyEvent,noStyle)
  ,OP("Tukar nilai A dan B",logicControl,enterEvent)
  ,SUBMENU(Cin)
  ,altOP(tampilan_carryOut,"Carry Out:",logicControl,anyEvent)
  ,altOP(outLogic,"bn_C:",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP2,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("bn_A",DataPinEdit[9],TxtPEdit9,checkInput,anyEvent,noStyle)
  ,EDIT("bn_B",DataPinEdit[10],TxtPEdit10,checkInput,anyEvent,noStyle)
  ,EDIT("Carry In  \x7F",DataPinEdit[0],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,EDIT("Carry Out \x7F",DataPinEdit[16],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,EDIT("bn_C",DataPinEdit[11],TxtPEdit11,checkInput,anyEvent,noStyle)
  ,SUBMENU(next21)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

//4 Bit
MENU(next2,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("bin_A",DataPinLogic[4],TxtPLogic3,logicControl,anyEvent,noStyle)
  ,EDIT("bin_B",DataPinLogic[5],TxtPLogic4,logicControl,anyEvent,noStyle)
  ,OP("Tukar nilai A dan B",logicControl,enterEvent)
  ,SUBMENU(Cin)
  ,altOP(tampilan_carryOut,"Carry Out:",logicControl,anyEvent)
  ,altOP(outLogic,"bin_C:",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP21,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("bin_A",DataPinEdit[6],TxtPEdit6,checkInput,anyEvent,noStyle)
  ,EDIT("bin_B",DataPinEdit[7],TxtPEdit7,checkInput,anyEvent,noStyle)
  ,EDIT("Carry In  \x7F",DataPinEdit[0],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,EDIT("Carry Out \x7F",DataPinEdit[16],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,EDIT("bin_C",DataPinEdit[8],TxtPEdit8,checkInput,anyEvent,noStyle)
  ,SUBMENU(next2)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(OP2,"8 bit adder (2 IC)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP2)
  ,EXIT("< Kembali")
);

MENU(OP1,"4 bit adder (1 IC)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP21)
  ,EXIT("< Kembali")
);

MENU(adder,"Adder (IC 74xx283)",doNothing,anyEvent,noStyle
  ,SUBMENU(OP1)
  ,SUBMENU(OP2)
  ,EXIT("< Kembali")
);

//Comparator
//8 bit
MENU(next31,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("bn_A",DataPinLogic[7],TxtPLogic6,logicControl,anyEvent,noStyle)
  ,EDIT("bn_B",DataPinLogic[8],TxtPLogic7,logicControl,anyEvent,noStyle)
  ,OP("Tukar nilai A dan B",logicControl,enterEvent)
  ,altOP(outLogic,"",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP3,"Setting pin in/out",doNothing,anyEvent,noStyle
  ,EDIT("bn_A",DataPinEdit[9],TxtPEdit9,checkInput,anyEvent,noStyle)
  ,EDIT("bn_B",DataPinEdit[10],TxtPEdit10,checkInput,anyEvent,noStyle)
  ,EDIT("\x0F",DataPinEdit[15],TxtPEdit15,checkInput,anyEvent,noStyle)
  ,SUBMENU(next31)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

//4 bit
MENU(next3,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("bin_A",DataPinLogic[4],TxtPLogic3,logicControl,anyEvent,noStyle)
  ,EDIT("bin_B",DataPinLogic[5],TxtPLogic4,logicControl,anyEvent,noStyle)
  ,OP("Tukar nilai A dan B",logicControl,enterEvent)
  ,altOP(outLogic,"",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP31,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("bin_A",DataPinEdit[6],TxtPEdit6,checkInput,anyEvent,noStyle)
  ,EDIT("bin_B",DataPinEdit[7],TxtPEdit7,checkInput,anyEvent,noStyle)
  ,EDIT("\x0F",DataPinEdit[15],TxtPEdit15,checkInput,anyEvent,noStyle)
  ,SUBMENU(next3)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(op2,"8 bit comp. (2 IC)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP3)
  ,EXIT("< Kembali")
);

MENU(op1,"4 bit comp. (1 IC)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP31)
  ,EXIT("< Kembali")
);

MENU(comp,"Comparator (74xx85)",doNothing,anyEvent,noStyle
  ,SUBMENU(op1)
  ,SUBMENU(op2)
  ,EXIT("< Kembali")
);

//Encoder
//Encoder 10 ke 4 (74xx147)
MENU(next4,"> Selanjutnya",setPin,enterEvent,noStyle
  ,OP("Semua input HIGH",logicControl,enterEvent)
  ,EDIT("In",DataPinLogic[12],TxtPLogic11,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Out: ",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP4,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("In",DataPinEdit[14],TxtPEdit14,checkInput,anyEvent,noStyle)
  ,EDIT("Out \x7F",DataPinEdit[6],TxtPEdit6,checkInput,anyEvent,noStyle)
  ,SUBMENU(next4)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

//Encoder 8 ke 3 (74xx148)
TOGGLE(bil[11][1],eI,"Input EI \x7F ",logicControl,anyEvent,noStyle
  ,VALUE("1 (HIGH)",1,logicControl,updateEvent)
  ,VALUE("0 (LOW)",0,logicControl,updateEvent)
);
  
MENU(next41,"> Selanjutnya",setPin,enterEvent,noStyle
  ,OP("Semua input HIGH",logicControl,enterEvent)
  ,SUBMENU(eI)
  ,EDIT("In \x7F",DataPinLogic[10],TxtPLogic9,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Output:",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP41,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("Input (In) EI \x7F",DataPinEdit[0],TxtPEdit0,checkInput,anyEvent,noStyle)
  ,EDIT("In \x7F",DataPinEdit[12],TxtPEdit12,checkInput,anyEvent,noStyle)
  ,EDIT("Output\x7F",DataPinEdit[4],TxtPEdit4,checkInput,anyEvent,noStyle)
  ,SUBMENU(next41)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(Op2,"Enc. 10~4 (74xx147)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP4)
  ,EXIT("< Kembali")
);

MENU(Op1,"Enc. 8~3 (74xx148)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP41)
  ,EXIT("< Kembali")
);

MENU(encod,"Encoder",doNothing,anyEvent,noStyle
  ,SUBMENU(Op1)
  ,SUBMENU(Op2)
  ,EXIT("< Kembali")
);

//Decoder
//Decoder 3 ke 8 active low (74xx138)
MENU(next51,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("Input \x7F",DataPinLogic[2],TxtPLogic1,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Out: ",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP51,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("Input \x7F",DataPinEdit[4],TxtPEdit4,checkInput,anyEvent,noStyle)
  ,EDIT("Out\x7F",DataPinEdit[12],TxtPEdit12,checkInput,anyEvent,noStyle)
  ,SUBMENU(next51)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

//Decoder 4 ke 10 dengan driver seven segment (74xx42)
MENU(next5,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("In \x7F",DataPinLogic[4],TxtPLogic3,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Ot:",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP5,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("In \x7F",DataPinEdit[6],TxtPEdit6,checkInput,anyEvent,noStyle)
  ,EDIT("Ot",DataPinEdit[5],TxtPEdit5,checkInput,anyEvent,noStyle)
  ,SUBMENU(next5)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(DeC2,"Dec. 4~10 (74xx42)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP5)
  ,EXIT("< Kembali")
);

MENU(DeC1,"Dec. 3~8 (74xx138)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP51)
  ,EXIT("< Kembali")
);

MENU(decod,"Decoder",doNothing,anyEvent,noStyle
  ,SUBMENU(DeC1)
  ,SUBMENU(DeC2)
  ,EXIT("< Kembali")
);

//Multiplexer
//Mux. 8~1 (74xx151)
MENU(next6,"> Selanjutnya",setPin,enterEvent,noStyle
  ,EDIT("In \x7F",DataPinLogic[10],TxtPLogic9,logicControl,anyEvent,noStyle)
  ,EDIT("Select\x7F",DataPinLogic[16],TxtPLogic13,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Output: ",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP6,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("In \x7F",DataPinEdit[12],TxtPEdit12,checkInput,anyEvent,noStyle)
  ,EDIT("Select\x7F",DataPinEdit[4],TxtPEdit4,checkInput,anyEvent,noStyle)
  ,EDIT("Output\x7F",DataPinEdit[2],TxtPEdit2,checkInput,anyEvent,noStyle)
  ,SUBMENU(next6)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(mux1,"Mux 8~1 (74xx151)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP6)
  ,EXIT("< Kembali")
);

MENU(mux,"Multiplexer",doNothing,anyEvent,noStyle
  ,SUBMENU(mux1)
  ,EXIT("< Kembali")
);

//Demultiplexer
//Demux. 1~8 (74xx138)
PADMENU(inL,"In",logicControl,anyEvent,noStyle
  ,FIELD(bil[0][1],"x1","",0,1,1,0,logicControl,anyEvent,wrapStyle)
  ,FIELD(bil[1][1],"\x0C\x32","",0,1,1,0,logicControl,anyEvent,wrapStyle)
  ,FIELD(bil[2][1],"\x0C\x33","",0,1,1,0,logicControl,anyEvent,wrapStyle)
);

MENU(next7,"> Selanjutnya",setPin,enterEvent,noStyle
  ,SUBMENU(inL)
  ,EDIT("Select\x7F",DataPinLogic[16],TxtPLogic13,logicControl,anyEvent,noStyle)
  ,altOP(outLogic,"Out: ",logicControl,anyEvent)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(SP7,"Setting pin in/out",doNothing,noEvent,noStyle
  ,EDIT("In",DataPinEdit[13],TxtPEdit13,checkInput,anyEvent,noStyle)
  ,EDIT("Select\x7F",DataPinEdit[4],TxtPEdit4,checkInput,anyEvent,noStyle)
  ,EDIT("Out\x7F",DataPinEdit[12],TxtPEdit12,checkInput,anyEvent,noStyle)
  ,SUBMENU(next7)
  ,OP("<< Menu Utama",keMenuUtama,enterEvent)
  ,OP("<  Kembali",keluar_kembali,enterEvent)
);

MENU(demux1,"Demux 1~8 (74xx138)",Inisialisasi_Input,enterEvent,noStyle
  ,SUBMENU(isi_PIN_Menu)
  ,SUBMENU(SP7)
  ,EXIT("< Kembali")
);

MENU(demux,"Demultiplexer",doNothing,anyEvent,noStyle
  ,SUBMENU(demux1)
  ,EXIT("< Kembali")
);

/*************************** Menu Utama ***************************/

MENU(menuUtama,"Menu Utama",doNothing,noEvent,wrapStyle
  ,SUBMENU(kon)       //Konversi Bilangan
  ,SUBMENU(gLogic)    //Logic Gate
  ,SUBMENU(adder)     //Adder
  ,SUBMENU(comp)      //Comparator
  ,SUBMENU(encod)     //Encoder
  ,SUBMENU(decod)     //Decoder
  ,SUBMENU(mux)       //Multiplexer
  ,SUBMENU(demux)     //Demultiplexer
  ,OP("< Keluar",keluar_kembali,enterEvent)
);

/******************************************************************/

NAVROOT(nav,menuUtama,MAX_DEPTH,in,out); //the navigation root object

//'\x08'-> Alamat karakter pada LCD2002 untuk Cursor  
//'\x09'-> Alamat karakter pada LCD2002 untuk disable cursor
config myOptions('\x08','\x09',defaultNavCodes,true);

void setup() {
  byte charRam[8];
  DPL = DataPinLogic;
  TBl = TxtBil;
  pinMode(encBtn,INPUT_PULLUP);
  encoder.begin();
  lcd.begin(20,2);
  for(byte b = 0; b < 8; b++) {
    memcpy_P(charRam, &charFlash[b][0], 8);
    lcd.createChar(b, charRam);
  }
  options=&myOptions;//can customize options
  Serial.begin(115200);
  while(!Serial);
  Serial.println(F("Trainer Elektronika Digital V1.0"));
  Serial.println();
  Serial.println(F("********************************"));
  Serial.println(F("* Dibuat oleh:                 *"));
  Serial.println(F("* Nama : Kevin Petrus Tambunan *"));
  Serial.println(F("* NIM  : 5163131022            *"));
  Serial.println(F("********************************"));
  Serial.flush();
  nav.showTitle=false;
  nav.useUpdateEvent = true;
  nav.idleOn();
}

void loop() {
  nav.poll();  //Panggil sistem menu
  if(nav.sleepTask) TscreenSaver.update();
  else if ((!nav.sleepTask)&&(!ST[2])) {
    lcd.noBlink();
    ST[2]=true;
  }
  delay(90);
}
