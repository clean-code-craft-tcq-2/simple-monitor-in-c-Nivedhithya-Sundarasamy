#include <stdio.h>
#include <string.h>
#include "BatteryStateMonitoring.h"

char alertString[100] = "Alert: Battery Status: Out of Range: ";

int (*fpPrint) (const char*) = &printOnConsole;

int printOnConsole(const char* statement) {
	printf("%s \n", statement);
	return 0;
}

int checkIfParamterInRange(float parameterValue, float min_threshold, float max_threshold) {
	if (parameterValue < min_threshold || parameterValue > max_threshold) {
		return 0;
	}
	return 1;
}

int checkIfParameterIsWithinLimit(float parameterValue, float max_limit) {
	if (parameterValue  > max_limit) {
		return 0;
	}
	return 1;
}

int checkParameterStatus(int status, const char* parameter) {
	char statement[100];
	strcpy(statement, alertString);
	strcat(statement, parameter);
	if (status == 0) {
		(*fpPrint)(statement);
	}
	return status;
}

int checkBatteryTemperature(float temperature) {
	int status;
	status = checkIfParamterInRange(temperature, MIN_THRESHOLD_BATT_TEMP, MAX_THRESHOLD_BATT_TEMP);
	status = checkParameterStatus(status, "Temperature");
	return status;
}

int checkBatterySoC(float SoC) {
	int status;
	status = checkIfParamterInRange(SoC, MIN_THRESHOLD_BATT_SoC, MAX_THRESHOLD_BATT_SoC);
	status = checkParameterStatus(status, "State of Charge");
	return status;
}

int checkBatteryChargeRate(float chargeRate){
	int status;
	status = checkIfParameterIsWithinLimit(chargeRate, MAX_THRESHOLD_BATT_CHARGE_RATE);
	status = checkParameterStatus(status, "Charge Rate");
	return status;
}

int checkBatteryCondition(float temperature, float SoC, float chargeRate){
	int batt_status;
	batt_status =(checkBatteryTemperature(temperature)) && (checkBatterySoC(SoC)) && (checkBatteryChargeRate(chargeRate));
	return batt_status;	
}
