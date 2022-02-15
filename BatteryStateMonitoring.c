#include <stdio.h>
#include <string.h>
#include "BatteryStateMonitoring.h"

enum parameterState{NORMAL = 1, LOW_BREACH, LOW_WARNING, HIGH_WARNING, HIGH_BREACH};

//Array to add/remove parameters to enable/disable warning alerts.
const char* parameterNamesEnabledForWarning[] = {"Temperature" , "State of Charge"};

int numberOfParametersEnabledForWarning =
	sizeof(parameterNamesEnabledForWarning) / sizeof(parameterNamesEnabledForWarning[0]);

char* arrayOfAlertStrings[][5] = {
	[ENGLISH] = {
	"Battery Status: Normal ",
	"Battery Status: Low Breach ",
	"Battery Status: Low Warning ",
	"Battery Status: High Warning ",
	"Battery Status: High Breach "
	},
	[GERMAN] = {
	"Batteriestatus: Normal ",
	"Batteriestatus: Niedrige Verletzung ",
	"Batteriestatus: Niedrige Warnung ",
	"Batteriestatus: Hohe Warnung ",
	"Batteriestatus: Hoher Bruch "
	}
};

void printOnConsole(const char* statement) {
	printf("%s \n", statement);
}

void setAlertStatement(const char* parameter, enum parameterState parameterstate,
		enum alertLanguageID alertlanguageID, char* alertStatement) {
	strcpy(alertStatement, arrayOfAlertStrings[alertlanguageID][parameterstate-1]);
	strcat(alertStatement,  parameter);
}

int batteryAlert(const char* parameter, enum parameterState parameterstate, enum alertLanguageID alertlanguageID) {
	char alertStatement[100];
	setAlertStatement(parameter, parameterstate, alertlanguageID, alertStatement);	
	printOnConsole(alertStatement);
	return 1; 
}

_Bool checkIfParamterInRange(float parameterValue, float minValue, float maxValue, int parameterStateChecked,
		const char* parameter, enum alertLanguageID alertlanguageID) {
	return (parameterValue > minValue && parameterValue < maxValue) ? batteryAlert(parameter, parameterStateChecked, alertlanguageID) : 0;
}

_Bool checkIfParameterIsWithinUpperLimit(float parameterValue, float maxValue, int parameterStateChecked,
	const char* parameter, enum alertLanguageID alertlanguageID) {
	return (parameterValue  > maxValue) ?  batteryAlert(parameter, parameterStateChecked, alertlanguageID) : 0;
}

_Bool checkIfParameterIsWithinLowerLimit(float parameterValue, float minValue, int parameterStateChecked,
	const char* parameter, enum alertLanguageID alertlanguageID) {
	return (parameterValue <  minValue) ?  batteryAlert(parameter, parameterStateChecked, alertlanguageID) : 0;
}

_Bool checkIfParameterEnabledForWarningStatus(const char* parameterName, int parameterIndex) {
		return (strcmp(parameterName,parameterNamesEnabledForWarning[parameterIndex])==0) ? 1 : 0;
}

void checkParameterWarningStatus(float parameterValue, float minThreshold, float minTolerance, float maxTolerance, float maxThreshold,
	const char* parameter, enum alertLanguageID alertlanguageID, int *parameterStatus) {
	*parameterStatus = (*parameterStatus) && (!checkIfParamterInRange(parameterValue, maxTolerance, maxThreshold,
	HIGH_WARNING, parameter, alertlanguageID)) && (!checkIfParamterInRange(parameterValue, minThreshold,
	minTolerance, LOW_WARNING, parameter, alertlanguageID)); 
}
	
int checkParameterEnabledForWarningStatus(float parameterValue, float minThreshold, float minTolerance, float maxTolerance, float maxThreshold,
	const char* parameter, enum alertLanguageID alertlanguageID, int parameterStatus) {
	for(int parameterIndex = 0; parameterIndex < numberOfParametersEnabledForWarning; parameterIndex++) {
		int parameterWarningStatus;
		parameterWarningStatus = checkIfParameterEnabledForWarningStatus(parameter, parameterIndex);
		if(parameterWarningStatus) {
			checkParameterWarningStatus(parameterValue, minThreshold, minTolerance, maxTolerance, maxThreshold,
			parameter, alertlanguageID, &parameterStatus);	
		}
	}
	return parameterStatus;
}
	
int checkParameterStatus(float parameterValue, float minThreshold, float minTolerance, float maxTolerance, float maxThreshold,
	const char* parameter, enum alertLanguageID alertlanguageID) {
	int parameterStatus;

	parameterStatus = (checkIfParamterInRange(parameterValue, minTolerance, maxTolerance, NORMAL, parameter, alertlanguageID)) ||
		((!checkIfParameterIsWithinUpperLimit(parameterValue, maxThreshold, HIGH_BREACH, parameter, alertlanguageID)) && 
		(!checkIfParameterIsWithinLowerLimit(parameterValue, minThreshold, LOW_BREACH, parameter, alertlanguageID)));

	return checkParameterEnabledForWarningStatus(parameterValue, minThreshold, minTolerance, maxTolerance, maxThreshold,
			parameter, alertlanguageID, parameterStatus);
}

int checkBatteryCondition(float temperature, float SoC, float chargeRate, enum alertLanguageID alertlanguageID){
	int batteryStatus;
	batteryStatus = (checkParameterStatus(temperature, MIN_THRESHOLD_BATT_TEMP, MIN_TOLERANCE_BATT_TEMP, MAX_TOLERANCE_BATT_TEMP,
		MAX_THRESHOLD_BATT_TEMP, "Temperature", alertlanguageID)) && (checkParameterStatus(SoC, MIN_THRESHOLD_BATT_SoC, MIN_TOLERANCE_BATT_SoC,
		MAX_TOLERANCE_BATT_SoC, MAX_THRESHOLD_BATT_SoC, "State of Charge", alertlanguageID)) && (checkParameterStatus(chargeRate,
		MIN_THRESHOLD_BATT_CHARGE_RATE, MIN_TOLERANCE_BATT_CHARGE_RATE, MAX_TOLERANCE_BATT_CHARGE_RATE,
		MAX_THRESHOLD_BATT_CHARGE_RATE, "Charge Rate", alertlanguageID));
	return batteryStatus;	
}
