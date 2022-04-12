#include "Arduino.h"
#define N 30000

int i;
float a = 3.14f, b = 2.71f, c;
double da = 3.14, db = 2.71, dc;
long double qa = 3.14, qb = 2.71, qc;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(100);
}

void loop() {
  Serial.println("Loop START");
  Serial.flush();
  delay(100);

  // COMMON
  // =========>
  // Benchmark for Serial.println
  Serial.println("Benchmark 01C");
  Serial.flush();
  delay(100);

  // COMMON
  // =========>
  // Benchmark for empty loop
  for (i = 0; i < N; ++i) {
  }
  
  Serial.println("Benchmark 02C");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float assignment
  for (i = 0; i < N; ++i) {
    c = a;
  }
  
  Serial.println("Benchmark 00F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float addition AB
  for (i = 0; i < N; ++i) {
    c = a + b;
  }
  
  Serial.println("Benchmark 01F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float addition BA
  for (i = 0; i < N; ++i) {
    c = b + a;
  }
  
  Serial.println("Benchmark 02F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float subtraction AB
  for (i = 0; i < N; ++i) {
    c = a - b;
  }
  
  Serial.println("Benchmark 03F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float subtraction BA
  for (i = 0; i < N; ++i) {
    c = b - a;
  }
  
  Serial.println("Benchmark 04F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float multiplication AB
  for (i = 0; i < N; ++i) {
    c = a * b;
  }
  
  Serial.println("Benchmark 05F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float multiplication BA
  for (i = 0; i < N; ++i) {
    c = b * a;
  }
  
  Serial.println("Benchmark 06F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float division AB
  for (i = 0; i < N; ++i) {
    c = a / b;
  }
  
  Serial.println("Benchmark 07F");
  Serial.flush();
  delay(100);

  // FLOAT
  // =========>
  // Benchmark for float division BA
  for (i = 0; i < N; ++i) {
    c = b / a;
  }
  
  Serial.println("Benchmark 08F");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double assignment
  for (i = 0; i < N; ++i) {
    dc = da;
  }
  
  Serial.println("Benchmark 00D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double addition AB
  for (i = 0; i < N; ++i) {
    dc = da + db;
  }
  
  Serial.println("Benchmark 01D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double addition BA
  for (i = 0; i < N; ++i) {
    dc = db + da;
  }
  
  Serial.println("Benchmark 02D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double subtraction AB
  for (i = 0; i < N; ++i) {
    dc = da - db;
  }
  
  Serial.println("Benchmark 03D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double subtraction BA
  for (i = 0; i < N; ++i) {
    dc = db - da;
  }
  
  Serial.println("Benchmark 04D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double multiplication AB
  for (i = 0; i < N; ++i) {
    dc = da * db;
  }
  
  Serial.println("Benchmark 05D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double multiplication BA
  for (i = 0; i < N; ++i) {
    dc = db * da;
  }
  
  Serial.println("Benchmark 06D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double division AB
  for (i = 0; i < N; ++i) {
    dc = da / db;
  }
  
  Serial.println("Benchmark 07D");
  Serial.flush();
  delay(100);

  // DOUBLE
  // =========>
  // Benchmark for double division BA
  for (i = 0; i < N; ++i) {
    dc = db / da;
  }
  
  Serial.println("Benchmark 08D");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double assignment
  for (i = 0; i < N; ++i) {
    qc = qa;
  }
  
  Serial.println("Benchmark 00Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double addition AB
  for (i = 0; i < N; ++i) {
    qc = qa + qb;
  }
  
  Serial.println("Benchmark 01Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double addition BA
  for (i = 0; i < N; ++i) {
    qc = qb + qa;
  }
  
  Serial.println("Benchmark 02Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double subtraction AB
  for (i = 0; i < N; ++i) {
    qc = qa - qb;
  }
  
  Serial.println("Benchmark 03Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double subtraction BA
  for (i = 0; i < N; ++i) {
    qc = qb - qa;
  }
  
  Serial.println("Benchmark 04Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double multiplication AB
  for (i = 0; i < N; ++i) {
    qc = qa * qb;
  }
  
  Serial.println("Benchmark 05Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double multiplication BA
  for (i = 0; i < N; ++i) {
    qc = qb * qa;
  }
  
  Serial.println("Benchmark 06Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double division AB
  for (i = 0; i < N; ++i) {
    qc = qa / qb;
  }
  
  Serial.println("Benchmark 07Q");
  Serial.flush();
  delay(100);

  // LONG DOUBLE
  // =========>
  // Benchmark for long double division BA
  for (i = 0; i < N; ++i) {
    qc = qb / qa;
  }
  
  Serial.println("Benchmark 08Q");
  Serial.flush();
  delay(100);


  // END
  Serial.println("Loop END");
  Serial.flush();

  delay(5000);
}
