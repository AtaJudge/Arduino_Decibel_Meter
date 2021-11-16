/*
MIT License

Copyright (c) 2021 Ata Berke YARGIÇ

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

#define led 3 //LED connection pin.
#define dBPinNum 0 //Mic connection pin.
#define X 80 //Reference dB value. (Change it by your own reference)

float Ref_dB_arv;//X.0 dB

String warningstr="dB. Out of the acceptable range.";
String standardstr="dB. Within the acceptable range.";

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(dBPinNum, INPUT);
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

float DecibelMeter()
{
  float decibel = 0;
  int ARV = 0;

  ARV=analogRead(dBPinNum);
  decibel=(ARV/Ref_dB_arv);
  double dB = 20*(log10(decibel))+X;
  return dB;
}

/*
void calibration()
{
  //Play sound at known dB level. Let this value be X dB.
  Ref_dB_arv = analogRead(dBPinNum); //This is the value of X dB in analog (0-1023) value.
}
*/
