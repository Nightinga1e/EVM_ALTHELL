#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int C:  10;
	unsigned int H:  4;
	unsigned int S:  6;
} tCHS;

typedef struct {
	unsigned int C:  10;
	unsigned int H:  8;
	unsigned int S:  6;
} tLARGE;

typedef struct {
	unsigned int C:  16;
	unsigned int H:  4;
	unsigned int S:  8;
} tIDECHS;

typedef struct {
	unsigned int A:  8;
	unsigned int B:  8;
	unsigned int C:  8;
} ttLARGE;

typedef struct {unsigned int S:  32;} tLBA;

struct table
{
	char is_active[4], os[4], identifer[10];
	ttLARGE begin, end;
	tLBA start;
	int size;
};

int g_large2lba(tLARGE LARGE, tLBA* LBA);
int g_idechs2lba(tIDECHS IDECHS, tLBA* LBA);
int g_idechs2large(tIDECHS IDECHS, tLARGE* LARGE);
int g_chs2lba(tCHS CHS, tLBA *LBA);
int g_lba2chs(tLBA LBA, tCHS* CHS);
int g_lba2large(tLBA LBA, tLARGE *LARGE);

int a_chs2large(tCHS geometry1, tLARGE geometry2, tLARGE LARGE, tCHS* CHS);
int a_large2chs(tLARGE geometry1, tCHS geometry2, tCHS CHS, tLARGE* LARGE);
int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE* LARGE);
int a_lba2idechs(tIDECHS geometry, tLBA LBA, tIDECHS* IDECHS);
int a_lba2chs(tCHS geometry, tLBA LBA, tCHS* CHS);
int a_chs2lba(tCHS geometry, tLBA LBA, tCHS* CHS);
