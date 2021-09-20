#define MAX_CHAR 256

//Deklarasikan pin Input/Output Arduino Mega
const char* const Pin_IO[][2] PROGMEM = {{"-",38},{"A",39},{"B",45},{"C",51},{"D",4},{"E",7},{"F",10},{"G",23},{"H",29}
                                        ,{"I",35},{"J",41},{"K",47},{"L",53},{"M",5},{"N",12},{"O",9},{"P",25},{"Q",31}
                                        ,{"R",37},{"S",43},{"T",49},{"U",48},{"V",6},{"W",11},{"X",8},{"Y",27},{"Z",33}};

void tampilanAwal();

//Creats a noDelay varible set to 650ms, 200ms, 150ms dan 90ms.
noDelay TimeD1(650),TimeD2(200),TimeD3(150);
noDelay TscreenSaver(90,tampilanAwal);

//Tampilan awal LCD                  "                    "
const char* const PROGMEM pesan[] = {"Trainer Elektronika"   //Baris pertama (Halaman 1)
                                    ,"    Digital V1.0"      //Baris kedua   (Halaman 1)
                                    ," Dibuat oleh:"         //Baris pertama (Halaman 2)
                                    ," Kevin P Tambunan"     //Baris kedua   (Halaman 2)
                                    };
                                
bool ST[3] = {false,false,false};
byte st[4]={0,0,0,0};

//Deklarasi variabel base untuk konversi bilangan
byte base1,base2;

char* constMEM abjad MEMMODE="\x41\x42\x43\x44\x45\x46GHIJKLMNOPQRSTUVWXYZ"; //Alpabet untuk Input/Output pada Text Edit
// Kode hex :\x41\x42\x43\x44\x45\x46 merupakan alamat pada memory Liquid Crystal Display untuk mengakses karakter huruf A,B,C,D,E dan F

//#define constMEM const
//#define MEMMODE PROGMEM

//////Sistem Bilangan///////
const char* constMEM signNumb MEMMODE=" -";                 //Signed Numbers
const char* constMEM binDigit MEMMODE="01";                 //biner
const char* constMEM octDigit MEMMODE="01234567";           //oktal
const char* constMEM decDigit MEMMODE="0123456789";         //desimal
const char* constMEM hexDigit MEMMODE="0123456789ABCDEF";   //heksadesimal
//////Digit Bilangan////////
char (*TBl)[18],TxtBil[5][18] = {"000000 (Oktal)"
                                ," 00000 (Desimal)"
                                ,"0x0000 (Heksa)"
                                ,"B0000000000000000"
                                ,"                 "};

//Simpan text bilangan ke memory flash
const char TB0[] PROGMEM = "000000 (Oktal)";
const char TB1[] PROGMEM = " 00000 (Desimal)";
const char TB2[] PROGMEM = "0x0000 (Heksa)";
const char TB3[] PROGMEM = "B0000000000000000";
const char TB4[] PROGMEM = "                 ";
const char TB5[] PROGMEM = "-00000 (Desimal)";
const char* const TB_PROG[] PROGMEM = {TB0,TB1,TB2,TB3,TB4,TB5};
                     
char* constMEM bineNr[] MEMMODE = {binDigit};
char* constMEM binNr[]  MEMMODE = {"B",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit};
char* constMEM octNr[]  MEMMODE = {octDigit,octDigit,octDigit,octDigit,octDigit,octDigit," ","(","O","k","t","a","l",")"};
char* constMEM decNr[]  MEMMODE = {signNumb,decDigit,decDigit,decDigit,decDigit,decDigit," ","(","D","e","s","i","m","a","l",")"};
char* constMEM hexNr[]  MEMMODE = {"0","x",hexDigit,hexDigit,hexDigit,hexDigit," ","(","H","e","k","s","a",")"};

