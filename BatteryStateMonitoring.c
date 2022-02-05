#include <stdio.h>
#include <string.h>
#include "BatteryStateMonitoring.h"

char alertString[100] = "Alert: Battery Status: Out of Range: ";

int (*fpPrintOnConsole) (const char*) = &printOnConsole;

int printOnConsole(const char* statement) {
	printf("%s \n", statement);
	return 0;
}

int rangeBasedConditionCheck(float parameterValue, float min_threshold, float max_threshold) {
	if (parameterValue < min_threshold || parameterValue > max_threshold) {
		return 0;
	}
	return 1;
}

int limitBasedConditionCheck(float parameterValue, float max_limit) {
	if (parameterValue  > max_limit) {
		return 0;
	}
	return 1;
}

int statusCheck(int status, const char* parameter) {
	char statement[100];
	strcpy(statement, alertString);
	if (status == 0) {
		strcat(statement, parameter);
		(*fpPrintOnConsole)(statement);
	}
	return status;
}

int checkBatteryTemperature(float temperature) {
	int status;
	status = rangeBasedConditionCheck(temperature, MIN_THRESHOLD_BATT_TEMP, MAX_THRESHOLD_BATT_TEMP);
	status = statusCheck(status, "Temperature");
	return status;
}

int checkBatterySoC(float SoC) {
	int status;
	status = rangeBasedConditionCheck(SoC, MIN_THRESHOLD_BATT_SoC, MAX_THRESHOLD_BATT_SoC);
	status = statusCheck(status, "State of Charge");
	return status;
}

int checkBatteryChargeRate(float chargeRate){
	int status;
	status = limitBasedConditionCheck(chargeRate, MAX_THRESHOLD_BATT_CHARGE_RATE);
	status = statusCheck(status, "Charge Rate");
	return status;
}

int checkBatteryCondition(float temperature, float SoC, float chargeRate){
	int status;
	status =(checkBatteryTemperature(temperature)) && (checkBatterySoC(SoC)) && (checkBatteryChargeRate(chargeRate));
	return status;	
}

