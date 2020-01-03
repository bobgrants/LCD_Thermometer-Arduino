

// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
int lowestTemp;

void setup() {
  Serial.begin( 9600);
  SetupLCD();
  lowestTemp = 100;
}

void SetupLCD() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World !!!");
}

void loop() {
  PrintCurrentTemp();
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if ( millis( ) - measurement_timestamp > 3000ul )
  {
    if ( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return ( true );
    }
  }
  return ( false );
}

void PrintCurrentTemp() {
  float temperature;
  float humidity;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if ( measure_environment( &temperature, &humidity ) == true )
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current Temp ");
    lcd.print(temperature, 0);

    if (temperature < lowestTemp) {
      lowestTemp = temperature;
    }

    lcd.setCursor(0, 1);
    lcd.print("Lowest Temp ");
    lcd.print(lowestTemp);

    Serial.print(temperature);
  }
}
