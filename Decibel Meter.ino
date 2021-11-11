#include "Sixfab_Tracker.h"

SixfabTracker GSM_module;
#define led 5
#define maxAmp (512)
#define nMes (1024*2)
String gpsSentence;
int dBPinNum = 5; 
float decibel = 0;

String smsGPSInfo;
String soundString = smsGPSInfo + "konumundaki ses seviyesi";
String stringOne = soundString + decibel;
String warningSMSstr = stringOne + "dB. Kabul edilebilir değerin üstünde.";
String standardSMSstr = stringOne + "dB. Kabul edilebilir değer aralığında.";
String phoneNumber = "05058233362";

void setup() 
{
  while(!DEBUG); 
  delay(2000);
  GSM_module.init();
  pinMode(led, OUTPUT);
}

void loop()
{
  digitalWrite(led, LOW);
  delay(5000);
  if (decibel >= 70)
  {
    digitalWrite(led, HIGH);
    GSM_module.sendSMS(phoneNumber.c_str(),warningSMSstr.c_str());
  }

  else if(decibel < 70)
  {
    digitalWrite(led, LOW);
    GSM_module.sendSMS(phoneNumber.c_str(), standardSMSstr.c_str());
  }
}

float DecibelMeter() 
{
    long soundVolAvg = 0, soundVolMax = 0, soundVolRMS = 0;
    for (int i = 0; i < nMes; i++)
    {
        int k = analogRead(dBPinNum);
        int amp = abs(k - maxAmp);
        //amp <<= VolumeGainFactorBits;
        soundVolMax = max(soundVolMax, amp);
        soundVolAvg += amp;
        soundVolRMS += ((long)amp*amp);
    }
    soundVolAvg /= nMes;
    soundVolRMS /= nMes;
    float soundVolRMSflt = sqrt(soundVolRMS);
    float decibel = 20.0*log10(soundVolRMSflt /maxAmp);
    return decibel;
}

String GPSDetector()
{
  gpsSentence = GSM_module.getNmeaSentence();
  if (gpsSentence.startsWith("$GPRMC") || gpsSentence.startsWith("$GNRMC") )
  {  
    DEBUG.println(gpsSentence); // displays raw RMC sentence
    returnData();  // returns $GPRMC or $GNRMC
    removeString();  //removes $GPRMC or $GNRMC

//UTC
    String utc = returnData();//print(utc);
    removeString();    // removes UTC

//Validity
    String validity = returnData();
    removeString();    //removes validity
    
//Latitude
    String lat = returnData();  
    removeString();  //remove latitude from the string

//North/South
    String northOrSouth = returnData();
    removeString();
  
//Longitude
    
    String lon = returnData();
    removeString();     //remove latitude from the string 
    
    String parsing = " , ";
    utc = utc + parsing;
    lat = lat + parsing;
    smsGPSInfo = utc + lat + lon;
  }
  return smsGPSInfo;
}

String returnData()
{
  int pos = gpsSentence.indexOf(','); // return index of first comma (,)
  return gpsSentence.substring(0,pos); // returns the String from 0 index till comma
}

void removeString()
{
  int pos=gpsSentence.indexOf(',');
  gpsSentence.remove(0, pos+1);
}