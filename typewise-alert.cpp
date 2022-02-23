#include "typewise-alert.h"
#include "map_alertTarget.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit)
{
  if (value < lowerLimit)
  {
    return TOO_LOW;
  }
  if (value > upperLimit)
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC)
{
  int lowerLimit = 0;
  int upperLimit = 0;
  lowerLimit = classifyTempBreachMap.find(coolingType)->second.first;
  upperLimit = classifyTempBreachMap.find(coolingType)->second.second;
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

bool checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC)
{

  BreachType breachType = classifyTemperatureBreach(
      batteryChar.coolingType, temperatureInC);

  pfun f = alertTargetMsg.find(alertTarget)->second;
  return ((*f)(breachType));
}

bool sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return true;
}

bool sendToEmail(BreachType breachType)
{
  const char *recepient = "a.b@c.com";
  if (sendToEmailMap.find(breachType)->first < (static_cast<BreachType>(3)))
  {
    cout << "To: " << recepient << "    " << sendToEmailMap.find(breachType)->second << "\n";
    return true;
  }
  else
  {
    return false;
  }
}
