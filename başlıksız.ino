 ​#​define​ ​led​ ​3 
 ​#​define​ ​maxAmp​ (​512​) 
 ​#​define​ ​dBPinNum​ ​0
 
 int RefdBarv;
  
 ​String warningstr =   ​"​dB. Kabul edilebilir değerin üstünde.​"​; 
 ​String standardstr =  ​"​dB. Kabul edilebilir değer aralığında.​"​; 
  
 ​void​ ​setup​() 
 ​{ 
 ​  ​pinMode​(led, OUTPUT); 
 ​  ​pinMode​(dBPinNum, INPUT); 
 ​  Serial.​begin​(​9600​); 
 ​} 
  
 ​void​ ​loop​() 
 ​{ 
 ​  ​float​ dBval=​DecibelMeter​(); 
 ​  ​if​(dBval>​70​) 
 ​  { 
 ​    Serial.​println​(dBval+warningstr); 
 ​    ​digitalWrite​(led, HIGH); 
 ​  } 
 ​  ​else​ ​if​(dBval<=​70​) 
 ​  { 
 ​    Serial.​println​(dBval+standardstr); 
 ​    ​digitalWrite​(led, LOW); 
 ​  } 
 ​} 
  
 ​float​ ​DecibelMeter​()  
 ​{
   float​ decibel = ​0​;
   int ARV = 0;
   
   ARV = analogRead(dBPinNum);
 ​  decibel = ​(ARV / ​refdB​arv); 
 ​  ​double​ dB = 20​*(​log10​(decibel))+X; //Replace X with your reference dB value.
 ​  ​return​ dB; 
 ​}
 
/*void calibration ()
 {
   //play sound at a known dB level. Let this value be X dB.
   refdBarv = analogRead(dBPinNum); //This is the value of X dB in ARV.   
 }*/
 