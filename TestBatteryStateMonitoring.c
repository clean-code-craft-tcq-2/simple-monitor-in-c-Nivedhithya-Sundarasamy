#include <stdio.h>
#include <assert.h>
#include "BatteryStateMonitoring.h"


void testCheckBatteryCondition(float temperature, float SoC, float chargeRate, enum alertLanguageID alertlanguageID, int expectedStatus){
	assert(checkBatteryCondition(temperature, SoC, chargeRate, alertlanguageID) == expectedStatus);
}

int main() {
	testCheckBatteryCondition(20, 45, 0.6, ENGLISH, 1);
	testCheckBatteryCondition(55, 100, 0.9, ENGLISH, 0);
	testCheckBatteryCondition(43, 90, 0.6, GERMAN, 0);
	testCheckBatteryCondition(1, 70, 0.9, ENGLISH, 0);
	testCheckBatteryCondition(-1, 70, 0.9, ENGLISH, 0);
	testCheckBatteryCondition(20, 90, 0.6, GERMAN, 0);
	testCheckBatteryCondition(20, 78, 0.6, ENGLISH, 0);
	testCheckBatteryCondition(20, 22, 0.6, ENGLISH, 0);
	testCheckBatteryCondition(20, 10, 0.6, GERMAN, 0);
	testCheckBatteryCondition(20, 45, 0.9, ENGLISH, 0);
	testCheckBatteryCondition(20, 45, 0.0, GERMAN, 0);
}
