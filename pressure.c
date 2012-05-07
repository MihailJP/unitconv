#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_pressure(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI */
		{"dPa", 1e-1, 0, {"decipascal","Ba","b","barye",""}},
		{"Pa", 1e0, 0, {"pascal",""}},
		{"hPa", 1e2, 0, {"hectopascal","mbar","millibar",""}},
		{"kPa", 1e3, 0, {"kilopascal","pz","pieze",""}},
		{"MPa", 1e6, 0, {"megapascal",""}},
		{"GPa", 1e9, 0, {"gigapascal",""}},
		/* Miscellaneous */
		{"bar", 1e5, 0, {""}}, /* CGS */
		{"atm", ATMOSPHERE, 0, {"atmosphere",""}}, /* CGS */
		{"kgf/mm^2", GRAVACC * 10e6, 0, {"kgf/mm2","kgforcepersqmm","kilogramforcepersqmillimeter","kilogrammeforcepersqmillimetre","kilogramforcepersquaremillimeter","kilogrammeforcepersquaremillimetre","kilogram-force per square millimeter","kilogramme-force per square millimetre",""}},
		{"kgf/cm^2", GRAVACC * 10e4, 0, {"kgf/cm2","kgforcepersqcm","kilogramforcepersqcentimeter","kilogrammeforcepersqcentimetre","kilogramforcepersquarecentimeter","kilogrammeforcepersquarecentimetre","kilogram-force per square centimeter","kilogramme-force per square centimetre","at",""}},
		{"nmHg", MMHG_TO_PASCAL * 1e-6, 0, {"nmhg","nanometermercury","nanometremercury","nanometreofmercury","nanometerofmercury","nanometre of mercury","nanometer of mercury","uTorr","utorr","microtorr",""}},
		{"umHg", MMHG_TO_PASCAL * 1e-3, 0, {"umhg","micrometermercury","micrometremercury","micrometreofmercury","micrometerofmercury","micrometre of mercury","micrometer of mercury","mTorr","mtorr","millitorr",""}},
		{"mmHg", MMHG_TO_PASCAL, 0, {"mmhg","millimetermercury","millimetremercury","millimetreofmercury","millimeterofmercury","millimetre of mercury","millimeter of mercury","Torr","torr",""}},
		{"cmHg", MMHG_TO_PASCAL * 1e1, 0, {"cmhg","centimetermercury","centimetremercury","centimetreofmercury","centimeterofmercury","centimetre of mercury","centimeter of mercury",""}},
		{"mmH2O", MMH2O_TO_PASCAL, 0, {"mmh2o","millimeterwater","millimetrewater","millimetreofwater","millimeterofwater","millimetre of water","millimeter of water",""}},
		{"cmH2O", MMH2O_TO_PASCAL * 1e1, 0, {"cmh2o","centimeterwater","centimetrewater","centimetreofwater","centimeterofwater","centimetre of water","centimeter of water",""}},
		/* Planck unit */
		{"p_p", PLANCK_PRESSURE, 0, {"planckpressure","planck pressure","Planck pressure",""}},
		/* Imperial */
		{"inHg", FTHG_TO_PASCAL / 12, 0, {"inhg","inchmercury","inchofmercury","inch of mercury",""}},
		{"ftHg", FTHG_TO_PASCAL, 0, {"fthg","footmercury","footofmercury","foot of mercury",""}},
		{"inH2O", FTH2O_TO_PASCAL / 12, 0, {"inh2o","inchwater","inchofwater","inch of water",""}},
		{"ftH2O", FTH2O_TO_PASCAL, 0, {"fth2o","footwater","footofwater","foot of water",""}},
		//{"ozf", OZF_TO_NEWTON, 0, {"ounceforce","ounce-force",""}},
		{"psi", LBF_PER_SQIN_TO_PASCAL, 0, {"lbf/in^2","lbf/in2","poundforcepersqinch","poundforcepersquareinch","pound-force per square inch",""}},
		{"ksi", LBF_PER_SQIN_TO_PASCAL * 1e3, 0, {"kipf/in^2","kipf/in2","kipforcepersqinch","kipforcepersquareinch","kip-force per square inch",""}},
		{"psf", LBF_PER_SQFT_TO_PASCAL, 0, {"lbf/ft^2","lbf/ft2","poundforcepersqfoot","poundforcepersquarefoot","pound-force per square foot",""}},
		{"kipf/ft^2", LBF_PER_SQFT_TO_PASCAL * 1e3, 0, {"kipf/ft2","kipforcepersqfoot","kipforcepersquarefoot","kip-force per square foot",""}},
		{"tnf/ft^2", LBF_PER_SQFT_TO_PASCAL * 2e3, 0, {"tnf/ft2","tonforcepersqfoot","tonforcepersquarefoot","ton-force per square foot",""}},
		{"pdl/ft^2", PDL_PER_SQFT_TO_PASCAL, 0, {"pdl/ft2","poundalpersqfoot","poundalpersquarefoot","poundal per square foot",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "pressure", &cnvval);
	return ret;
}
