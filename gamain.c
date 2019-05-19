#include <stdio.h>

#include "g2a.h"

int S, H, C, active = 0;

int main() {
	tIDECHS IDECHS; tLBA LBA; tLARGE LARGE;
	struct table t[10];
	struct table te[10];
	int start = 1, i = 0, j;
	float c, h, s;
	double size;
	int base = 0, ext = 0;
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




	while (1) {
		printf ("\nSize of disk: %f\n", size);
		printf ("Input size of part or 0:"); scanf ("%d", &t[i].size);
		size = size - t[i].size;
		if (t[i].size == 0 || size <= 0) break;

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
		if (strcmp (t[i].identifer, "FAT12") == 0) strcpy (t[i].os, "01"),base++;
		else if  (strcmp (t[i].identifer, "FAT16") == 0) strcpy (t[i].os, "04"),base++;
		else if  (strcmp (t[i].identifer, "Extended") == 0){
			strcpy (te[ext].os, "05");
			te[ext].size = size;
				if (active == 0) {
					printf ("Is part active? (1 or 0) "); scanf ("%d", &active);
					while (active != 1 && active != 0) {
						printf ("Error! Incorrect value of active; Active can be equal to 0 or 1.\n");
						printf ("Try again.\n");
						printf ("Is part active? (1 or 0) "); scanf ("%d", &active);
					}
					if (active == 0) strcpy (te[i].is_active, "0");
					else  {
						strcpy (te[i].is_active, "80h");
						active=1;
					}
				} 
			else{
				strcpy (te[i].is_active, "0");
			}
			te[i].start.S = start;
			start = te[i].start.S + te[i].size;
			LBA.S = start;


			a_lba2large (LARGE, te[i].start, &te[i].begin);
			a_lba2large (LARGE, LBA, &te[i].end);
			ext++;
		}
		else if  (strcmp (t[i].identifer, "MS-DOS_FAT16") == 0) strcpy (t[i].os, "06"),base++;
		else if  (strcmp (t[i].identifer, "NTFS") == 0) strcpy (t[i].os, "07"),base++; 
		else if  (strcmp (t[i].identifer, "Win95_FAT32") == 0) strcpy (t[i].os, "0c"),base++;
		else if  (strcmp (t[i].identifer, "Win95_FAT16") == 0) strcpy (t[i].os, "0Eh"),base++;
		else if  (strcmp (t[i].identifer, "Linux_swap") == 0) strcpy (t[i].os, "82"),base++;
		else if  (strcmp (t[i].identifer, "Linux") == 0) strcpy (t[i].os, "83"),base++;
		else strcpy (t[i].os, "00"),base++;
		if (strcmp (t[i].identifer, "Extended") != 0) {
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
			t[i].start.S = start;
			start = t[i].start.S + t[i].size;
			LBA.S = start;


			a_lba2large (LARGE, t[i].start, &t[i].begin);
			a_lba2large (LARGE, LBA, &t[i].end);
			++i;
		}
			if(base==4){
				printf("Entered max count of main directs");
				break;
			}
	}
    printf ("\n");
    printf("Count of main direct: %d\nCount of extended direct: %d\n",base,ext);
	for (j = 0; j < i; ++j) {
		printf("Active %s\t", t[j].is_active);
		printf("CHS start %d %d %d\t\t", t[j].begin.C, t[j].begin.H, t[j].begin.S);
		printf("OC %s\t\t", t[j].os);
		printf ("CHS end %d %d %d\t\t", t[j].end.C , t[j].end.H , t[j].end.S);
		printf("LBA %d\t\tsize %d \n\n", t[j].start.S, t[j].size);
	}
	for (j = 0; j < ext; ++j) {
		printf("Active %s\t", te[j].is_active);
		printf("CHS start %d %d %d\t\t", te[j].begin.C, te[j].begin.H, te[j].begin.S);
		printf("OC %s\t\t", te[j].os);
		printf ("CHS end %d %d %d\t\t", te[j].end.C , te[j].end.H , te[j].end.S);
		printf("LBA %d\t\tsize %d \n\n", te[j].start.S, te[j].size);
	}
	return 0;
}
