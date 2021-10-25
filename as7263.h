#include "esphome.h"
#include "AS726X.h"

class Mi7263 : public PollingComponent, public Sensor
{
public:
  AS726X sensor; //Creates the sensor object
  Sensor *temperature_sensor = new Sensor();
  Sensor *ondaR = new Sensor();
  Sensor *ondaS = new Sensor();
  Sensor *ondaT = new Sensor();
  Sensor *ondaU = new Sensor();
  Sensor *ondaV = new Sensor();
  Sensor *ondaW = new Sensor();
  byte GAIN = 2;
  byte MEASUREMENT_MODE = 2;

  // constructor
  Mi7263() : PollingComponent(3000) {}

  float get_setup_priority() const override { return esphome::setup_priority::BUS; }

  void setup() override
  {
    Wire.begin();
    sensor.begin(Wire, GAIN, MEASUREMENT_MODE);
  }

  void update() override
  {

    sensor.takeMeasurementsWithBulb();

    float temperature = sensor.getTemperature();
    temperature_sensor->publish_state(temperature);

    float MondaR = sensor.getCalibratedR();
    ondaR->publish_state(MondaR);

    float MondaS = sensor.getCalibratedS();
    ondaS->publish_state(MondaS);

    float MondaT = sensor.getCalibratedT();
    ondaT->publish_state(MondaT);

    float MondaU = sensor.getCalibratedU();
    ondaU->publish_state(MondaU);

    float MondaV = sensor.getCalibratedV();
    ondaV->publish_state(MondaV);

    float MondaW = sensor.getCalibratedW();
    ondaW->publish_state(MondaW);
  }
};
