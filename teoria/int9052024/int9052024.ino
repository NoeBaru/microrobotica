const int PIN_3 = 2;
const int PIN_2 = 3;
const int PIN_1 = 4;
const int PIN_0 = 5;
const int PIN_ENB = 8;

int Q3 = 0;
int Q2 = 0;
int Q1 = 0;
int Q0 = 0;
int E;
int D2, D1, D0;
void setup()
{
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_0, OUTPUT);
  pinMode(PIN_ENB, INPUT);
}

void loop()
{
  digitalWrite(PIN_3, Q3);
  digitalWrite(PIN_2, Q2);
  digitalWrite(PIN_1, Q1);
  digitalWrite(PIN_0, Q0);
    
  E = digitalRead(PIN_ENB);
  
  D2 = !Q2*Q1*Q0*E;
  D1 = (!Q2*Q1*!Q0*E) + (!Q2*!Q1*Q0*E);
  D0 = !Q2*!Q0*E;
  
  Q2 = D2;
  Q1 = D1;
  Q0 = D0;
    
  delay(1000);
}