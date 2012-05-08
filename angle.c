#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

/*
 * For calculation convenience, unlike other genres,
 * angles are held by degrees which itself is not an SI unit.
 */
int conv_angle(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI, scientific use */
		{"urad", RADIAN_TO_DEGREE * 1e-6, 0, {"microradian",""}},
		{"mrad", RADIAN_TO_DEGREE * 1e-3, 0, {"milliradian",""}},
		{"rad", RADIAN_TO_DEGREE, 0, {"radian",""}},
		/* Degrees, everyday use */
		{"deg", 1, 0, {"degree",""}},
		{"'", 1.0 / 60.0, 0, {"^I","I","arcminute","moa","MOA",""}},
		{"\"", 1.0 / 3600.0, 0, {"''","^II","II","arcsecond",""}},
		{"'''", 1.0 / 3600.0 / 60.0, 0, {"^III","III","third",""}},
		{"''''", 1.0 / 3600.0 / 3600.0, 0, {"^IV","IV","fourth",""}},
		/* Gradian, revolution-age France */
		{"grad", .9, 0, {"^g","grade","gon","gradian",""}},
		{"^c", 9e-3, 0, {"^cg","centigrade",""}},
		{"^cc", 9e-5, 0, {"centicentigrade","myriograde",""}},
		/* Miscellaneous */
		{"mil", 180.0 / 6400.0, 0, {""}},
		{"turn", 360, 0, {""}},
		{"quadrant", 90, 0, {""}},
		{"sextant", 60, 0, {""}},
		{"octant", 45, 0, {""}},
		{"sign", 30, 0, {""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "angle", &cnvval);
	return ret;
}
