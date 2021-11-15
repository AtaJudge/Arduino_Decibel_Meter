 #define led 3
 #define maxAmp 512
 #define dBPinNum 0
 #define X 80

int Ref_dB_arv;

String warningstr="dB. Out of the acceptable range.";
String standartstr="dB. Within the acceptable range.";

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
    Serial.println(dBval+standartstr);
    digitalWrite(led, LOW);
  }
}

float DecibelMeter()
{
  float decibel = 0;
  int ARV = 0;

  ARV=analogRead(dBPinNum);
  decibel=(ARV/Ref_dB_arv);
  double dB = 20*(log10(decibel))+X; //Replace X with your referance dB value.
  return dB;
}

/*
void calibration()
{
  //Play sound at known dB level. Let this value be X dB.
  Ref_dB_arv = analogRead(dBPinNum); //This is the value of X dB in analog (0-1023) value.
}
*/