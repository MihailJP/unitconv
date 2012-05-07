#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

int conv_mass(double val, char *unitname, unsigned int chainflag)
{
	int i, ret; double cnvval;
	unit unitlist[] = {
		/* Metric */
		{"ug", 1e-9, 0, {"microgram","microgramme","gamma",""}},
		{"mg", 1e-6, 0, {"milligram","milligramme",""}},
		{"g", 1e-3, 0, {"gram","gramme",""}},
		{"kg", 1, 0, {"kilogram","kilogramme","kilo","grave",""}},
		{"Mg", 1e3, 0, {"megagram","megagramme","tonne",""}},
		/* Miscellaneous */
		{"u", 1.66053873e-27, 0, {"AMU",""}},
		{"Da", 1.66090210e-27, 0, {"dalton",""}},
		{"m_e", ELECTRON_MASS, 0, {""}},
		{"m_p", PLANCK_MASS, 0, {"planckmass","planck mass","Planck mass",""}},
		/* US Customary-Imperial */
		{"mite", GRAIN_TO_KILOGRAM / 20, 0, {""}},
		{"gr", GRAIN_TO_KILOGRAM, 0, {"grain",""}},
		{"sheet", POUND_AV_TO_KILOGRAM / 700, 0, {""}},
		{"dr av", GRAIN_TO_KILOGRAM * 27.34375, 0, {"drav","dr","dram",""}},
		{"oz av", POUND_AV_TO_KILOGRAM / 16, 0, {"ozav","oz","ounce",""}},
		{"lb av", POUND_AV_TO_KILOGRAM, 0, {"lbav","lb","pound",""}},
		{"clove", POUND_AV_TO_KILOGRAM * 8, 0, {""}},
		{"st", POUND_AV_TO_KILOGRAM * 14, 0, {"stone",""}},
		{"sh cwt", POUND_AV_TO_KILOGRAM * 100, 0, {"shcwt","shorthundredweight","short hundredweight",""}},
		{"long cwt", POUND_AV_TO_KILOGRAM * 112, 0, {"longcwt","longhundredweight","long hundredweight","cwt","cental",""}},
		{"wey", POUND_AV_TO_KILOGRAM * 252, 0, {""}},
		{"kip", POUND_AV_TO_KILOGRAM * 1000, 0, {""}},
		{"sh tn", POUND_AV_TO_KILOGRAM * 2000, 0, {"shtn","shortton","short ton",""}},
		{"long tn", POUND_AV_TO_KILOGRAM * 2240, 0, {"longtn","longton","long ton","ton",""}},
		{"barge", POUND_AV_TO_KILOGRAM * 2000 * 22.5, 0, {""}},
		{"s ap", GRAIN_TO_KILOGRAM * 20, 0, {"sap","scruple",""}},
		{"dwt", POUND_TROY_TO_KILOGRAM / 12 / 20, 0, {"pwt","pennyweight",""}},
		{"dr t", GRAIN_TO_KILOGRAM * 60, 0, {"drt","troydram","troy dram","dr ap","drap","apothecarydram","apothecary dram",""}},
		{"oz t", POUND_TROY_TO_KILOGRAM / 12, 0, {"ozt","troyounce","troy ounce","oz ap","ozap","apothecaryounce","apothecary ounce",""}},
		{"mark", POUND_TROY_TO_KILOGRAM / 12 * 8, 0, {""}},
		{"lb t", POUND_TROY_TO_KILOGRAM, 0, {"lbt","troypound","troy pound","troy",""}},
		/* Chinese */
		{"hu1", CATTY_TO_KILOGRAM / 1e7, 0, {"hu",""}},
		{"si1", CATTY_TO_KILOGRAM / 1e6, 0, {"si",""}},
		{"hao2", CATTY_TO_KILOGRAM / 1e5, 0, {"hao",""}},
		{"cash", CATTY_TO_KILOGRAM / 1e4, 0, {"cash(CN)","li2","li",""}},
		{"candareen", CATTY_TO_KILOGRAM / 1e3, 0, {"candareen(CN)","fen1","fen",""}},
		{"mace", CATTY_TO_KILOGRAM / 100, 0, {"mace(CN)","qian2","qian",""}},
		{"tael", CATTY_TO_KILOGRAM / 10, 0, {"tael(CN)","liang3","liang","chineseounce","chinese ounce","Chinese ounce",""}},
		{"catty", CATTY_TO_KILOGRAM, 0, {"catty(CN)","jin1","jin","chinesepound","chinese pound","Chinese pound",""}},
		{"picul", CATTY_TO_KILOGRAM * 100, 0, {"picul(CN)","dan4","dan","chinesehundredweight","chinesecwt","chinese hundredweight","Chinese hundredweight",""}},
		/* Hong Kong */
		{"candareen(HK)", HK_CATTY_TO_KILOGRAM / 1600, 0, {"candareen","fan",""}},
		{"mace(HK)", HK_CATTY_TO_KILOGRAM / 160, 0, {"mace","cin","chin","tsin",""}},
		{"tael(HK)", HK_CATTY_TO_KILOGRAM / 16, 0, {"tael","loeng","leung",""}},
		{"catty(HK)", HK_CATTY_TO_KILOGRAM, 0, {"catty","gan",""}},
		{"picul(HK)", HK_CATTY_TO_KILOGRAM * 100, 0, {"picul","daam",""}},
		/* Japanese-Taiwanese */
		{"fun", JAPANESE_CATTY_TO_KILOGRAM / 1600, 0, {"candareen(JP)","candareen(TW)","fen",""}},
		{"mom", JAPANESE_CATTY_TO_KILOGRAM / 160, 0, {"momme","mace(JP)","mace(TW)","mace","qian",""}},
		{"ryoh", JAPANESE_CATTY_TO_KILOGRAM / 16, 0, {"ryo","ryou","tael(JP)","tael(TW)","tael","liang",""}},
		{"kin", JAPANESE_CATTY_TO_KILOGRAM, 0, {"catty(JP)","catty(TW)","catty","jin",""}},
		{"kan", JAPANESE_CATTY_TO_KILOGRAM * 6.25, 0, {""}},
		{"picul(TW)", JAPANESE_CATTY_TO_KILOGRAM * 100, 0, {"picul","dan",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "mass", &cnvval);
	if ((!(chainflag&MODE_CHAINED))&&(ret != RET_UNKNOWN_UNIT)) {
		printf("And equivalent energy is...\n");
		conv_energy(cnvval / KILOGRAM_TO_ELECTRONVOLT, "eV", MODE_CHAINED);
	}
	return ret;
}
