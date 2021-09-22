#define MAX_DEPTH 8

//Deklarasi pin LCD
LiquidCrystal lcd(22, 24, 26, 2, 28, 3);

///////////// Rotary Encoder ////////////////////////
#define encB 64 //Pin A10
#define encA 65 //Pin A11
//this encoder has a button here
#define encBtn 66 //Pin A12

encoderIn<encA,encB> encoder;                                   //simple quad encoder driver
#define ENC_SENSIVITY 4
encoderInStream<encA,encB> encStream(encoder,ENC_SENSIVITY);    // simple quad encoder fake Stream

//a keyboard with only one key as the encoder button
keyMap encBtn_map[]={{-encBtn,defaultNavCodes[enterCmd].ch}};   //negative pin numbers use internal pull-up, this is on when low
keyIn<1> encButton(encBtn_map);                                 //1 is the number of keys

//input from the encoder + encoder button + serial
serialIn serial(Serial);
menuIn* inputsList[]={&encStream,&encButton,&serial};
chainStream<3> in(inputsList);//3 is the number of inputs

//Keluaran menu pada Serial dan LCD
MENU_OUTPUTS(out,MAX_DEPTH
  ,SERIAL_OUT(Serial)
  ,LIQUIDCRYSTAL_OUT(lcd,{0,0,20,2})
);