///////////////////////////////////////////////////////////////Pin Edit///////////////////////////////////////////////////////////////
//Simpan data pin edit yang sudah terisi ke memory flash
const char dpei0[]  PROGMEM = "D";
const char dpei1[]  PROGMEM = "S0\x0D\x41 B\x0ES1";                          
const char dpei2[]  PROGMEM = "|z\x0DS \x0A T\x0E\x0B|";                                             
const char dpei3[]  PROGMEM = "S0\x0D\x41 B C\x0ES2";                                                          
const char dpei4[]  PROGMEM = "A2\x0DS T U\x0E\x41\x30";                                        
const char dpei5[]  PROGMEM = "Y0\x0DSTUVWXYZQR\x0EY9";                                               
const char dpei6[]  PROGMEM = "A3\x0D\x42 C D E\x0E\x41\x30";            
const char dpei7[]  PROGMEM = "B3\x0DK L M N\x0E\x42\x30";                                 
const char dpei8[]  PROGMEM = "C3\x0DT U V W\x0E\x43\x30";             
const char dpei9[]  PROGMEM = "A7\x0D\x41\x42\x43\x44\x45\x46GH\x0E\x41\x30";                                   
const char dpei10[] PROGMEM = "B7\x0DJKLMNOPQ\x0E\x42\x30";            
const char dpei11[] PROGMEM = "C7\x0DSTUVWXYZ\x0E\x43\x30";                                 
const char dpei12[] PROGMEM = "S0\x0D\x42\x43\x44\x45\x46GHI\x0ES7";                    
const char dpei13[] PROGMEM = "x1\x0D\x41 \x0A \x0C\x32\x0D\x42 C\x0E\x0C\x33";                             
const char dpei14[] PROGMEM = "S1\x0D\x41\x42\x43\x44\x45\x46GHI\x0ES9";               
const char dpei15[] PROGMEM = "A<B\x0DS A=B\x0DT A>B\x0DU";                                     
const char dpei16[] PROGMEM = "J";
const char dpei17[] PROGMEM = "S";
const char dpei18[] PROGMEM = "I";
const char dpei19[] PROGMEM = "R";
const char dpei20[] PROGMEM = "A3\x0D\x41 B C D\x0E\x41\x30";            
const char dpei21[] PROGMEM = "B3\x0DJ K L M\x0E\x42\x30";
const char dpei22[] PROGMEM = "A3\x0DS T U V\x0E\x41\x30";
const char dpei23[] PROGMEM = "A2\x0D\x41 B C\x0E\x41\x30";
const char dpei24[] PROGMEM = "S0\x0DSTUVWXYZ\x0ES7";
const char dpei25[] PROGMEM = "A2\x0DJ K L\x0E\x41\x30";
const char dpei26[] PROGMEM = "A";
const char dpei27[] PROGMEM = "S0\x0D\x41\x42\x43\x44\x45\x46GH\x0ES7";                                   
const char* const DPE_Isi[] PROGMEM = {dpei0,dpei1,dpei2,dpei3,dpei4,dpei5,dpei6,dpei7,dpei8,dpei9,dpei10,dpei11,dpei12,dpei13,dpei14,dpei15,dpei16,dpei17,dpei18,dpei19,dpei20,dpei21,dpei22,dpei23,dpei24,dpei25,dpei26,dpei27};

