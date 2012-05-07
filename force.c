#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_force(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* SI */
		{"mN", 1e-3, 0, {"millinewton",""}},
		{"N", 1.0, 0, {"newton",""}},
		{"kN", 1e3, 0, {"kilonewton","sn","sthene",""}}, /* MTS: Sthene is virtually an alias for kilonewton */
		/* Miscellaneous */
		{"dyn", 1e-5, 0, {"dyne",""}}, /* CGS */
		{"gf", GRAVACC * 1e-3, 0, {"gramforce","grammeforce","gram-force","gramme-force",""}},
		{"kgf", GRAVACC, 0, {"kilogramforce","kilogrammeforce","kilogram-force","kilogramme-force","kp","kilopond","graveforce","grave-force",""}},
		{"Mgf", GRAVACC * 1e3, 0, {"megagramforce","megagrammeforce","megagram-force","megagramme-force","",""}},
		/* Atomic unit */
		{"au", HARTREE_TO_JOULE / BOHR_RADIUS, 0, {"auforce","au(force)","atomicforce","atomicunitforce","atomicunitofforce","atomic unit of force",""}},
		/* Planck unit */
		{"F_p", PLANCK_FORCE, 0, {"planckforce","planck force","Planck force",""}},
		/* Imperial */
		{"ozf", OZF_TO_NEWTON, 0, {"ounceforce","ounce-force",""}},
		{"lbf", LBF_TO_NEWTON, 0, {"poundforce","pound-force",""}},
		{"kipf", LBF_TO_NEWTON * 1e3, 0, {"klbf","kipforce","kip-force",""}},
		{"tnf", LBF_TO_NEWTON * 2e3, 0, {"tonforce","ton-force",""}},
		{"pdl", POUNDAL_TO_NEWTON, 0, {"poundal",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "force", &cnvval);
	return ret;
}
