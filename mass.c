#include <stdio.h>
#include "unitconv.h"
#include "calc.h"
#include "unitdata.h"

#define POUND_AVOIRDUPOIS 4.5359237e-1
#define POUND_TROY (POUND_AVOIRDUPOIS/7000*5760)
#define CHINESE_POUND 5e-1
#define HK_POUND 6.0478982e-1
#define JAPANESE_POUND 6e-1
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
		{"m_e", 9.10938215e-31, 0, {""}},
		{"m_p", 2.17644e-8, 0, {"planckmass","planck mass","Planck mass",""}},
		/* US Customary-Imperial */
		{"mite", POUND_AVOIRDUPOIS / 7000 / 20, 0, {""}},
		{"gr", POUND_AVOIRDUPOIS / 7000, 0, {"grain",""}},
		{"sheet", POUND_AVOIRDUPOIS / 700, 0, {""}},
		{"dr av", POUND_AVOIRDUPOIS / 7000 * 27.34375, 0, {"drav","dr","dram",""}},
		{"oz av", POUND_AVOIRDUPOIS / 16, 0, {"ozav","oz","ounce",""}},
		{"lb av", POUND_AVOIRDUPOIS, 0, {"lbav","lb","pound",""}},
		{"clove", POUND_AVOIRDUPOIS * 8, 0, {""}},
		{"st", POUND_AVOIRDUPOIS * 14, 0, {"stone",""}},
		{"sh cwt", POUND_AVOIRDUPOIS * 100, 0, {"shcwt","shorthundredweight","short hundredweight",""}},
		{"long cwt", POUND_AVOIRDUPOIS * 112, 0, {"longcwt","longhundredweight","long hundredweight","cwt","cental",""}},
		{"wey", POUND_AVOIRDUPOIS * 252, 0, {""}},
		{"kip", POUND_AVOIRDUPOIS * 1000, 0, {""}},
		{"sh tn", POUND_AVOIRDUPOIS * 2000, 0, {"shtn","shortton","short ton",""}},
		{"long tn", POUND_AVOIRDUPOIS * 2240, 0, {"longtn","longton","long ton","ton",""}},
		{"barge", POUND_AVOIRDUPOIS * 2000 * 22.5, 0, {""}},
		{"s ap", POUND_TROY / 7000 * 20, 0, {"sap","scruple",""}},
		{"dwt", POUND_TROY / 12 / 20, 0, {"pwt","pennyweight",""}},
		{"dr t", POUND_TROY / 7000 * 60, 0, {"drt","troydram","troy dram","dr ap","drap","apothecarydram","apothecary dram",""}},
		{"oz t", POUND_TROY / 12, 0, {"ozt","troyounce","troy ounce","oz ap","ozap","apothecaryounce","apothecary ounce",""}},
		{"mark", POUND_TROY / 12 * 8, 0, {""}},
		{"lb t", POUND_TROY, 0, {"lbt","troypound","troy pound","troy",""}},
		/* Chinese */
		{"hu1", CHINESE_POUND / 1e7, 0, {"hu",""}},
		{"si1", CHINESE_POUND / 1e6, 0, {"si",""}},
		{"hao2", CHINESE_POUND / 1e5, 0, {"hao",""}},
		{"cash", CHINESE_POUND / 1e4, 0, {"cash(CN)","li2","li",""}},
		{"candareen", CHINESE_POUND / 1e3, 0, {"candareen(CN)","fen1","fen",""}},
		{"mace", CHINESE_POUND / 100, 0, {"mace(CN)","qian2","qian",""}},
		{"tael", CHINESE_POUND / 10, 0, {"tael(CN)","liang3","liang","chineseounce","chinese ounce","Chinese ounce",""}},
		{"catty", CHINESE_POUND, 0, {"catty(CN)","jin1","jin","chinesepound","chinese pound","Chinese pound",""}},
		{"picul", CHINESE_POUND * 100, 0, {"picul(CN)","dan4","dan","chinesehundredweight","chinesecwt","chinese hundredweight","Chinese hundredweight",""}},
		/* Hong Kong */
		{"candareen(HK)", HK_POUND / 1600, 0, {"candareen","fan",""}},
		{"mace(HK)", HK_POUND / 160, 0, {"mace","cin","chin","tsin",""}},
		{"tael(HK)", HK_POUND / 16, 0, {"tael","loeng","leung",""}},
		{"catty(HK)", HK_POUND, 0, {"catty","gan",""}},
		{"picul(HK)", HK_POUND * 100, 0, {"picul","daam",""}},
		/* Japanese-Taiwanese */
		{"fun", JAPANESE_POUND / 1600, 0, {"candareen(JP)","candareen(TW)","fen",""}},
		{"mom", JAPANESE_POUND / 160, 0, {"momme","mace(JP)","mace(TW)","mace","qian",""}},
		{"ryoh", JAPANESE_POUND / 16, 0, {"ryo","ryou","tael(JP)","tael(TW)","tael","liang",""}},
		{"kin", JAPANESE_POUND, 0, {"catty(JP)","catty(TW)","catty","jin",""}},
		{"kan", JAPANESE_POUND * 6.25, 0, {""}},
		{"picul(TW)", JAPANESE_POUND * 100, 0, {"picul","dan",""}},
	};
	unsigned int listlen = (sizeof(unitlist) / sizeof(unit));
	
	ret = calculate(val, unitname, listlen, unitlist, chainflag, "mass", &cnvval);
	if ((!(chainflag&MODE_CHAINED))&&(ret != RET_UNKNOWN_UNIT)) {
		printf("And equivalent energy is...\n");
		conv_energy(cnvval / 1.782661845e-36, "eV", MODE_CHAINED);
	}
	return ret;
}
#undef POUND_AVOIRDUPOIS
#undef POUND_TROY
#undef CHINESE_POUND
#undef HK_POUND
#undef JAPANESE_POUND
