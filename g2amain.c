#include <stdio.h>

#include "g2a.h"
struct mext {
	struct table ext[4];
};


struct mext extab[4];

int S, H, C;
tIDECHS IDECHS; tLBA LBA;
int active = 0;
float c, h, s;
int exti = 0, masse[4];
struct table ex[5];
tLARGE gLARGE;

int partition(struct table *t, double size, int start) {
	int i = 0, g = 0;
	while (1) {
		printf ("\nSize of disk: %f\n", size);
		printf ("Input size of part or 0:"); scanf ("%d", &t[i].size);
		size = size - t[i].size;
		if (t[i].size == 0 || size < 0) break;

		{
		printf ("Input type of part:\n");
        printf ("\tFAT12\n");
        printf ("\tFAT16\n");
        printf ("\tExtended\n");
        printf ("\tMS-DOS_FAT16\n");
        printf ("\tNTFS\n");
        printf ("\tWin95_FAT32\n");
        printf ("\tWin95_FAT16\n");
        printf ("\tLinux_swap\n");
        printf ("\tLinux\n");
        scanf("%s", t[i].identifer);
		if (strcmp (t[i].identifer, "FAT12") == 0) strcpy (t[i].os, "01");
		else if  (strcmp (t[i].identifer, "FAT16") == 0) strcpy (t[i].os, "04");
		else if  (strcmp (t[i].identifer, "Extended") == 0){
			g = partition(extab[exti].ext, t[i].size, start);
			masse[exti] = g;
		    strcpy (t[i].os, "05");
		    exti++;
		}
		else if  (strcmp (t[i].identifer, "MS-DOS_FAT16") == 0) strcpy (t[i].os, "06");
		else if  (strcmp (t[i].identifer, "NTFS") == 0) strcpy (t[i].os, "07"); 
		else if  (strcmp (t[i].identifer, "Win95_FAT32") == 0) strcpy (t[i].os, "0c");
		else if  (strcmp (t[i].identifer, "Win95_FAT16") == 0) strcpy (t[i].os, "0Eh");
		else if  (strcmp (t[i].identifer, "Linux_swap") == 0) strcpy (t[i].os, "82");
		else if  (strcmp (t[i].identifer, "Linux") == 0) strcpy (t[i].os, "83");
		else strcpy (t[i].os, "00");
		
		if (active == 0) {
			printf ("Is part active? (1 or 0) "); scanf ("%d", &active);
			while (active != 1 && active != 0) {
				printf ("Error! Incorrect value of active; Active can be equal to 0 or 1.\n");
				printf ("Try again.\n");
				printf ("Is part active? (1 or 0) "); scanf ("%d", &active);
			}
			if (active == 0) strcpy (t[i].is_active, "0");
			else  {
				strcpy (t[i].is_active, "80h");
				active=1;
			}

		} 
		else{
			strcpy (t[i].is_active, "0");
		}
		}
		
		t[i].start.S = start;
		start = t[i].start.S + t[i].size*1024*1024*2;
		LBA.S = start;
		
		if (t[i].start.S > 1023*255*63) {
			t[i].begin.A = 255;
			t[i].begin.B = 255;
			t[i].begin.C = 255;
		} else {
			tLARGE ttL;
			a_lba2large (gLARGE, t[i].start, &ttL);
			
			t[i].begin.A = ttL.H;
			int x = ttL.C >> 8;
			t[i].begin.B = x << 6 | ttL.S;
			t[i].begin.C = ttL.C & 255;
		}
		
		if (LBA.S > 1023*255*63) {
			t[i].end.A = 255;
			t[i].end.B = 255;
			t[i].end.C = 255;
		} else {
			tLARGE ttL2;
			a_lba2large (gLARGE, LBA, &ttL2);
			
			t[i].end.A = ttL2.H;
			int x1 = ttL2.C >> 8;
			t[i].end.B = x1 << 6 | ttL2.S;
			t[i].end.C = ttL2.C & 255;
		}
		++i;
		if(i==4){
			printf("Entered max count of main directs");
			break;
		}
	}
	return i;
}

int main() {
	double size;
	int start = 1;
	
	printf("Input Cylinder/Head/Sector\n");
	printf("C: "); 
	scanf("%fl", &c);
	printf("H: ");
	scanf("%fl", &h);
	printf("S: "); 
	scanf("%fl", &s);
	IDECHS.C = c;
	IDECHS.H = h;
	IDECHS.S = s;
	
	size = c * h * s * 512 / 1024 / 1024 / 1024;
	tLBA gDisc;
	gDisc.S = c*h*s;
	
	if (gDisc.S > 1023*255*63) {
		gLARGE.C = 1023; gLARGE.H = 255; gLARGE.S = 63;
	} else {
		g_lba2large(gDisc, &gLARGE);
	}
	
	struct table t[10];
	int g = partition(t, size, start);
	
	printf("\n");
	for (int j = 0; j < g; ++j) {
		printf("Active %s\t", t[j].is_active);
		printf("CHS start %3d %3d %3d\t", t[j].begin.A, t[j].begin.B, t[j].begin.C);
		printf("OC %s\t", t[j].os);
		printf ("CHS end %3d %3d %3d\t", t[j].end.A , t[j].end.B , t[j].end.C);
		printf("LBA %8d\t\tsize %8d \n\n", t[j].start.S, t[j].size*1024*1024*2);
	}
	
	for (int j = 0; j < exti; ++j) {
		printf("\n");
		printf("Extended table %d:\n", j);
		for (int y = 0; y < masse[j]; ++y) { 
			printf("Active %s\t", extab[j].ext[y].is_active);
			printf("CHS start %3d %3d %3d\t", extab[j].ext[y].begin.A, extab[j].ext[y].begin.B, extab[j].ext[y].begin.C);
			printf("OC %s\t", extab[j].ext[y].os);
			printf ("CHS end %3d %3d %3d\t", extab[j].ext[y].end.A , extab[j].ext[y].end.B , extab[j].ext[y].end.C);
			printf("LBA %8d\t\tsize %8d \n\n", extab[j].ext[y].start.S, extab[j].ext[y].size*1024*1024*2);
		}
		printf("\n");
	}
	return 0;
}
