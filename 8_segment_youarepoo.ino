// This is code to drive an 8-segment display extracted from some junk parts for irl shitposting
//
// By tadyen. Originally on 10-MAY-2022
// updated on 28-DEC-2022


// pin mapping
const int PIN_MAX = 13;
const int Seg8_pin[] = {-1, 8, 7, 6, 5, 4, -1, 2, 9, 10, 11, 12, 13};

// The above is a (more) compact implementation of the following:
// MAPPING Arduino digital pins to the 8-Segment-display pins
//const int pin12 = 13;
//const int pin11 = 12;
//const int pin10 = 11;
//const int pin9 = 10;
//const int pin8 = 9;
//const int pin7 = 2;
//const int pin6 = 3; //SET TO -1 for UNUSED
//const int pin5 = 4;
//const int pin4 = 5;
//const int pin3 = 6;
//const int pin2 = 7;
//const int pin1 = 8;

// 8-segment pin layout 
// 8-seg pins {12, 9, 8} controls block {1, 2, 3} on the display respectively 
//  _11_
// |10  |7
// |_5__|
// |1   |4
// |_2__| #3
//  

//delay quanta in ms between 'frames'. Higher value is brighter but leads to flickering
const int Seg8_DELAY = 3; 

void setup()
{
  Serial.begin(9600);
  flush_Seg8Disp();
}

void loop()
{
  you_r_poo();
  why_r_you_poo();
  rocket();
}

// Due to rushed code, time_delta values below are not intuitive.
// Explanation:
//  Each disp_alph call uses 2*Seg8_DELAY
//  Thus a word, eg 'you' has 3* calls of disp_alph(_, _)
//  This gives a total delta of (6*Seg8_DELAY) for 'you' 

void you_r_poo()
{
  // implementation of "you are poo"
  int i;
  int toggle=0;
  int duration;
  int elapsed;
  int time_delta = 6*Seg8_DELAY;
    
  //you
  duration=1500;
  elapsed=0;
  do
  {
    disp_alph('y',1);
    disp_alph('o',2);
    disp_alph('u',3);
    elapsed+=time_delta;
  }while(elapsed < duration);

  //are
  duration=1000;
  elapsed=0;
  do
  {
    disp_alph('a',1);
    disp_alph('r',2);
    disp_alph('e',3);
    elapsed+=time_delta;
  }while(elapsed < duration);

  //blinking poo
  duration=4000;
  elapsed=0;
  toggle=0;
  time_delta = 8*Seg8_DELAY;
  do
  {
    if(elapsed % 400 < time_delta){toggle^=1;}
    if(toggle)
    {
      disp_alph('p',1);
      disp_alph('o',2);
      disp_alph('o',3);
      disp_alph('.',3);
    }
    else
    {
      disp_alph('*',1);
      disp_alph('*',2);
      disp_alph('*',3);
      disp_alph('*',3);
    }
    elapsed+=time_delta;
  }while(elapsed < duration);

  return;
}


void why_r_you_poo()
{
  // implementation of "why -r- you poo"
  int i;
  int block=3;
  int toggle=0;
  int duration;
  int elapsed;
  int time_delta;
  
  // why
  duration=1000; elapsed=0; i=0;
  time_delta = 200+2*Seg8_DELAY;
  do
  { 
    disp_alph('y',block);
    if(i%2==0){toggle^=1;}
    if(toggle)
    {
      block--;
    }
    else
    {
      block++;
    }
    delay(200);
    elapsed += time_delta;
    i++;
  }while(elapsed<duration);
  
  //are
  duration=1000;
  elapsed=0;
  time_delta = 6*Seg8_DELAY;
  do
  {
    disp_alph('a',1);
    disp_alph('r',2);
    disp_alph('e',3);
    elapsed+=time_delta;
  }while(elapsed < duration);

  //you
  duration=1000;
  elapsed=0;
  do
  {
    disp_alph('y',1);
    disp_alph('o',2);
    disp_alph('u',3);
    elapsed+=time_delta;
  }while(elapsed < duration);

  //poo
  duration=3000;
  elapsed=0;
  do
  {
    disp_alph('p',1);
    disp_alph('o',2);
    disp_alph('o',3);
    elapsed+=time_delta;
  }while(elapsed < duration);

  return;
}

void rocket()
{
  //animated rocket
  int toggle=0;
  int elapsed=0;
  int i;
  int frame_num=1;

  // each iteration is the next frame
  for(i=0; i<55; i++)
  {
    //reverse the frame direction on last frame
    if(i%6==0){toggle^=1;}
    rocket_frame(frame_num);
    if(toggle)
    {
      frame_num++;
    }
    else
    {
      frame_num--;
    }
  }
  return;
}