//Simpan data pin edit default ke memory flash
const char dpe0[]  PROGMEM = "-";
const char dpe1[]  PROGMEM = "S0\x0D- -\x0ES1";                          //9 Gate Logic dua input (S0-S1)
const char dpe2[]  PROGMEM = "|z\x0D- \x0A -\x0E\x0B|";                  //9 Multiplekser (Output)
const char dpe3[]  PROGMEM = "S0\x0D- - -\x0ES2";                        //11 Gate Logic tiga input (S0-S2)
const char dpe4[]  PROGMEM = "A2\x0D- - -\x0E\x41\x30";                  //11 3 bit (A2-A0)
const char dpe5[]  PROGMEM = "Y0\x0D----------\x0EY9";                   //11 Decoder 4 to 10 (Y0-Y9)
const char dpe6[]  PROGMEM = "A3\x0D- - - -\x0E\x41\x30";                //13 Adder 4 bit
const char dpe7[]  PROGMEM = "B3\x0D- - - -\x0E\x42\x30";                //13 Adder 4 bit
const char dpe8[]  PROGMEM = "C3\x0D- - - -\x0E\x43\x30";                //13 Adder 4 bit
const char dpe9[]  PROGMEM = "A7\x0D--------\x0E\x41\x30";               //14 Adder 8 bit
const char dpe10[] PROGMEM = "B7\x0D--------\x0E\x42\x30";               //14 Adder 8 bit
const char dpe11[] PROGMEM = "C7\x0D--------\x0E\x43\x30";               //14 Adder 8 bit
const char dpe12[] PROGMEM = "S0\x0D--------\x0ES7";                     //14 S0-S7 Encoder
const char dpe13[] PROGMEM = "x1\x0D- \x0A \x0C\x32\x0D- -\x0E\x0C\x33"; //14 Demultiplekser (input)
const char dpe14[] PROGMEM = "S1\x0D---------\x0ES9";                    //16 S1-S9 Encoder
const char dpe15[] PROGMEM = "A<B\x0D- A=B\x0D- A>B\x0D-";               //17 Comparator
const char dpe16[] PROGMEM = "-";
const char* const DPE_PROG[] PROGMEM = {dpe0,dpe1,dpe2,dpe3,dpe4,dpe5,dpe6,dpe7,dpe8,dpe9,dpe10,dpe11,dpe12,dpe13,dpe14,dpe15,dpe16};

char DataPinEdit[17][20] = {"-","S0\x0D- -\x0ES1"                      //9 Gate Logic dua input (S0-S1)
                           ,"|z\x0D- \x0A -\x0E\x0B|"                  //9 Multiplekser (Output)
                           ,"S0\x0D- - -\x0ES2"                        //11 Gate Logic tiga input (S0-S2)
                           ,"A2\x0D- - -\x0E\x41\x30"                  //11 3 bit (A2-A0)
                           ,"Y0\x0D----------\x0EY9"                   //11 Decoder 4 to 10 (Y0-Y9)
                           ,"A3\x0D- - - -\x0E\x41\x30"                //13 Adder 4 bit
                           ,"B3\x0D- - - -\x0E\x42\x30"                //13 Adder 4 bit
                           ,"C3\x0D- - - -\x0E\x43\x30"                //13 Adder 4 bit
                           ,"A7\x0D--------\x0E\x41\x30"               //14 Adder 8 bit
                           ,"B7\x0D--------\x0E\x42\x30"               //14 Adder 8 bit
                           ,"C7\x0D--------\x0E\x43\x30"               //14 Adder 8 bit
                           ,"S0\x0D--------\x0ES7"                     //14 S0-S7 Encoder
                           ,"x1\x0D- \x0A \x0C\x32\x0D- -\x0E\x0C\x33" //14 Demultiplekser (input)
                           ,"S1\x0D---------\x0ES9"                    //16 S1-S9 Encoder
                           ,"A<B\x0D- A=B\x0D- A>B\x0D-"               //17 Comparator
                           ,"-"};
