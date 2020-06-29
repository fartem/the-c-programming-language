#include <stdio.h>

/*
 * Write a programn ot compare two files, printing the first line
 * where they differ.
 */

void filecmp(FILE *, FILE *);

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	
	if (argc == 1)
	{
		printf("Please provide two files");
		return 1;
	}
	else
	{
		while (--argc > 0)
		{
			if ((fp1 = fopen(argv[1], "r")) == NULL)
			{
				printf("cat: can't open %s\n", *argv);
				return 1;
			}
			if ((fp2 = fopen(argv[2], "r")) == NULL)
			{
				printf("cat: can't open %s\n", *argv);
				return 1;
			}
			filecmp(fp1, fp2);
			fclose(fp1);
			fclose(fp2);	
		}
	}
	return 0;
}

void filecmp(FILE *fp1, FILE *fp2)
{
	int f1, f2;
	while (1)
	{
		if ((f1 = getc(fp1)) == EOF)
			break;
		if ((f2 = getc(fp2)) == EOF)
			break;

		if (f1 != f2)
		{
			putchar(f1);
			putchar(f2);
			break;
		}
	}
}

