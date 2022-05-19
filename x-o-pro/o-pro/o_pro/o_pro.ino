#include <LiquidCrystal.h>
#include <Keypad.h>


#define l1 A0
#define l2 A1
#define l3 A2
#define l4 A3

#define n1 A7  //green
#define n2 A6  //white
#define n3 A5  //orange
const int rs = 13, en = 8, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A12, A11, A10, A9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A13, A14, A15}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char matrix[9];
boolean flag=true;
void setup() {
  
  Serial.begin(9600);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(l4, OUTPUT);
  pinMode(n1, OUTPUT);
  pinMode(n2, OUTPUT);
  pinMode(n3, OUTPUT);
  lcd.begin(16, 4);
  lcd.clear();
  for(int i=0;i<9;i++){
    matrix[i]='_';
    }
  printMatrix();
  
}

void loop() {
    
    if(Serial.available()){
        char c = Serial.read();
        if(c=='e'){
           flag=false;
           print_win(0);  
        }else if(c=='x'){
           flag=false;                   
           print_win(1);
        }else if(c=='o'){
           flag=false;                    
           print_win(2);
        }else{
           flag=true;
           int indexOfHome=index(c);
           if(matrix[indexOfHome - 1]=='_'){
              matrix[indexOfHome - 1]= 'x';
              printMatrix();
           }
                                   
        }
      
      }

    if(flag==true){
        char key = keypad.getKey();  
            if (key){

              boolean checkNumber=checkIsNumber(key);
              if(checkNumber){
                  
                  int indexOfMatrix=index(key);
                  if(matrix[indexOfMatrix - 1]=='_'){
                      matrix[indexOfMatrix - 1]= 'o';
                      printMatrix();
                      flag=false;
                      char win =  checkWin();
                      Serial.write(key); 
                      if(win=='n'){
                          //Serial.write(key);  
                        }else if(win=='e'){
                            Serial.write('e');
                            print_win(0);
                          }else if(win=='x'){
                              Serial.write('x');
                              print_win(1);
                            }else if(win=='o'){
                                Serial.write('o');
                                print_win(2);
                              }
                      
                      
                    }
                  
                
        
               } 
              
          }
    }


    if(flag==true){
          digitalWrite(l1, HIGH);
          digitalWrite(l2, HIGH);
          digitalWrite(l3, HIGH);
          digitalWrite(l4, HIGH);
          }else if(flag==false){
            
            digitalWrite(l1, LOW);
            digitalWrite(l2, LOW);
            digitalWrite(l3, LOW);
            digitalWrite(l4, LOW);
            }
    
  }



void print_win(int gamer)
{


  if(gamer==1){
    lcd.setCursor(2 , 0);
    lcd.print("Player X won");
    digitalWrite(n1, HIGH);
    }else if(gamer==2){
    lcd.setCursor(2 , 0);
    lcd.print("Player O won");
    digitalWrite(n3, HIGH);
    }else if(gamer==0){
      
      lcd.setCursor(2 , 0);
      lcd.print("Equal");
     digitalWrite(n2, HIGH);
      }
    
    
}

char  checkWin(){
  char whichWin='n';
  boolean check_win=false;
  if(matrix[0]==matrix[1] && matrix[0]==matrix[2] && matrix[0]!='_'){
    whichWin=matrix[0];
    check_win=true;
    
    }
  if(matrix[3]==matrix[4] && matrix[3]==matrix[5] && matrix[3]!='_'){
    whichWin=matrix[3];
    check_win=true;
    
    }

   if(matrix[6]==matrix[7] && matrix[6]==matrix[8] && matrix[6]!='_'){
    whichWin=matrix[6];
    check_win=true;
    
    }

    if(matrix[0]==matrix[3] && matrix[0]==matrix[6] && matrix[0]!='_'){
    whichWin=matrix[0];
    check_win=true;
    
    }
    if(matrix[1]==matrix[4] && matrix[1]==matrix[7] && matrix[1]!='_'){
    whichWin=matrix[1];
    check_win=true;
    
    }
    if(matrix[2]==matrix[5] && matrix[2]==matrix[8] && matrix[2]!='_'){
    whichWin=matrix[2];
    check_win=true;
    
    }
    if(matrix[0]==matrix[4] && matrix[0]==matrix[8] && matrix[0]!='_'){
    whichWin=matrix[0];
    check_win=true;
    
    }

    if(matrix[2]==matrix[4] && matrix[2]==matrix[6] && matrix[2]!='_'){
    whichWin=matrix[2];
    check_win=true;
    
    }


//check if 2 players dose not win
    if(matrix[0]!='_'  && matrix[1]!='_'  && matrix[2]!='_' && matrix[3]!='_' && matrix[4]!='_' && matrix[5]!='_' && matrix[6]!='_' && matrix[7]!='_' && matrix[8]!='_' && check_win==false){
    
          whichWin='e';
          
    }else if(check_win==false){
      
          whichWin='n';
         
      
      }
      
  
  return whichWin;
  
  }

int index(char key){
  
  int index=0;
  if(key=='1'){
    index=1;
    }else if(key=='2'){
    index=2;
    }else if(key=='3'){
    index=3;
    }else if(key=='4'){
    index=4;
    }else if(key=='5'){
    index=5;
    }else if(key=='6'){
    index=6;
    }else if(key=='7'){
    index=7;
    }else if(key=='8'){
    index=8;
    }else if(key=='9'){
    index=9;
    }
  
  return index;
  }


  boolean checkIsNumber(char key){
    
    return ( (key=='1' ||key=='2' ||key=='3' ||key=='4' ||key=='5' ||key=='6' ||key=='7' ||key=='8'||key=='9' ) );
    
    }



    void printMatrix()
{

  lcd.clear();
  lcd.setCursor(0 , 0);
  lcd.print("O");
  lcd.setCursor(6 , 1);
  lcd.write(matrix[0]);
  lcd.setCursor(7 , 1);
  lcd.write(matrix[1]);
  lcd.setCursor(8 , 1);
  lcd.write(matrix[2]);
  lcd.setCursor(6 , 2);
  lcd.write(matrix[3]);
  lcd.setCursor(7 , 2);
  lcd.write(matrix[4]);
  lcd.setCursor(8 , 2);
  lcd.write(matrix[5]);
  lcd.setCursor(6 , 3);
  lcd.write(matrix[6]);
  lcd.setCursor(7 , 3);
  lcd.write(matrix[7]);
  lcd.setCursor(8 , 3);
  lcd.write(matrix[8]);
  
  
  
  
  }