void rocket_frame(int frame)
{
  // stuff for rocket()
  // this defines each frame for the rocket 
  int duration = 100;
  int elapsed;
  int time_delta=6*Seg8_DELAY;
  
  switch(frame)
  {
    case 1:
      // frame1
      elapsed=0;
      do
      {
        disp_alph('*',1);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[2],HIGH);
        disp_alph('*',3);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;
      
    case 2:
      // frame2
      elapsed=0;
      do
      {
        disp_alph('*',1);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[5],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',3);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;

    case 3:
      // frame3
      elapsed=0;
      do
      {
        disp_alph('*',1);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[10],HIGH);
        digitalWrite(Seg8_pin[11],HIGH);
        digitalWrite(Seg8_pin[7],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',3);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;

    case 4:
      // frame4
      elapsed=0;
      do
      {
        disp_alph('*',1);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[10],HIGH);
        digitalWrite(Seg8_pin[7],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',3);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;

    case 5:
      // frame5
      elapsed=0;
      do
      {
        disp_alph('*',1);
        digitalWrite(Seg8_pin[2],HIGH);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[10],HIGH);
        digitalWrite(Seg8_pin[7],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',3);
        digitalWrite(Seg8_pin[2],HIGH);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;

    case 6:
      // frame6
      elapsed=0;
      do
      {
        disp_alph('*',1);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[2],HIGH);
        digitalWrite(Seg8_pin[5],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',2);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[2],HIGH);
        digitalWrite(Seg8_pin[10],HIGH);
        digitalWrite(Seg8_pin[7],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        disp_alph('*',3);
        digitalWrite(Seg8_pin[1],HIGH);
        digitalWrite(Seg8_pin[2],HIGH);
        digitalWrite(Seg8_pin[5],HIGH);
        digitalWrite(Seg8_pin[4],HIGH);
        elapsed += time_delta;
      }while(elapsed < duration);
      break;

    default:
      break;
  }
    return;
}

void disp_alph(char alph, int Seg8Block)
{
  // displays an alphabet
  // arg1: alphabet (char)
  // arg2: which block? (int 1-3)
  //
  // this works by driving the pin for the selected block LOW

  delay(Seg8_DELAY);
  flush_Seg8Disp();
  switch(Seg8Block)
  {
    case 1:
      digitalWrite(Seg8_pin[8], HIGH);
      digitalWrite(Seg8_pin[9], HIGH);
      digitalWrite(Seg8_pin[12], LOW);
      break;
      
    case 2:
      digitalWrite(Seg8_pin[8], HIGH);
      digitalWrite(Seg8_pin[9], LOW);
      digitalWrite(Seg8_pin[12], HIGH);
      break;
      
    case 3:
      digitalWrite(Seg8_pin[8], LOW);
      digitalWrite(Seg8_pin[9], HIGH);
      digitalWrite(Seg8_pin[12], HIGH);
      break;
      
    default:
      break;
  }
  Seg8Alph(alph);
  delay(Seg8_DELAY);
  return;
}

void Seg8Alph(char alpha)
{
  // Set Seg8pin(s) to HI/LO accordingly for characters
  //  _11_
  // |10  |7
  // |_5__|
  // |1   |4
  // |_2__| #3
  //  
  // Minimal supported characters: aegporuy.-
  // * for blank
  // # for all
  switch(alpha)
  {
    // blank
    case '*':
      digitalWrite(Seg8_pin[1],LOW);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],LOW);
      digitalWrite(Seg8_pin[11],LOW);
      break;

    // All
    case '#':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],HIGH);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
              
    case '-':
      digitalWrite(Seg8_pin[1],LOW);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],LOW);
      digitalWrite(Seg8_pin[11],LOW);
      break;
      
    case '.':
      digitalWrite(Seg8_pin[1],LOW);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],HIGH);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],LOW);
      digitalWrite(Seg8_pin[11],LOW);
      break;

    case 'a':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
      
    case 'e':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
      
    case 'g':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
    
    case 'p':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;

    case 'o':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
      
    case 'r':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],LOW);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],LOW);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],LOW);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],HIGH);
      break;
      
    case 'u':
      digitalWrite(Seg8_pin[1],HIGH);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],LOW);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],LOW);
      break;
      
    case 'y':
      digitalWrite(Seg8_pin[1],LOW);
      digitalWrite(Seg8_pin[2],HIGH);
      digitalWrite(Seg8_pin[3],LOW);
      digitalWrite(Seg8_pin[4],HIGH);
      digitalWrite(Seg8_pin[5],HIGH);
      digitalWrite(Seg8_pin[7],HIGH);
      digitalWrite(Seg8_pin[10],HIGH);
      digitalWrite(Seg8_pin[11],LOW);
      break;

    default:
      break;
  }
  return;
}

void flush_Seg8Disp()
{ 
  // flush the display by resetting all pins to display blank
  bool flag_BlockPin=false;
  int pin_num;
  for(pin_num = 1; pin_num<PIN_MAX ; pin_num++)
  {
    flag_BlockPin=false;
    if(pin_num == 12){flag_BlockPin=1;}
    if(pin_num == 9){flag_BlockPin=1;}
    if(pin_num == 8){flag_BlockPin=1;}
    if(pin_num == 6){flag_BlockPin=1;}
    
    pinMode(Seg8_pin[pin_num], OUTPUT);
    if(flag_BlockPin)
    {
        digitalWrite(Seg8_pin[pin_num], HIGH);
    }
    else
    {
        digitalWrite(Seg8_pin[pin_num], LOW);
    }
  }
  return;
}
