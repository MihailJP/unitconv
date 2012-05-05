#ifndef UNITCONV_H
#define UNITCONV_H

#define RET_OK 0
#define RET_AMBIGUOUS_UNIT 1
#define RET_NOT_ENOUGH_PARAM 2
#define RET_UNKNOWN_UNIT 3

#define BUF_UNITNAME 40
#define BUF_ALIASLIST 20

typedef struct {
	char name[BUF_UNITNAME];
	double tr;
	double zeroadj;
	char alias[BUF_ALIASLIST][BUF_UNITNAME];
} unit;

#endif /* UNITCONV_H */
