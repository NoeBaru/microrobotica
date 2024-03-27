const int PIN_A = 13;
const int PIN_B = 12;
const int PIN_C = 11;

int Q_A = 1, Q_B = 1, Q_C = 0;
int D_A, D_B, D_C;

int k = 0;

void setup()
{
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
}

void loop()
{
  digitalWrite(PIN_A, Q_A);
  digitalWrite(PIN_B, Q_B);
  digitalWrite(PIN_C, Q_C);
  
  D_A = !Q_A * !Q_B * !Q_C;
  D_B = Q_A + Q_B * Q_C;
  D_C = Q_A + Q_B * !Q_C;
  
  Q_A = D_A;
  Q_B = D_B;
  Q_C = D_C; 
  
  delay(1000);
}