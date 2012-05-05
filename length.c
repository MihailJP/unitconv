#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

#define LIGHT_SECOND 2.99792458e8
#define FOOT 3.048e-1
#define US_SURVEY_FOOT (1200.0/3937.0)
#define CHINESE_FOOT (1.0/3.0)
#define HK_FOOT 3.71475e-1
#define JAPANESE_FOOT (10.0/33.0)
int conv_length(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* Metric */
		{"fm", 1e-15, 0, {"femtometer","femtometre","fermi",""}},
		{"pm", 1e-12, 0, {"picometer","picometre","stigma","bicron",""}},
		{"nm", 1e-9, 0, {"nanometer","nanometre",""}},
		{"um", 1e-6, 0, {"micrometer","micrometre","micron",""}},
		{"mm", 1e-3, 0, {"millimeter","millimetre",""}},
		{"cm", 1e-2, 0, {"centimeter","centimetre",""}},
		{"dm", 1e-1, 0, {"decimeter","decimetre",""}},
		{"m", 1e0, 0, {"meter","metre",""}},
		{"km", 1e3, 0, {"kilometer","kilometre",""}},
		{"Mm", 1e6, 0, {"megameter","megametre",""}},
		{"Gm", 1e9, 0, {"gigameter","gigametre",""}},
		{"Tm", 1e12, 0, {"terameter","terametre","spat",""}},
		/* Miscellaneous */
		{"l_p", 1.61624e-35, 0, {"plancklength","planck length","Planck length",""}},
		{"a_0", 5.291772083e-11, 0, {"bohr","bohrradius","bohr radius","Bohr radius","au",""}},
		{"angstrom", 1e-10, 0, {""}},
		{"pc", 3.08567782e16, 0, {"parsec",""}},
		{"AU", 1.49597870691e11, 0, {"astronomicalunit","astronomical unit",""}},
		{"l.ns.", LIGHT_SECOND / 1e9, 0, {"light-nanosecond","lightnanosecond",""}},
		{"l.us.", LIGHT_SECOND / 1e6, 0, {"light-microsecond","lightmicrosecond",""}},
		{"l.ms.", LIGHT_SECOND / 1e3, 0, {"light-millisecond","lightmillisecond",""}},
		{"l.s.", LIGHT_SECOND, 0, {"light-second","lightsecond",""}},
		{"l.m.", LIGHT_SECOND * 60, 0, {"light-minute","lightminute",""}},
		{"l.h.", LIGHT_SECOND * 3600, 0, {"light-hour","lighthour",""}},
		{"l.d.", LIGHT_SECOND * 86400, 0, {"light-day","lightday",""}},
		{"l.y.", LIGHT_SECOND * 86400 * 365.25, 0, {"ly","light-year","lightyear",""}},
		{"cable", 185.2, 0, {""}},
		{"NM", 1852, 0, {"nmi","nauticalmile","nautical mile",""}},
		{"NL", 1852*3, 0, {"nl","nauticalleague","nautical league",""}},
		{"lieue", 4000, 0, {""}},
		/* US Customary-Imperial */
		{"mil", FOOT / 12 / 1e3, 0, {"thou",""}},
		{"ln", FOOT / 144, 0, {"line",""}},
		{"barleycorn", FOOT / 36, 0, {""}},
		{"finger", FOOT / 12 * .875, 0, {""}},
		{"in", FOOT / 12, 0, {"inch",""}},
		{"stick", FOOT / 6, 0, {""}},
		{"palm", FOOT / 4, 0, {""}},
		{"hand", FOOT / 3, 0, {""}},
		{"finger(cloth)", FOOT / 12 * 4.5, 0, {""}},
		{"span", FOOT / 2, 0, {""}},
		{"lnk", FOOT * .66, 0, {"link",""}},
		{"span", FOOT / 12 * 9, 0, {"",""}},
		{"ft", FOOT, 0, {"foot","lnk(Ramsden)","link(Ramsden)",""}},
		{"cubit", FOOT * 1.5, 0, {""}},
		{"pace", FOOT * 2.5, 0, {""}},
		{"yd", FOOT * 3, 0, {"yard",""}},
		{"ell", FOOT * 3.75, 0, {""}},
		{"fathom", FOOT * 6, 0, {"fm",""}},
		{"rd", FOOT * 16.5, 0, {"rod","pole","perch",""}},
		{"rope", FOOT * 20, 0, {""}},
		{"ch", FOOT * 66, 0, {"chain",""}},
		{"ch(Ramsden)", FOOT * 100, 0, {"chain(Ramsden)",""}},
		{"cable(UK)", FOOT * 608, 0, {"cable(imperial)",""}},
		{"fur", FOOT * 660, 0, {"furlong",""}},
		{"cable(US)", FOOT * 720, 0, {""}},
		{"mi", FOOT * 5280, 0, {"mile",""}},
		{"mi(tactical)", FOOT * 6000, 0, {"mile(tactical)","tacticalmile","tactical mile",""}},
		{"NM(Adm)", FOOT * 6080, 0, {"nmi(Adm)",""}},
		{"mi(geographical)", FOOT * 6082, 0, {"mi(Geo)","mi(geo)","mile(Geo)","mile(geo)","mile(geographical)","geographicalmile","geographical mile",""}},
		{"mi(telegraph)", FOOT * 6087, 0, {"mile(telegraph)","telegraphmile","telegraph mile",""}},
		{"lea", FOOT * 5280 * 3, 0, {"league",""}},
		{"ft(US)", US_SURVEY_FOOT, 0, {"foot(US)",""}},
		{"ch(US)", US_SURVEY_FOOT * 66, 0, {"chain(US)",""}},
		{"mi(US)", US_SURVEY_FOOT * 5280, 0, {"mile(US)",""}},
		{"ft(Ben)", 3.04799735e-1, 0, {"foot(Ben)",""}},
		{"ft(Cla)", 3.047972654e-1, 0, {"foot(Cla)",""}},
		{"ft(Ind)", 3.04799514e-1, 0, {"foot(Ind)",""}},
		{"ft(Sear)", 3.0479947e-1, 0, {"foot(Sear)",""}},
		/* Chinese */
		{"hu1", CHINESE_FOOT / 1e5, 0, {"hu",""}},
		{"si1", CHINESE_FOOT / 1e4, 0, {"si",""}},
		{"hao2", CHINESE_FOOT / 1e3, 0, {"hao",""}},
		{"li2", CHINESE_FOOT / 100, 0, {"li",""}},
		{"fen1", CHINESE_FOOT / 10, 0, {"fen","chineseinch","Chinese inch","chinese inch",""}},
		{"chi1", CHINESE_FOOT, 0, {"chi","chinesefoot","Chinese foot","chinese foot",""}},
		{"bu4", CHINESE_FOOT * 5, 0, {"bu","chinesepace","Chinese pace","chinese pace",""}},
		{"zhang4", CHINESE_FOOT * 10, 0, {"zhang",""}},
		{"yin3", CHINESE_FOOT * 100, 0, {"yin",""}},
		{"li3", 500, 0, {"li",""}},
		/* Hong Kong */
		{"fen(HK)", HK_FOOT / 100, 0, {"fen",""}},
		{"tsun", HK_FOOT / 10, 0, {"hongkonginch","hkinch","HKinch","hk inch","HK inch","Hong Kong inch",""}},
		{"chek", HK_FOOT, 0, {"hongkongfoot","hkfoot","HKfoot","hk foot","HK foot","Hong Kong foot",""}},
		/* Japanese-Taiwanese */
		{"moh", JAPANESE_FOOT / 100, 0, {"mou","mo",""}},
		{"rin", JAPANESE_FOOT / 100, 0, {""}},
		{"bu(JP)", JAPANESE_FOOT / 100, 0, {"bu",""}},
		{"sun", JAPANESE_FOOT / 10, 0, {"japaneseinch","japanese inch","Japanese inch",""}},
		{"shaku", JAPANESE_FOOT, 0, {"japanesefoot","japanese foot","Japanese foot","kanejaku",""}},
		{"ken", JAPANESE_FOOT * 6, 0, {"hiro","edoma","japanesefathom","japanese fathom","Japanese fathom",""}},
		{"ken(Kyoto)", JAPANESE_FOOT * 6.5, 0, {"kyoma","kyouma","kyohma",""}},
		{"joh", JAPANESE_FOOT * 10, 0, {"jo","jou",""}},
		{"choh", JAPANESE_FOOT * 360, 0, {"cho","chou",""}},
		{"ri", JAPANESE_FOOT * 36 * 360, 0, {""}},
		{"sun(kujirajaku)", 2.5/66.0, 0, {""}},
		{"shaku(kujirajaku)", 25.0/66.0, 0, {"kujirajaku",""}},
		/* Special */
		{"pt(US)", FOOT / 12 / 72.272, 0, {"point(US)",""}},
		{"pt(Didot)", 5e-2 / 133.0, 0, {"point(Didot)",""}},
		{"pt(ps)", FOOT / 12 / 72, 0, {"pt(postscript)","pt(PostScript)","point(ps)","point(postscript)","point(PostScript)",""}},
		{"pt(TeX)", FOOT / 12 / 72.27, 0, {"point(TeX)",""}},
		{"pica(US)", FOOT / 72.272, 0, {""}},
		{"pica(Didot)", 5e-2 / 133.0 * 12, 0, {""}},
		{"pica(ps)", FOOT / 72, 0, {"pica(postscript)","pica(PostScript)",""}},
		{"pica(TeX)", FOOT / 72.27, 0, {""}},
		{"twp", FOOT / 12 / 1440, 0, {"twip",""}},
		{"xu", 1.0021e-13, 0, {"xunit","x unit","siegbahn",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "length", &cnvval);
	return ret;
}
#undef LIGHT_SECOND
#undef FOOT
#undef CHINESE_FOOT
#undef HK_FOOT
#undef JAPANESE_FOOT
