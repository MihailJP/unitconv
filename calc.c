#include <string.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "unitconv.h"
#include "calc.h"

int calculate(double val, char *unitname, unsigned int listlen, unit unitlist[], unsigned int chainflag, char *category, double *cnvval)
{
	int i, j, conversionfound;
	int retval = RET_UNKNOWN_UNIT;
	double converted;
	
	for (i = 0; i < listlen; i++) {
		conversionfound = 0;
		if (!(strcmp(unitname, unitlist[i].name))) {
			if (!(chainflag&MODE_CHAINED)) printf("'%s' is a unit of %s.\n%g %s is equivalent to...\n", unitname, category, val, unitlist[i].name);
			conversionfound = 1;
		} else {
			j = 0;
			while (strcmp(unitlist[i].alias[j], "")) {
				if (!(strcmp(unitname, unitlist[i].alias[j]))) {
					if (!(chainflag&MODE_CHAINED)) printf("'%s' is a unit of %s, and is an alias of '%s'.\n%g %s is equivalent to...\n", unitname, category, unitlist[i].name, val, unitlist[i].name);
					conversionfound = 1;
				}
				j++;
			}
		}
		if (conversionfound) {
			*cnvval = (val + unitlist[i].zeroadj) * unitlist[i].tr;
			for (j = 0; j < listlen; j++) {
				converted = (*cnvval) / unitlist[j].tr - unitlist[j].zeroadj;
				if ((fabs(converted) < DBL_EPSILON)&&((unitlist[i].zeroadj != 0)||(unitlist[j].zeroadj != 0))) converted = 0;
				printf("... %g %s\n", converted, unitlist[j].name);
			}
			printf("\n");
			retval = ((retval == RET_UNKNOWN_UNIT) ? RET_OK : RET_AMBIGUOUS_UNIT);
		}
	}
	
	return retval;
}