char* constMEM TxtPEdit0[]  MEMMODE={abjad};
char* constMEM TxtPEdit1[]  MEMMODE={"S","0","\x0D",abjad," ",abjad,"\x0E","S","1"};                                              //9 Gate Logic dua input (S0-S1)
char* constMEM TxtPEdit2[]  MEMMODE={"|","z","\x0D",abjad," ","\x0A"," ",abjad,"\x0E","\x0B","|"};                                //9 Multiplekser (Output)
char* constMEM TxtPEdit3[]  MEMMODE={"S","0","\x0D",abjad," ",abjad," ",abjad,"\x0E","S","2"};                                    //11 Gate Logic tiga input (S0-S2)
char* constMEM TxtPEdit4[]  MEMMODE={"A","2","\x0D",abjad," ",abjad," ",abjad,"\x0E","A","0"};                                    //11 3 bit (A2-A0)
char* constMEM TxtPEdit5[]  MEMMODE={"Y","0","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","Y","9"};  //11 Decoder 4 to 10 (Y0-Y9)
char* constMEM TxtPEdit6[]  MEMMODE={"A","3","\x0D",abjad," ",abjad," ",abjad," ",abjad,"\x0E","A","0"};                          //13 Adder 4 bit
char* constMEM TxtPEdit7[]  MEMMODE={"B","3","\x0D",abjad," ",abjad," ",abjad," ",abjad,"\x0E","B","0"};                          //13 Adder 4 bit
char* constMEM TxtPEdit8[]  MEMMODE={"C","3","\x0D",abjad," ",abjad," ",abjad," ",abjad,"\x0E","C","0"};                          //13 Adder 4 bit
char* constMEM TxtPEdit9[]  MEMMODE={"A","7","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","A","0"};              //14 Adder 8 bit
char* constMEM TxtPEdit10[] MEMMODE={"B","7","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","B","0"};              //14 Adder 8 bit
char* constMEM TxtPEdit11[] MEMMODE={"C","7","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","C","0"};              //14 Adder 8 bit
char* constMEM TxtPEdit12[] MEMMODE={"S","0","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","S","7"};              //14 S0-S7 Encoder
char* constMEM TxtPEdit13[] MEMMODE={"x","1","\x0D",abjad," ","\x0A"," ","\x0C","2","\x0D",abjad," ",abjad,"\x0E","\x0C","3"};    //14 Demultiplekser (input)
char* constMEM TxtPEdit14[] MEMMODE={"S","1","\x0D",abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,abjad,"\x0E","S","9"};        //16 S1-S9 Encoder
char* constMEM TxtPEdit15[] MEMMODE={"A","<","B","\x0D",abjad," ","A","=","B","\x0D",abjad," ","A",">","B","\x0D",abjad};         //17 Comparator
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////Pin Logic///////////////////////////////////////////////////////////////
//Simpan data pin logic ke memory flash
const char dpL0[]  PROGMEM = " ";                                                     //Output S
const char dpL1[]  PROGMEM = "|z\x0D\x30 \x0A \x30\x0E\x0B|";                         //9 Multiplekser (Output)
const char dpL2[]  PROGMEM = "A2\x0D\x30 0 0\x0E\x41\x30";                            //11 3 bit (A2-A0)
const char dpL3[]  PROGMEM = "Y0\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x0EY9";  //11 Decoder 4 to 10 (Y0-Y9)
const char dpL4[]  PROGMEM = "A3\x0D\x30 0 0 0\x0E\x41\x30";                          //13 Adder 4 bit
const char dpL5[]  PROGMEM = "B3\x0D\x30 0 0 0\x0E\x42\x30";                          //13 Adder 4 bit
const char dpL6[]  PROGMEM = "C3\x0D\x30 0 0 0\x0E\x43\x30";                          //13 Adder 4 bit
const char dpL7[]  PROGMEM = "A7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x41\x30";    //14 Adder 8 bit
const char dpL8[]  PROGMEM = "B7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x42\x30";    //14 Adder 8 bit
const char dpL9[]  PROGMEM = "C7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x43\x30";    //14 Adder 8 bit
const char dpL10[] PROGMEM = "S0\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0ES7";          //14 S0-S7 Encoder
const char dpL11[] PROGMEM = "x1\x0D\x30 \x0A \x0C2\x0D\x30 \x30\x0E\x0C\x33";        //14 Demultiplekser (input)
const char dpL12[] PROGMEM = "S1\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x30\x0ES9";      //16 S1-S9 Encoder
const char dpL13[] PROGMEM = "A<B\x0D\x30 |A=B\x0D\x30 |A>B\x0D\x30";                 //17 Comparator
const char dpL14[] PROGMEM = "                   ";
const char dpL15[] PROGMEM = "                   ";
const char dpL16[] PROGMEM = "A2\x0D\x30 0 0\x0E\x41\x30";                            //Selector/address untuk Mux dan Demux                 
const char* const DPL_PROG[] PROGMEM = {dpL0,dpL1,dpL2,dpL3,dpL4,dpL5,dpL6,dpL7,dpL8,dpL9,dpL10,dpL11,dpL12,dpL13,dpL14,dpL15,dpL16};

