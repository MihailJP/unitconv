#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_time(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI */
		{"ns", 1e-9, 0, {"nanosecond",""}},
		{"us", 1e-6, 0, {"microsecond","sigma",""}},
		{"ms", 1e-3, 0, {"millisecond",""}},
		{"cs", 1e-2, 0, {"centisecond","ja","jiffy",""}},
		{"s", 1, 0, {"second",""}},
		{"ks", 1e3, 0, {"kilosecond",""}},
		/* Miscellaneous */
		{"min", MINUTE_TO_SECOND, 0, {"minute",""}},
		{"h", HOUR_TO_SECOND, 0, {"hour",""}},
		{"decimal second", DAY_TO_SECOND * 1e-5, 0, {"decimalsecond",""}},
		{"md", DAY_TO_SECOND * 1e-3, 0, {"milliday","decimalminute","decimal minute",""}},
		{"cd", DAY_TO_SECOND * 1e-2, 0, {"centiday","ke",""}},
		{"dd", DAY_TO_SECOND * 1e-1, 0, {"deciday","decimalhour","decimal hour",""}},
		{"d", DAY_TO_SECOND, 0, {"day",""}},
		{"wk", DAY_TO_SECOND * 7, 0, {"week",""}},
		{"fn", DAY_TO_SECOND * 14, 0, {"fortnight",""}},
		{"d(sidereal)", 86164.1, 0, {"day(sidereal)","siderealday","sidereal day",""}},
		{"mo(full)", MONTH_FL_TO_SECOND, 0, {"mo","month","month(full)","fullmonth","full month",""}},
		{"mo(hollow)", MONTH_HOL_TO_SECOND, 0, {"mo","month","month(hollow)","hollowmonth","hollow month",""}},
		{"mo(Gregorian)", YEAR_GR_TO_SECOND / 12, 0, {"mo","month","month(Gregorian)","gregorianmonth","Gregorianmonth","Gregorian month",""}},
		{"mo(synodic)", MONTH_SYN_TO_SECOND, 0, {"mo","month","month(synodic)","synodicmonth","synodic month",""}},
		{"a(Julian)", YEAR_TO_SECOND, 0, {"y(Julian)","yr(Julian)","a","y","yr","year","year(Julian)","julianyear","julian year","Julian year",""}},
		{"a(Gregorian)", YEAR_GR_TO_SECOND, 0, {"y(Gregorian)","yr(Gregorian)","a","y","yr","year","year(Gregorian)","gregorianyear","gregorian year","Gregorian year",""}},
		{"a(vague)", YEAR_VAGUE_TO_SECOND, 0, {"y(vague)","yr(vague)","a","y","yr","year","year(vague)","vagueyear","vague year",""}},
		{"a(sidereal)", YEAR_SID_TO_SECOND, 0, {"y(sidereal)","yr(sidereal)","a","y","yr","year","year(sidereal)","siderealyear","sidereal year",""}},
		{"a(tropical)", YEAR_TROP_TO_SECOND, 0, {"y(tropical)","yr(tropical)","a","y","yr","year","year(tropical)","tropicalyear","tropical year",""}},
		{"dec(Julian)", YEAR_TO_SECOND * 10, 0, {"dec","decade","decade(Julian)","juliandecade","julian decade","Julian decade",""}},
		{"dec(Gregorian)", YEAR_GR_TO_SECOND * 10, 0, {"dec","decade","decade(Gregorian)","gregoriandecade","gregorian decade","Gregorian decade",""}},
		{"dec(vague)", YEAR_VAGUE_TO_SECOND * 10, 0, {"dec","decade","decade(vague)","vaguedecade","vague decade",""}},
		{"dec(sidereal)", YEAR_SID_TO_SECOND * 10, 0, {"dec","decade","decade(sidereal)","siderealdecade","sidereal decade",""}},
		{"dec(tropical)", YEAR_TROP_TO_SECOND * 10, 0, {"dec","decade","decade(tropical)","tropicaldecade","tropical decade",""}},
		{"c(Julian)", YEAR_TO_SECOND * 100, 0, {"c","century","century(Julian)","juliancentury","julian century","Julian century",""}},
		{"c(Gregorian)", YEAR_GR_TO_SECOND * 100, 0, {"c","century","century(Gregorian)","gregoriancentury","gregorian century","Gregorian century",""}},
		{"c(vague)", YEAR_VAGUE_TO_SECOND * 100, 0, {"c","century","century(vague)","vaguecentury","vague century",""}},
		{"c(sidereal)", YEAR_SID_TO_SECOND * 100, 0, {"c","century","century(sidereal)","siderealcentury","sidereal century",""}},
		{"c(tropical)", YEAR_TROP_TO_SECOND * 100, 0, {"c","century","century(tropical)","tropicalcentury","tropical century",""}},
		{"millennium(Julian)", YEAR_TO_SECOND * 1000, 0, {"millennium","julianmillennium","julian millennium","Julian millennium",""}},
		{"millennium(Gregorian)", YEAR_GR_TO_SECOND * 1000, 0, {"millennium","gregorianmillennium","gregorian millennium","Gregorian millennium",""}},
		{"millennium(vague)", YEAR_VAGUE_TO_SECOND * 1000, 0, {"millennium","vaguemillennium","vague millennium",""}},
		{"millennium(sidereal)", YEAR_SID_TO_SECOND * 1000, 0, {"millennium","siderealmillennium","sidereal millennium",""}},
		{"millennium(tropical)", YEAR_TROP_TO_SECOND * 1000, 0, {"millennium","tropicalmillennium","tropical millennium",""}},
		{"S", 1e-13, 0, {"svedberg",""}},
		{"shake", 1e-8, 0, {""}},
		{"j", 1.0/60.0, 0, {"jiffy",""}},
		{"helek", HOUR_TO_SECOND / 1080.0, 0, {""}},
		{"moment", 90.0, 0, {""}},
		{"ke", HOUR_TO_SECOND / 4, 0, {""}},
		{"lustre", YEAR_VAGUE_TO_SECOND * 5, 0, {"lustrum",""}},
		{"octaeteris", YEAR_TO_SECOND * 8, 0, {"lustrum",""}},
		/* Astronomical */
		{"Metonic cycle", DAY_TO_SECOND * 6940, 0, {"metonic","Metonic","metoniccycle","metonic cycle","enneadecaeteris",""}},
		{"Callipic cycle", YEAR_TO_SECOND * 76, 0, {"callipic","Callipic","callipiccycle","callipic cycle",""}},
		{"Hipparchic cycle", YEAR_TO_SECOND * 76 * 4 - DAY_TO_SECOND, 0, {"hipparchic","Hipparchic","hipparchiccycle","hipparchic cycle",""}},
		{"Sothic cycle", YEAR_VAGUE_TO_SECOND * 1461, 0, {"sothic","Sothic","sothiccycle","sothic cycle",""}},
		/* Atomic unit */
		{"au", BOHR_RADIUS / FINE_STRUCT / LIGHTSPEED, 0, {"autime","au(time)","atomictime","atomicunittime","atomicunitoftime","atomic unit of time",""}},
		/* Planck unit */
		{"t_p", PLANCK_TIME, 0, {"plancktime","planck time","Planck time",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "time", &cnvval);
	return ret;
}
