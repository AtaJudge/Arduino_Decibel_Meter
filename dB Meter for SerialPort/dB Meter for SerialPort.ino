/*
MIT License

Copyright (c) 2021 Ata Berke YARGIÇ (AtaJudge)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define led 3
#define maxAmp (512)
#define nMes (1024*2)
#define dBPinNum 0
float decibel = 0;

String warningstr="dB. Out of the acceptable range.";
String standardstr="dB. Within the acceptable range.";

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(dBPinNum, INPUT);
  Serial.begin(9600);
}

void loop()
{
  float dBval=DecibelMeter();
  if(dBval>70)
  {
    Serial.println(dBval+warningstr);
    digitalWrite(led, HIGH);
  }
  else if(dBval<=70)
  {
    Serial.println(dBval+standardstr);
    digitalWrite(led, LOW);
  }
}

double DecibelMeter() 
{
  float decibel ;
    
  decibel = analogRead(dBPinNum) * (5.0 / 362);
  double dB = - 20*(log10(decibel));
    
  return dB;
}
