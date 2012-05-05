/* Commandline unit conversion tool */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "unitconv.h"
#include "unitdata.h"

#define mark_checked stat = ((stat == RET_UNKNOWN_UNIT) ? RET_OK : RET_AMBIGUOUS_UNIT)

int main(int argc, char *argv[])
{
	double val; char *unitname; int param, stat;

	if (argc < 3) {
		fprintf(stderr, "Not enough parameter.\nUsage: %s value unit\n", argv[0]);
		return RET_NOT_ENOUGH_PARAM;
	} else {
		val = atof(argv[1]);
		unitname = argv[2];
		stat = RET_UNKNOWN_UNIT;
		
		if (conv_length(val, unitname) != RET_UNKNOWN_UNIT) mark_checked;
		
		if (stat == RET_UNKNOWN_UNIT) fprintf(stderr, "Unknown unit: %s\n", unitname);
		return stat;
	}
}

#undef mark_checked
