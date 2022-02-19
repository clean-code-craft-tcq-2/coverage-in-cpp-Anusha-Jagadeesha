#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
BatteryCharacter batteryChartest;
TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(46, 10, 40) == TOO_HIGH);
  REQUIRE(inferBreach(20, 10, 30) == NORMAL);
}

TEST_CASE("classifyTemperatureBreach the breach according to limits") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
}

TEST_CASE("test check and alert") {
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChartest , 30) == true);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChartest , 30) == true);

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChartest , 45) == true);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChartest , 56) == true);

  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryChartest , -5) == true);
  REQUIRE(checkAndAlert(TO_EMAIL, batteryChartest , -10) == true);
}

TEST_CASE("test send to controller") {
  REQUIRE(sendToController(NORMAL) == true);
  REQUIRE(sendToController(TOO_LOW) == true);
  REQUIRE(sendToController(TOO_HIGH) == true);
}

// TEST_CASE("test send to email") {
//   REQUIRE(sendToEmail(NORMAL) == true);
//   REQUIRE(sendToEmail(TOO_LOW) == true);
//   REQUIRE(sendToEmail(TOO_HIGH) == true);
// }
