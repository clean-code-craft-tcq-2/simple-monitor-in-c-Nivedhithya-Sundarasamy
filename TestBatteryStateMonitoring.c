#include <stdio.h>
#include <assert.h>
#include "BatteryStateMonitoring.h"

int printCallCount = 0;

int fakePrintOnConsole(const char* statement) {
	printf("%s \n",statement);
	printCallCount++;
	return 0;
}

void testCheckBatteryTemperature(float temperature, int expectedStatus) {
	assert(checkBatteryTemperature(temperature) == expectedStatus);
}
 
void testCheckBatterySoC(float SoC, int expectedStatus) {
	assert(checkBatterySoC(SoC) == expectedStatus);
}

void testCheckBatteryChargeRate(float chargeRate, int expectedStatus){
	assert(checkBatteryChargeRate(chargeRate) == expectedStatus);
}
 
void testCheckBatteryCondition(float temperature, float SoC, float chargeRate, int expectedStatus){
	assert(checkBatteryCondition(temperature, SoC, chargeRate) == expectedStatus);
}

int main() {
	fpPrintOnConsole = &fakePrintOnConsole; //Assigning fake print function for testing
	testCheckBatteryTemperature(30, 1);
	testCheckBatteryTemperature(55, 0);
	testCheckBatterySoC(50, 1);
	testCheckBatterySoC(85, 0);
	testCheckBatteryChargeRate(0.7, 1);
	testCheckBatteryChargeRate(0.9, 0);
	testCheckBatteryCondition(20, 45, 0.6, 1);
	testCheckBatteryCondition(55, 100, 0.9, 0);
	testCheckBatteryCondition(43, 90, 0.6, 0);
	testCheckBatteryCondition(43, 70, 0.9, 0);
	assert(printCallCount == 6);
}
