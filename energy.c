#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

#define ELECTRON_VOLT 1.60217653e-19
#define WATT_HOUR 3.6e3
#define CALORIE_IT 4.1868
#define CALORIE_TH 4.184
#define BTU_IT 1.05505585262e3
#define BTU_59F 1.054804e3
#define FOOT_LBF 1.3558179483314004
int conv_energy(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI */
		{"nJ", 1e-9, 0, {"nanojoule",""}},
		{"uJ", 1e-6, 0, {"microjoule",""}},
		{"mJ", 1e-3, 0, {"millijoule",""}},
		{"J", 1, 0, {"joule","W*s","Ws","W s","wattsecond","watt-second","C*V","CV","C V","coulombvolt","coulomb-volt",""}},
		{"kJ", 1e3, 0, {"kilojoule","kW*s","kWs","kW s","wattsecond","kilowatt-second",""}},
		{"MJ", 1e6, 0, {"megajoule","MW*s","MWs","MW s","megawattsecond","megawatt-second",""}},
		{"GJ", 1e9, 0, {"gigajoule","GW*s","GWs","GW s","gigawattsecond","gigawatt-second",""}},
		{"TJ", 1e12, 0, {"terajoule","TW*s","TWs","TW s","terawattsecond","terawatt-second",""}},
		/* electronvolt */
		{"meV", ELECTRON_VOLT * 1e-3, 0, {"millielectronvolt",""}},
		{"eV", ELECTRON_VOLT, 0, {"electronvolt","electron volt",""}},
		{"keV", ELECTRON_VOLT * 1e3, 0, {"kiloelectronvolt",""}},
		{"MeV", ELECTRON_VOLT * 1e6, 0, {"megaelectronvolt",""}},
		{"GeV", ELECTRON_VOLT * 1e9, 0, {"gigaelectronvolt",""}},
		{"TeV", ELECTRON_VOLT * 1e12, 0, {"teraelectronvolt",""}},
		/* watthour */
		{"Wh", WATT_HOUR, 0, {"W*h","W h","watthour","watt-hour",""}},
		{"kWh", WATT_HOUR * 1e3, 0, {"kW*h","kW h","kilowatthour","kilowatt-hour","BOTU","B.O.T.U","B.O.T.U.",""}},
		{"MWh", WATT_HOUR * 1e6, 0, {"MW*h","MW h","megawatthour","megawatt-hour",""}},
		{"GWh", WATT_HOUR * 1e9, 0, {"GW*h","GW h","gigawatthour","gigawatt-hour",""}},
		{"TWh", WATT_HOUR * 1e12, 0, {"TW*h","TW h","terawatthour","terawatt-hour",""}},
		/* calorie */
		{"cal", CALORIE_IT, 0, {"cal_IT","cal(IT)","calorie",""}},
		{"kcal", CALORIE_IT * 1e3, 0, {"kcal_IT","kcal(IT)","Cal","kilocalorie",""}},
		{"Mcal", CALORIE_IT * 1e6, 0, {"Mcal_IT","Mcal(IT)","megacalorie","thermie",""}},
		{"cal_th", CALORIE_TH, 0, {"cal(th)","calorie(th)",""}},
		{"cal_15degC", 4.1855, 0, {"cal(15degC)","calorie(15degC)",""}},
		{"tTNT", CALORIE_TH * 1e9, 0, {"tontnt","tonoftnt","ton of tnt","ton of TNT",""}},
		{"TCE", CALORIE_TH * 7e9, 0, {"toncoal","tonofcoal","ton of coal","tonofcoaleqv","tonofcoalequiv","tonofcoalequivalent","ton of coal equivalent",""}},
		{"TOE", CALORIE_TH * 10e9, 0, {"tonoil","tonofoil","ton of oil","tonofoileqv","tonofoilequiv","tonofoilequivalent","ton of oil equivalent",""}},
		/* Miscellaneous */
		{"gf m", 1.0 / 9.80665e-3, 0, {"gf*m","gfm","gramforcemeter","grammeforcemetre","gramforce meter","grammeforce metre","gramforce-meter","grammeforce-metre","gram-force meter","gramme-force metre","gram-force-meter","gramme-force-metre",""}},
		{"kgf m", 1.0 / 9.80665, 0, {"kgf*m","kgfm","kilogramforcemeter","kilogrammeforcemetre","kilogramforce meter","kilogrammeforce metre","kilogramforce-meter","kilogrammeforce-metre","kilogram-force meter","kilogramme-force metre","kilogram-force-meter","kilogramme-force-metre",""}},
		{"erg", 1e-7, 0, {""}},
		{"CHU", 1.899100534716e3, 0, {""}},
		{"cc atm", 0.101325, 0, {"ccatm","scc",""}},
		{"l atm", 101.325, 0, {"latm","litreatmosphere","literatmosphere","litre-atmosphere","liter-atmosphere","sl",""}},
		{"foe", 1e44, 0, {""}},
		{"Ry", 2.179872e-18, 0, {"rydberg",""}},
		{"E_h", 4.359744e-18, 0, {"hartree",""}},
		{"E_p", 1.9561e9, 0, {"planckenergy","planck energy","Planck energy",""}},
		/* British thermal unit */
		{"BTU", 1.0545e3, 0, {"BTU_ISO","BTU(ISO)","Btu_ISO","Btu(ISO)",""}},
		{"BTU_IT", BTU_IT, 0, {"BTU(IT)","Btu_IT","Btu(IT)",""}},
		{"BTU_th", 1.05435026444e3, 0, {"BTU(th)","Btu_th","Btu(th)",""}},
		{"BTU_59degF", BTU_59F, 0, {"BTU(59degF)","BTU_15degC","BTU(15degC)","Btu_59degF","Btu(59degF)","Btu_15degC","Btu(15degC)",""}},
		{"th", BTU_IT * 1e5, 0, {"therm",""}},
		{"th(US)", BTU_59F * 1e5, 0, {"therm(US)",""}},
		{"quad", BTU_IT * 1e15, 0, {""}},
		{"bboe", 6.12e9, 0, {"barreloil","barrelofoil","barrel of oil","barrelofoileqv","barrelofoilequiv","barrelofoilequivalent","barrel of oil equivalent",""}},
		/* Imperial */
		{"in lbf", FOOT_LBF / 12, 0, {"in*lbf","inlbf","inchpoundforce","inch-poundforce","inch-pound force",""}},
		{"ft lbf", FOOT_LBF, 0, {"ft*lbf","ftlbf","footpoundforce","foot-poundforce","foot-pound force",""}},
		{"ft pdl", 4.21401100938048e-2, 0, {"ft*pdl","ftpdl","footpoundal","foot-poundal",""}},
		{"hp h", 2.684519537696172792e6, 0, {"hp*h","hph","horsepowerhour","horsepower-hour",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "energy", &cnvval);
	if ((!(chainflag&MODE_CHAINED))&&(ret != RET_UNKNOWN_UNIT)) {
		printf("And equivalent mass is...\n");
		conv_mass(cnvval / ELECTRON_VOLT * 1.782661845e-36, "kg", MODE_CHAINED);
		printf("And equivalent temperature is...\n");
		conv_temperature(cnvval / ELECTRON_VOLT * 11604, "K", MODE_CHAINED);
	}
	return ret;
}
#undef ELECTRON_VOLT
#undef WATT_HOUR
#undef CALORIE_IT
#undef CALORIE_TH
#undef BTU_IT
#undef BTU_59F
#undef FOOT_LBF
