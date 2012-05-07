#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_power(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI (watt) */
		{"W", 1, 0, {"watt","J/s",""}},
		{"kW", 1e3, 0, {"watt","kJ/s",""}},
		/* calorie */
		{"cal/s", CALORIE_IT_TO_JOULE, 0, {"cal_IT/s","cal(IT)/s","caloriepersecond","calorie per second",""}},
		/* Miscellaneous */
		{"kgf m/s", 1.0 * GRAVACC, 0, {"kgf*m/s","kgfm/s","kilogramforcemeterpersecond","kilogrammeforcemetrepersecond","kilogramforce meter per second","kilogrammeforce metre per second","kilogramforce-meter per second","kilogrammeforce-metre per second","kilogram-force meter per second","kilogramme-force metre per second","kilogram-force-meter per second","kilogramme-force-metre per second",""}},
		{"p", 100.0 * GRAVACC, 0, {"poncelet",""}},
		{"erg/s", 1e-7, 0, {""}},
		{"atm ccm", ATMOSPHERE * 1e-6 / MINUTE_TO_SECOND, 0, {"atmccm",""}},
		{"atm ccs", ATMOSPHERE * 1e-6, 0, {"atmccs",""}},
		{"l atm/min", ATMOSPHERE * 1e-3 / MINUTE_TO_SECOND, 0, {"latm/min","l*atm/min","litreatmosphereperminute","literatmosphereperminute","litreatmosphere per minute","literatmosphere per minute","litre-atmosphere per minute","liter-atmosphere per minute",""}},
		{"l atm/s", ATMOSPHERE * 1e-3, 0, {"latm/s","l*atm/s","litreatmospherepersecond","literatmospherepersecond","litreatmosphere per second","literatmosphere per second","litre-atmosphere per second","liter-atmosphere per second",""}},
		{"P_p", PLANCK_POWER, 0, {"planckpower","planck power","Planck power",""}},
		/* British thermal unit */
		{"BTU_IT/h", BTU_IT_TO_JOULE / HOUR_TO_SECOND, 0, {"BTU(IT)/h","Btu_IT/h","Btu(IT)/h","BTU/h","Btu/h","btu/h",""}},
		{"BTU_IT/min", BTU_IT_TO_JOULE / MINUTE_TO_SECOND, 0, {"BTU(IT)/min","Btu_IT/min","Btu(IT)/min","BTU/min","Btu/min","btu/min",""}},
		{"sq ft EDR", 240.0 * BTU_IT_TO_JOULE / HOUR_TO_SECOND, 0, {"sqftedr","sqftEDR","ft^2 edr","ft^2 EDR","ft^2edr","ft^2EDR","ft2 edr","ft2 EDR","ft2edr","ft2EDR",""}},
		{"BTU_IT/s", BTU_IT_TO_JOULE, 0, {"BTU(IT)/s","Btu_IT/s","Btu(IT)/s","BTU/s","Btu/s","btu/s",""}},
		/* Imperial */
		{"ft lbf/h", FOOTLBF_TO_JOULE / HOUR_TO_SECOND, 0, {"ft*lbf/h","ftlbf/h","footpoundforceperhour","footpoundforce per hour","foot-poundforce per hour","foot-pound force per hour",""}},
		{"ft lbf/min", FOOTLBF_TO_JOULE / MINUTE_TO_SECOND, 0, {"ft*lbf/min","ftlbf/min","footpoundforceperminute","footpoundforce per minute","foot-poundforce per minute","foot-pound force per minute",""}},
		{"ft lbf/s", FOOTLBF_TO_JOULE, 0, {"ft*lbf/s","ftlbf/s","footpoundforcepersecond","footpoundforce per second","foot-poundforce per second","foot-pound force per second",""}},
		{"hp", 550.0 * FOOTLBF_TO_JOULE, 0, {"horsepower",""}},
		{"PS", 75.0 / GRAVACC, 0, {"hp(metric)","horsepower(metric)","metrichorsepower","metric horsepower",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "power", &cnvval);
	return ret;
}
#undef ELECTRON_VOLT
#undef WATT_HOUR
#undef CALORIE_IT
#undef CALORIE_TH
#undef BTU_IT
#undef BTU_59F
#undef FOOT_LBF
