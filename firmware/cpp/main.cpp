#include "cathode_control_task.h"
#include "temperature_sensor_task.h"
#include "wifi_services.h"

CathodeControlTaskHandler cathodeControl;
TemperatureSensorTaskHandler temperatureSensor;
WifiServices wifiServices;

#define SIGNAL_PIN 3
#define HV_EN_PIN 15
#define PWM_PIN 19
#define SIGNAL_FREQUENCY_HZ 0.5 // 0.5Hz frequency for signal pin
#define PWM_FREQUENCY_HZ 1000 // 1kHz frequency for PWM pin
#define SIGNAL_INTERVAL_MS (1000 / SIGNAL_FREQUENCY_HZ)
#define PWM_INTERVAL_MS (1000 / PWM_FREQUENCY_HZ)

bool signalState = false;
bool pwmState = false;
unsigned long lastSignalToggleTime = 0;
unsigned long lastPwmToggleTime = 0;

void setup()
{
  delay(5000);

  Serial.begin(115200);
  log_d("Starting setup...");

  // Configure pins
  pinMode(HV_EN_PIN, OUTPUT);
  pinMode(SIGNAL_PIN, INPUT);
  pinMode(PWM_PIN, OUTPUT);
  
  // Initialize pins
  digitalWrite(HV_EN_PIN, LOW);
  digitalWrite(PWM_PIN, LOW);

  // wifiServices.setup(DEVICE_NAME);

  // cathodeControl.createTask();
  // temperatureSensor.createTask();
  // wifiServices.createTask();

  // wifiServices.registerGetDataCallback<float>("/temperature", []() -> float
  //                                      { return temperatureSensor.isSensorFound() ? temperatureSensor.getTemperature() : -999; });
  // wifiServices.registerSetDisplayCallback([&](bool state)
  //                                         { cathodeControl.setDisplay(state); });
  // wifiServices.registerSetMessageCallback("/cathodeControl", [](const char *message)
  //                                         { if (strlen(message) > 0)  cathodeControl.setMessage(message);
  //                                           return cathodeControl.getMessage(); });

  log_d("Setup complete");
}

void loop()
{
  unsigned long currentTime = millis();
  
  // Read SIGNAL_PIN and set HV_EN_PIN to match
  bool signalInput = digitalRead(SIGNAL_PIN);
  digitalWrite(HV_EN_PIN, signalInput);
  
  // Toggle PWM_PIN at 1kHz
  if (currentTime - lastPwmToggleTime >= PWM_INTERVAL_MS) {
    pwmState = !pwmState;
    digitalWrite(PWM_PIN, pwmState ? HIGH : LOW);
    lastPwmToggleTime = currentTime;
  }
}
  if (currentTime - lastPwmToggleTime >= PWM_INTERVAL_MS) {
    pwmState = !pwmState;
    digitalWrite(PWM_PIN, pwmState ? HIGH : LOW);
    lastPwmToggleTime = currentTime;
  }
}
