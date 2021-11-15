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