char (*DPL)[20],DataPinLogic[17][20]={" ","|z\x0D\x30 \x0A \x30\x0E\x0B|"                         //9 Multiplekser (Output)
                                         ,"A2\x0D\x30 0 0\x0E\x41\x30"                            //11 3 bit (A2-A0)
                                         ,"Y0\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x0EY9"  //11 Decoder 4 to 10 (Y0-Y9)
                                         ,"A3\x0D\x30 0 0 0\x0E\x41\x30"                          //13 Adder 4 bit
                                         ,"B3\x0D\x30 0 0 0\x0E\x42\x30"                          //13 Adder 4 bit
                                         ,"C3\x0D\x30 0 0 0\x0E\x43\x30"                          //13 Adder 4 bit
                                         ,"A7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x41\x30"    //14 Adder 8 bit
                                         ,"B7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x42\x30"    //14 Adder 8 bit
                                         ,"C7\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0E\x43\x30"    //14 Adder 8 bit
                                         ,"S0\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x0ES7"          //14 S0-S7 Encoder
                                         ,"x1\x0D\x30 \x0A \x0C2\x0D\x30 \x30\x0E\x0C\x33"        //14 Demultiplekser (input)
                                         ,"S1\x0D\x30\x30\x30\x30\x30\x30\x30\x30\x30\x0ES9"      //16 S1-S9 Encoder
                                         ,"A<B\x0D\x30 |A=B\x0D\x30 |A>B\x0D\x30"                 //17 Comparator
                                         ,"                   "
                                         ,"                   " 
                                         ,"A2\x0D\x30 0 0\x0E\x41\x30"};                          //Selector/address untuk Mux dan Demux
                       
char* constMEM TxtPLogic0[]  MEMMODE={"|","z","\x0D",binDigit," ","\x0A"," ",binDigit,"\x0E","\x0B","|"};                                                       //9 Multiplekser (Output)
char* constMEM TxtPLogic1[]  MEMMODE={"A","2","\x0D",binDigit," ",binDigit," ",binDigit,"\x0E","A","0"};                                                        //11 3 bit (A2-A0)
char* constMEM TxtPLogic2[]  MEMMODE={"Y","0","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","Y","9"}; //11 Decoder 4 to 10 (Y0-Y9)
char* constMEM TxtPLogic3[]  MEMMODE={"A","3","\x0D",binDigit," ",binDigit," ",binDigit," ",binDigit,"\x0E","A","0"};                                           //13 Adder 4 bit
char* constMEM TxtPLogic4[]  MEMMODE={"B","3","\x0D",binDigit," ",binDigit," ",binDigit," ",binDigit,"\x0E","B","0"};                                           //13 Adder 4 bit
char* constMEM TxtPLogic5[]  MEMMODE={"C","3","\x0D",binDigit," ",binDigit," ",binDigit," ",binDigit,"\x0E","C","0"};                                           //13 Adder 4 bit
char* constMEM TxtPLogic6[]  MEMMODE={"A","7","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","A","0"};                   //14 Adder 8 bit
char* constMEM TxtPLogic7[]  MEMMODE={"B","7","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","B","0"};                   //14 Adder 8 bit
char* constMEM TxtPLogic8[]  MEMMODE={"C","7","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","C","0"};                   //14 Adder 8 bit
char* constMEM TxtPLogic9[]  MEMMODE={"S","0","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","S","7"};                   //14 S0-S7 Encoder
char* constMEM TxtPLogic10[] MEMMODE={"x","1","\x0D",binDigit," ","\x0A"," ","\x0C","2","\x0D",binDigit," ",binDigit,"\x0E","\x0C","3"};                        //14 Demultiplekser (input)
char* constMEM TxtPLogic11[] MEMMODE={"S","1","\x0D",binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,binDigit,"\x0E","S","9"};          //16 S0-S9 Encoder
char* constMEM TxtPLogic12[] MEMMODE={"A","<","B","\x0D",binDigit," ","|","A","=","B","\x0D",binDigit," ","|","A",">","B","\x0D",binDigit};                     //17 Comparator
char* constMEM TxtPLogic13[] MEMMODE={"A","2","\x0D",binDigit," ",binDigit," ",binDigit,"\x0E","A","0"};                                                        //Selector/address untuk Mux dan Demux
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte bil[26][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};

