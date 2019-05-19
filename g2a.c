#include "g2a.h"

extern int C, H, S;

int g_large2lba(tLARGE LARGE, tLBA* LBA) {
	LBA->S = (LARGE.C * H + LARGE.H) * S + LARGE.S - 1;
	return 0;
}

int g_idechs2lba(tIDECHS IDECHS, tLBA* LBA) {
	LBA->S = (IDECHS.C * H + IDECHS.H) * S + IDECHS.S - 1;
	return 0;
}

int g_idechs2large(tIDECHS IDECHS, tLARGE* LARGE) {
	LARGE->S = IDECHS.S; 
	LARGE->H = IDECHS.H;
	LARGE->C = IDECHS.C;
	return 0;
}

int g_chs2lba(tCHS CHS, tLBA *LBA) {
	LBA->S = (CHS.C * 255 + CHS.H) * 63 + CHS.S - 1;
	return 0;
}

int g_lba2chs(tLBA LBA, tCHS* CHS) {
	int temp1, temp2, divider, i;
	temp1 = LBA.S / 63; 
	temp2 = temp1 / 1023;

	for (i = 2; i <= 256; i *= 2) {
		if (i / 2 < temp2 && i > temp2) {
			if (i == 256) --i;
			divider = i;
			break;
		}
	}
	CHS->S = 63;
	CHS->H = divider;
	CHS->C = temp1 / divider;
	return 0;
}

int g_lba2large(tLBA LBA, tLARGE *LARGE)
{
	tCHS gCHS;
	g_lba2chs(LBA, &gCHS);
	LARGE->C = gCHS.C/2;
	LARGE->H = gCHS.H*2;
	LARGE->S = gCHS.S;
	
	return 0;
}

int a_chs2large(tCHS geometry1, tLARGE geometry2, tLARGE LARGE, tCHS* CHS) {
	CHS->S = LARGE.S;
	CHS->C = geometry2.C * (LARGE.H % 2) + LARGE.C;
	CHS->H = (int) LARGE.H / 2;
	return 0;
}

int a_large2chs(tLARGE geometry1, tCHS geometry2, tCHS CHS, tLARGE* LARGE) {
	LARGE->S = CHS.S;
	LARGE->C = CHS.C % geometry1.C;
	LARGE->H = (int) (geometry1.H / 2) * (CHS.C % 2) + CHS.H;
	return 0;
}

int a_lba2large(tLARGE geometry, tLBA LBA, tLARGE* LARGE) {
	LARGE->S = LBA.S % geometry.S + 1;
	LARGE->H = ((LBA.S - (LARGE->S - 1)) / geometry.S) % geometry.H;
	LARGE->C = ((LBA.S - (LARGE->S - 1) - (LARGE->H * geometry.S)) / (geometry.S * geometry.H));
	return 0;
}

int a_lba2idechs(tIDECHS geometry, tLBA LBA, tIDECHS* IDECHS) {
	IDECHS->S = LBA.S % geometry.S + 1;
	IDECHS->H = ((LBA.S - (IDECHS->S - 1)) / geometry.S) % geometry.H;
	IDECHS->C = ((LBA.S - (IDECHS->S - 1) - (IDECHS->H * geometry.S)) / (geometry.S * geometry.H));
	return 0;
}

int a_lba2chs(tCHS geometry, tLBA LBA, tCHS* CHS) {
	CHS->S = LBA.S % 63 + 1;
	CHS->H = ((LBA.S - (CHS->S - 1)) / 63) % 255;
	CHS->C = ((LBA.S - (CHS->S - 1) - (CHS->H * 63)) / (63 * 255));
	return 0;
}

int a_chs2lba(tCHS geometry, tLBA LBA, tCHS* CHS) {
	CHS->S = (LBA.S % geometry.S) + 1;
	CHS->H = (LBA.S / geometry.S) % geometry.H;
	CHS->C = (LBA.S / geometry.S) / geometry.H;
	return 0;
}
