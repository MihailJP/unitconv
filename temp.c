#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_temperature(double val, char *unitname)
{
	int i;
	unit unitlist[] = {
		{"K", 1, 0, {"kelvin","Kelvin",""}}, /* SI */
		{"deg C", 1, 273.15, {"degc","degC","Celsius","centigrade",""}}, /* metric */
		{"deg F", 1.0/1.8, 459.67, {"degf","degF","Fahrenheit",""}}, /* imperial */
		{"deg R", 1.0/1.8, 0, {"degr","degR","Rankine",""}},
		{"deg D", -2.0/3.0, -559.725, {"degd","degD","Delisle",""}},
		{"deg N", 100.0/33.0, 90.1395, {"degn","degN","Newton",""}},
		{"deg Re", 1.25, 218.52, {"degre","degRe","Reaumur",""}}, 
		{"deg Ro", 40.0/21.0, 135.90375, {"degro","degRo","Romer","Roemer",""}}, 
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	return calculate(val, unitname, listlen, unitlist);
}