bool Sign = 0; //Tanda sebuah bilangan

bool isi = 0; //Tukar isi pada rangkaian adder

byte Jlh_Char; //Jumlah Char atau karakter

const byte charFlash[8][8] PROGMEM = {
{ 0b01000, //[0] Karakter segitiga
  0b00100, // Alamat karakter pada LCD2002 : lcd.print('\x08'); 
  0b10010,
  0b11001,
  0b10010,
  0b00100,
  0b01000,
  0b00000
  },
{ 0b00000, //[1] Karakter garis horizontal
  0b00000, // Alamat karakter pada LCD2002 : lcd.print('\x09');
  0b00000,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000
  },
{ 0b01010, //[2] Karakter garis double vertikal
  0b01010, // Alamat karakter pada LCD2002 : lcd.print('\x0A');
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b01010
  },
{ 0b11111, //[3] Karakter 'bukan z'
  0b00000, // Alamat karakter pada LCD2002 : lcd.print('\x0B');
  0b11111,
  0b00010,
  0b00100,
  0b01000,
  0b11111,
  0b00000
  },
{ 0b11111, //[4] Karakter 'bukan x' 
  0b00000, // Alamat karakter pada LCD2002 : lcd.print('\x0C');
  0b10001,
  0b01010,
  0b00100,
  0b01010,
  0b10001,
  0b00000
  },
{ 0b10000, //[5] Karakter '├>'
  0b10100, // Alamat karakter pada LCD2002 : lcd.print('\x0D');
  0b10110,
  0b11111,
  0b10110,
  0b10100,
  0b10000,
  0b10000
  },
{ 0b00001, //[6] Karakter '<┤' 
  0b00101, // Alamat karakter pada LCD2002 : lcd.print('\x0E');
  0b01101,
  0b11111,
  0b01101,
  0b00101,
  0b00001,
  0b00001
  },
{ 0b10000, //[7] Karakter '└>'
  0b10100, // Alamat karakter pada LCD2002 : lcd.print('\x0F');
  0b10010,
  0b11111,
  0b00010,
  0b00100,
  0b00000,
  0b00000
  }
};
//////Data 8 Bit (Pin Digital)///////
//String dataku[4];

//////Scroll Bar (Custom Char LCD 20x2)/////////
/*const uint8_t charBitmap2[][8] = {
   { B11111, //[0] Scroll bar atas
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B10001
   },
   { B11111, //[1] Scroll bar atas pertama
     B10001,
     B11111,
     B11111,
     B10001,
     B10001,
     B10001,
     B10001
   },
   { B11111, //[2] Scroll bar atas kedua
     B10001,
     B10001,
     B10001,
     B11111,
     B11111,
     B10001,
     B10001
   },
   { B11111, //[3] Scroll bar atas ketiga
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B11111,
     B11111
   },
   { B11111, //[4] Scroll bar bawah pertama
     B11111,
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B11111
   },
   { B10001, //[5] Scroll bar bawah kedua
     B10001,
     B11111,
     B11111,
     B10001,
     B10001,
     B10001,
     B11111
   },
   { B10001, //[6] Scroll bar bawah ketiga
     B10001,
     B10001,
     B10001,
     B11111,
     B11111,
     B10001,
     B11111
   },
   { B10001, //[7] Scroll bar bawah
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B10001,
     B11111
   }
};*/
