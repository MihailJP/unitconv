#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

#define SQUARE_FOOT 9.290304e-2
#define SQUARE_US_SURVEY_FOOT (1200.0/3937.0*1200.0/3937.0)
#define CHINESE_MU (2000.0/3.0)
#define CHINESE_SQUARE_FEET (1.0/9.0)
#define JAPANESE_TSUBO (60.0/33.0*60.0/33.0)

int conv_area(double val, char *unitname)
{
	int i;
	unit unitlist[] = {
		/* Metric */
		{"mm^2", 1e-6, {"mm2","squaremillimeter","squaremillimetre","square millimeter","square millimetre","millimetersquared","millimetresquared","millimeter squared","millimetre squared",""}},
		{"cm^2", 1e-4, {"cm2","squarecentimeter","squarecentimetre","square centimeter","square centimetre","centimetersquared","centimetresquared","centimeter squared","centimetre squared",""}},
		{"m^2", 1e0, {"m2","squaremeter","squaremetre","square meter","square metre","metersquared","metresquared","meter squared","metre squared",""}},
		{"dam^2", 1e2, {"dam2","squaredecameter","squaredecametre","square decameter","square decametre","decametersquared","decametresquared","decameter squared","decametre squared","a","are",""}},
		{"hm^2", 1e4, {"hm2","squarehectometer","squarehectometre","square hectometer","square hectometre","hectometersquared","hectometresquared","hectometer squared","hectometre squared","ha","hectare",""}},
		{"km^2", 1e6, {"km2","squarekilometer","squarekilometre","square kilometer","square kilometre","kilometersquared","kilometresquared","kilometer squared","kilometre squared",""}},
		{"Mm^2", 1e12, {"Mm2","squaremegameter","squaremegametre","square megameter","square megametre","megametersquared","megametresquared","megameter squared","megametre squared",""}},
		/* Miscellaneous */
		{"shed", 1e-52, {""}},
		{"b", 1e-28, {"barn",""}},
		{"stremma", 1e3, {"dunam","dunum","donum",""}},
		{"l^2_p", 1.61624e-35 * 1.61624e-35, {"l2_p","planckarea","planck area","Planck area",""}},
		/* US Customary-Imperial */
		{"sq in", SQUARE_FOOT / 12 / 12, {"sqin","in^2","in2","squareinch","square inch", "inchsquared","inch squared",""}},
		{"bd", SQUARE_FOOT / 12, {"board",""}},
		{"sq lnk", SQUARE_FOOT * .66 * .66, {"sqlnk","lnk^2","lnk2","squarelink","square link", "linksquared","link squared",""}},
		{"sq ft", SQUARE_FOOT, {"sqft","ft^2","ft2","squarefoot","square foot", "footsquared","foot squared",""}},
		{"sq yd", SQUARE_FOOT * 3 * 3, {"sqyd","yd^2","yd2","squareyard","square yard", "yardsquared","yard squared",""}},
		{"cord", SQUARE_FOOT / 12 * 192, {""}},
		{"sq rd", SQUARE_FOOT * 16.5 * 16.5, {"sqrd","rd^2","rd2","squarerod","square rod", "rodsquared","rod squared","squarepole","square pole", "polesquared","pole squared","squareperch","square perch", "perchsquared","perch squared",""}},
		{"guntha", SQUARE_FOOT * 3 * 3 * 121, {""}},
		{"sq ch", SQUARE_FOOT * 66 * 66, {"sqch","ch^2","ch2","squarechain","square chain", "chainsquared","chain squared",""}},
		{"ro", SQUARE_FOOT * 660 * 66 / 4, {"rood",""}},
		{"ac", SQUARE_FOOT * 660 * 66, {"acre",""}},
		{"sq fur", SQUARE_FOOT * 660 * 660, {"sqfur","fur^2","fur2","squarefurlong","square furlong", "furlongsquared","furlong squared",""}},
		{"yardland", SQUARE_FOOT * 660 * 66 * 30, {""}},
		{"hide", SQUARE_FOOT * 660 * 66 * 100, {""}},
		{"sq mi", SQUARE_FOOT * 5280 * 5280, {"sqmi","mi^2","mi2","squaremile","square mile", "milesquared","mile squared","section",""}},
		{"barony", SQUARE_FOOT * 660 * 66 * 4000, {""}},
		{"sq lnk(US)", SQUARE_US_SURVEY_FOOT * .66 * .66, {"sqlnk(US)","lnk^2(US)","lnk2(US)","squarelink(US)","square link(US)", "linksquared(US)","link squared(US)", "link(US)squared","link(US) squared",""}},
		{"sq ft(US)", SQUARE_US_SURVEY_FOOT, {"sqft(US)","ft^2(US)","ft2(US)","squarefoot(US)","square foot(US)", "footsquared(US)","foot squared(US)", "foot(US)squared","foot(US) squared",""}},
		{"sq ch(US)", SQUARE_US_SURVEY_FOOT * 66 * 66, {"sqch(US)","ch^2(US)","ch2(US)","squarechain(US)","square chain(US)", "chainsquared(US)","chain squared(US)", "chain(US)squared","chain(US) squared",""}},
		{"ac(US)", SQUARE_US_SURVEY_FOOT * 660 * 66, {"acre(US)",""}},
		{"sq mi(US)", SQUARE_US_SURVEY_FOOT * 5280 * 5280, {"sqmi(US)","mi^2(US)","mi2(US)","squaremile(US)","square mile(US)", "milesquared(US)","mile squared(US)", "mile(US)squared","mile(US) squared",""}},
		{"township", SQUARE_US_SURVEY_FOOT * 5280 * 5280 * 36, {""}},
		/* Chinese */
		{"li2", CHINESE_MU / 100, {"li",""}},
		{"fen1", CHINESE_MU / 10, {"fen",""}},
		{"mu3", CHINESE_MU, {"mu",""}},
		{"shi2", CHINESE_MU * 10, {"shi",""}},
		{"qing3", CHINESE_MU * 100, {"qing",""}},
		{"fang1 cun4", CHINESE_SQUARE_FEET / 100, {"fang1cun4","fang cun","fangcun","cun4^2","cun^2","squarecun","square cun", "cunsquared","cun squared","squarecun4","square cun4", "cun4squared","cun4 squared",""}},
		{"fang1 chi3", CHINESE_SQUARE_FEET, {"fang1chi3","fang chi","fangchi","chi3^2","chi^2","squarechi","square chi", "chisquared","chi squared","squarechi3","square chi3", "chi3squared","chi3 squared",""}},
		{"fang1 zhang4", CHINESE_SQUARE_FEET * 100, {"fang1zhang4","fang zhang","fangzhang","zhang4^2","zhang^2","squarezhang","square zhang", "zhangsquared","zhang squared","squarezhang4","square zhang4", "zhang4squared","zhang4 squared",""}},
		/* Japanese-Taiwanese */
		{"sun^2", JAPANESE_TSUBO / 60 / 60, {"sun2","squaresun","square sun", "sunsquared","sun squared",""}},
		{"shaku", JAPANESE_TSUBO / 100, {""}},
		{"shaku^2", JAPANESE_TSUBO / 6 / 6, {"shaku2","squareshaku","square shaku", "shakusquared","shaku squared",""}},
		{"goh", JAPANESE_TSUBO / 10, {"go","gou",""}},
		{"tsubo", JAPANESE_TSUBO, {"bu",""}},
		{"se", JAPANESE_TSUBO * 30, {""}},
		{"tan", JAPANESE_TSUBO * 300, {""}},
		{"choh", JAPANESE_TSUBO * 3000, {"cho","choh","chohbu","chobu","choubu",""}},
		{"ri^2", JAPANESE_TSUBO * 2160 * 2160, {"ri2","squareri","square ri", "risquared","ri squared",""}},
		{"jia3", JAPANESE_TSUBO * 2934, {"jia","kah",""}},
		{"li2(TW)", JAPANESE_TSUBO * 14670, {"li(TW)","le",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	return calculate(val, unitname, listlen, unitlist);
}

#undef SQUARE_FOOT
#undef SQUARE_US_SURVEY_FOOT
#undef CHINESE_MU
#undef CHINESE_SQUARE_FEET
#undef JAPANESE_TSUBO
