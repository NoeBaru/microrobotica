const int PIN_ENB = 13;
const int PIN_O0 = 5;
const int PIN_O1 = 4;
const int PIN_O2 = 3;
const int PIN_O3 = 2;

int E;
int d0 = 0;
int d1 = 0;
int d2 = 0;
int d3 = 0;

int q0 = 0;
int q1 = 0;
int q2 = 0;
int q3 = 0;

void setup() {
  pinMode(PIN_ENB, INPUT);
  pinMode(PIN_O0, OUTPUT);
  pinMode(PIN_O1, OUTPUT);
  pinMode(PIN_O2, OUTPUT);
  pinMode(PIN_O3, OUTPUT);
}

void loop() {
  

  digitalWrite(PIN_O0, q0);
  digitalWrite(PIN_O1, q1);
  digitalWrite(PIN_O2, q2);
  digitalWrite(PIN_O3, q3);

  E = digitalRead(PIN_ENB);


  d0 = !q2 * !q0 * E;
  d1 = (!q2 * q1 * !q0 * E) + (!q2 * !q1 * q0 * E);
  d2 = !q2 * q1 * q0 * E;

  q0 = d0;
  q1 = d1;
  q2 = d2;
  q3 = d3;
  
  delay (1000);
  
}