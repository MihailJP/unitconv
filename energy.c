#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

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
		{"meV", ELECTRONVOLT_TO_JOULE * 1e-3, 0, {"millielectronvolt",""}},
		{"eV", ELECTRONVOLT_TO_JOULE, 0, {"electronvolt","electron volt",""}},
		{"keV", ELECTRONVOLT_TO_JOULE * 1e3, 0, {"kiloelectronvolt",""}},
		{"MeV", ELECTRONVOLT_TO_JOULE * 1e6, 0, {"megaelectronvolt",""}},
		{"GeV", ELECTRONVOLT_TO_JOULE * 1e9, 0, {"gigaelectronvolt",""}},
		{"TeV", ELECTRONVOLT_TO_JOULE * 1e12, 0, {"teraelectronvolt",""}},
		/* watthour */
		{"Wh", WATTHOUR_TO_JOULE, 0, {"W*h","W h","watthour","watt-hour",""}},
		{"kWh", WATTHOUR_TO_JOULE * 1e3, 0, {"kW*h","kW h","kilowatthour","kilowatt-hour","BOTU","B.O.T.U","B.O.T.U.",""}},
		{"MWh", WATTHOUR_TO_JOULE * 1e6, 0, {"MW*h","MW h","megawatthour","megawatt-hour",""}},
		{"GWh", WATTHOUR_TO_JOULE * 1e9, 0, {"GW*h","GW h","gigawatthour","gigawatt-hour",""}},
		{"TWh", WATTHOUR_TO_JOULE * 1e12, 0, {"TW*h","TW h","terawatthour","terawatt-hour",""}},
		/* calorie */
		{"cal", CALORIE_IT_TO_JOULE, 0, {"cal_IT","cal(IT)","calorie",""}},
		{"kcal", CALORIE_IT_TO_JOULE * 1e3, 0, {"kcal_IT","kcal(IT)","Cal","kilocalorie",""}},
		{"Mcal", CALORIE_IT_TO_JOULE * 1e6, 0, {"Mcal_IT","Mcal(IT)","megacalorie","thermie",""}},
		{"cal_th", CALORIE_TH_TO_JOULE, 0, {"cal(th)","calorie(th)",""}},
		{"cal_15degC", 4.1855, 0, {"cal(15degC)","calorie(15degC)",""}},
		{"tTNT", CALORIE_TH_TO_JOULE * 1e9, 0, {"tontnt","tonoftnt","ton of tnt","ton of TNT",""}},
		{"TCE", CALORIE_TH_TO_JOULE * 7e9, 0, {"toncoal","tonofcoal","ton of coal","tonofcoaleqv","tonofcoalequiv","tonofcoalequivalent","ton of coal equivalent",""}},
		{"TOE", CALORIE_TH_TO_JOULE * 10e9, 0, {"tonoil","tonofoil","ton of oil","tonofoileqv","tonofoilequiv","tonofoilequivalent","ton of oil equivalent",""}},
		/* Miscellaneous */
		{"gf m", 1.0 * GRAVACC * 1e-3, 0, {"gf*m","gfm","gramforcemeter","grammeforcemetre","gramforce meter","grammeforce metre","gramforce-meter","grammeforce-metre","gram-force meter","gramme-force metre","gram-force-meter","gramme-force-metre",""}},
		{"kgf m", 1.0 * GRAVACC, 0, {"kgf*m","kgfm","kilogramforcemeter","kilogrammeforcemetre","kilogramforce meter","kilogrammeforce metre","kilogramforce-meter","kilogrammeforce-metre","kilogram-force meter","kilogramme-force metre","kilogram-force-meter","kilogramme-force-metre",""}},
		{"erg", 1e-7, 0, {""}},
		{"CHU", 1.899100534716e3, 0, {""}},
		{"cc atm", ATMOSPHERE * 1e-6, 0, {"ccatm","scc",""}},
		{"l atm", ATMOSPHERE * 1e-3, 0, {"latm","litreatmosphere","literatmosphere","litre-atmosphere","liter-atmosphere","sl",""}},
		{"foe", 1e44, 0, {""}},
		{"Ry", RYDBERG_TO_JOULE, 0, {"rydberg",""}},
		/* Atomic unit */
		{"E_h", HARTREE_TO_JOULE, 0, {"hartree","au","auenergy","au(energy)","atomicenergy","atomicunitenergy","atomicunitofenergy","atomic unit of energy",""}},
		/* Planck unit */
		{"E_p", PLANCK_ENERGY, 0, {"planckenergy","planck energy","Planck energy",""}},
		/* British thermal unit */
		{"BTU", 1.0545e3, 0, {"BTU_ISO","BTU(ISO)","Btu_ISO","Btu(ISO)",""}},
		{"BTU_IT_TO_JOULE", BTU_IT_TO_JOULE, 0, {"BTU(IT)","Btu_IT","Btu(IT)",""}},
		{"BTU_th", 1.05435026444e3, 0, {"BTU(th)","Btu_th","Btu(th)",""}},
		{"BTU_59degF", BTU_59F_TO_JOULE, 0, {"BTU(59degF)","BTU_15degC","BTU(15degC)","Btu_59degF","Btu(59degF)","Btu_15degC","Btu(15degC)",""}},
		{"th", BTU_IT_TO_JOULE * 1e5, 0, {"therm",""}},
		{"th(US)", BTU_59F_TO_JOULE * 1e5, 0, {"therm(US)",""}},
		{"quad", BTU_IT_TO_JOULE * 1e15, 0, {""}},
		{"bboe", 6.12e9, 0, {"barreloil","barrelofoil","barrel of oil","barrelofoileqv","barrelofoilequiv","barrelofoilequivalent","barrel of oil equivalent",""}},
		/* Imperial */
		{"in lbf", FOOTLBF_TO_JOULE / 12, 0, {"in*lbf","inlbf","inchpoundforce","inch-poundforce","inch-pound force",""}},
		{"ft lbf", FOOTLBF_TO_JOULE, 0, {"ft*lbf","ftlbf","footpoundforce","foot-poundforce","foot-pound force",""}},
		{"ft pdl", FOOTLBF_TO_JOULE * POUNDAL_TO_NEWTON, 0, {"ft*pdl","ftpdl","footpoundal","foot-poundal",""}},
		{"hp h", HORSEPOWER_TO_JOULE * HOUR_TO_SECOND, 0, {"hp*h","hph","horsepowerhour","horsepower-hour",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "energy", &cnvval);
	if ((!(chainflag&MODE_CHAINED))&&(ret != RET_UNKNOWN_UNIT)) {
		printf("And equivalent mass is...\n");
		conv_mass(cnvval / ELECTRONVOLT_TO_JOULE * KILOGRAM_TO_ELECTRONVOLT, "kg", MODE_CHAINED);
		printf("And equivalent temperature is...\n");
		conv_temperature(cnvval / ELECTRONVOLT_TO_JOULE * 11604, "K", MODE_CHAINED);
	}
	return ret;
}
