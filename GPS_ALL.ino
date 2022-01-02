
/* On UNO...
 * GPS data being recieved if red LED flashes at 1 sec rate
 * static const int RXPin = 4, TXPin = 3; ***BUT** TXD needs to on pin 4 
 * Using GPS Module GPS NEO-6M from MakerFocus on Amazon
   This sample code demonstrates just about every built-in operation of TinyGPS++ (TinyGPSPlus).
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;   //TXPin is actually pin 4, RXPin is probably pin 3
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// For stats that happen every 5 seconds
unsigned long last = 0UL;

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  Serial.println(F("FIRST LINE"));     // Serial.println prints on same line?
  Serial.println(F("2ND LINE"));       // Serial.print will make a new line?
  Serial.print(F("3RD LINE")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("4TH LINE"));
}

void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated())
  {
    Serial.print(F("LOCATION        "));
    Serial.print(gps.location.age());
    Serial.print(F("ms Raw Lat="));
    Serial.print(gps.location.rawLat().negative ? "-" : "+");
    Serial.print(gps.location.rawLat().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLat().billionths);
    Serial.print(F(" billionths],  Raw Long="));
    Serial.print(gps.location.rawLng().negative ? "-" : "+");
    Serial.print(gps.location.rawLng().deg);
    Serial.print("[+");
    Serial.print(gps.location.rawLng().billionths);
    Serial.print(F("   Lat="));
    Serial.print(gps.location.lat(), 3);
    Serial.print(F(" Long="));
    Serial.println(gps.location.lng(), 3);
  }

  else if (gps.date.isUpdated())
  {
    Serial.print(F("DATE              "));
    Serial.print(gps.date.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.date.value());
    Serial.print(F(" Year="));
    Serial.print(gps.date.year());
    Serial.print(F(" Month="));
    Serial.print(gps.date.month());
    Serial.print(F(" Day="));
    Serial.println(gps.date.day());
  }

  else if (gps.time.isUpdated())
  {
    Serial.print(F("TIME               "));
    Serial.print(gps.time.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.time.value());
    Serial.print(F(" Hour="));
    Serial.print(gps.time.hour());
    Serial.print(F(" Minute="));
    Serial.print(gps.time.minute());
    Serial.print(F(" Second="));
    Serial.print(gps.time.second());
    Serial.print(F(" Hundredths="));
    Serial.println(gps.time.centisecond());
  }

  else if (gps.speed.isUpdated())
  {
    Serial.print(F("SPEED             "));
    Serial.print(gps.speed.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.speed.value());
    Serial.print(F(" Knots="));
    Serial.print(gps.speed.knots());
    Serial.print(F(" MPH="));
    Serial.println(gps.speed.mph());
    Serial.print(F(" m/s="));
    Serial.print(gps.speed.mps());
    Serial.print(F(" km/h="));
    Serial.println(gps.speed.kmph());
  }

  else if (gps.course.isUpdated())
  {
    Serial.print(F("COURSE            "));
    Serial.print(gps.course.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.course.value());
    Serial.print(F(" Deg="));
    Serial.println(gps.course.deg());
  }

  else if (gps.altitude.isUpdated())
  {
    Serial.print(F("ALTITUDE           "));
    Serial.print(gps.altitude.age());
    Serial.print(F("ms Raw="));
    Serial.print(gps.altitude.value());
    Serial.print(F(" Meters="));
    Serial.print(gps.altitude.meters());
    Serial.print(F(" Miles="));
    Serial.print(gps.altitude.miles());
    Serial.print(F(" KM="));
    Serial.print(gps.altitude.kilometers());
    Serial.print(F("Feet="));
    Serial.println(gps.altitude.feet() ,0);
  }

  else if (gps.satellites.isUpdated())
  {
    Serial.print(F("SATELLITES         "));
    Serial.print(gps.satellites.age());
    Serial.print(F("ms Value="));
    Serial.println(gps.satellites.value());
  }

  else if (gps.hdop.isUpdated())
  {
     Serial.print(F("HDOP               "));      // If this is deleted, Capitol Location W/N show
     Serial.print(gps.hdop.age());              
     Serial.print(F("ms raw="));
     Serial.print(gps.hdop.value());
     Serial.print(F(" hdop="));
     Serial.println(gps.hdop.hdop());
  }

  else if (millis() - last > 5000)
  {
    Serial.println();
    if (gps.location.isValid())
    {
      static const double CAPITOL_LAT = 43.089619, CAPITOL_LON = -88.179440;
      double distanceToLondon =
        TinyGPSPlus::distanceBetween(
          gps.location.lat(),
          gps.location.lng(),
          CAPITOL_LAT, 
          CAPITOL_LON);
      double courseToLondon =
        TinyGPSPlus::courseTo(
          gps.location.lat(),
          gps.location.lng(),
          CAPITOL_LAT, 
          CAPITOL_LON);

      Serial.print(F("CAPITOL Distance="));
      Serial.print(distanceToLondon/1000*.6213712, 2);        // *0.6213712  *** change from KM o miles!!!!!!!!!
      Serial.print(F(" MILES Course-to="));
      Serial.print(courseToLondon, 6);
      Serial.print(F(" degrees ["));
      Serial.print(TinyGPSPlus::cardinal(courseToLondon));
      Serial.println(F("]"));
    }

    //Serial.print(F("DIAGS      Chars="));
    //Serial.print(gps.charsProcessed());
    //Serial.print(F(" Sentences-with-Fix="));
    //Serial.print(gps.sentencesWithFix());
    //Serial.print(F(" Failed-checksum="));
    //Serial.print(gps.failedChecksum());
    //Serial.print(F(" Passed-checksum="));
    //Serial.println(gps.passedChecksum());

    if (gps.charsProcessed() < 10)
      Serial.println(F("WARNING: No GPS data.  Check wiring."));

    last = millis();
    Serial.println();
  }
}
