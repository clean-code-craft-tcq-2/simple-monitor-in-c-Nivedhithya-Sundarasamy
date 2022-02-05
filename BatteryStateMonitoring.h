#define MIN_THRESHOLD_BATT_TEMP 0
#define MAX_THRESHOLD_BATT_TEMP 45
#define MIN_THRESHOLD_BATT_SoC 20
#define MAX_THRESHOLD_BATT_SoC 80
#define MAX_THRESHOLD_BATT_CHARGE_RATE 0.8


extern int checkBatteryTemperature(float temperature);
extern int checkBatterySoC(float SoC);
extern int checkBatteryChargeRate(float chargeRate);
extern int checkBatteryCondition(float temperature, float SoC, float chargeRate);
int printOnConsole(const char* statement);
extern int (*fpPrintOnConsole) (const char*);
