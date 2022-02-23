#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include <string>
#include "typewise-alert.h"
using namespace std;

using pfun = bool (*)(BreachType);
std::map<AlertTarget, pfun> alertTargetMsg =
    {
        {AlertTarget::TO_CONTROLLER, sendToController},
        {AlertTarget::TO_EMAIL, sendToEmail}};

std::map<BreachType, std::string> sendToEmailMap =
    {
        {BreachType::TOO_LOW, "Hi, the temperature is too low"},
        {BreachType::TOO_HIGH, "Hi, the temperature is too high"},
        {BreachType::NORMAL, "Hi, the temperature is normal"}};

std::map<CoolingType, pair<int, int>> classifyTempBreachMap =
    {
        {CoolingType::PASSIVE_COOLING, make_pair(0, 35)},
        {CoolingType::HI_ACTIVE_COOLING, make_pair(0, 45)},
        {CoolingType::MED_ACTIVE_COOLING, make_pair(0, 40)}};
