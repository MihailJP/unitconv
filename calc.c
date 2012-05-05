#include <string.h>
#include <stdio.h>
#include "unitconv.h"
#include "calc.h"

int calculate(double val, char *unitname, unsigned int listlen, unit unitlist[])
{
	int i, j, conversionfound;
	int retval = RET_UNKNOWN_UNIT;
	
	for (i = 0; i < listlen; i++) {
		conversionfound = 0;
		if (!(strcmp(unitname, unitlist[i].name))) {
			printf("%g %s is equivalent to...\n", val, unitname);
			conversionfound = 1;
		} else {
			j = 0;
			while (strcmp(unitlist[i].alias[j], "")) {
				if (!(strcmp(unitname, unitlist[i].alias[j]))) {
					printf("%g %s is equivalent to...\n", val, unitname);
					conversionfound = 1;
				}
				j++;
			}
		}
		if (conversionfound) {
			for (j = 0; j < listlen; j++) {
				printf("... %g %s\n", val * unitlist[i].tr / unitlist[j].tr, unitlist[j].name);
			}
			printf("\n");
			retval = ((retval == RET_UNKNOWN_UNIT) ? RET_OK : RET_AMBIGUOUS_UNIT);
		}
	}
	
	return retval;
}
