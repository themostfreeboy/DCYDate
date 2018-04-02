#include "ReadFile.h"
#include "stdafx.h"

void ReadFile(const char readfilename[], const char writefilename[])
{
	errno_t err_read, err_write;
	FILE *fp_read = NULL;
	FILE *fp_write = NULL;
	err_read = fopen_s(&fp_read, readfilename, "rb");
	err_write = fopen_s(&fp_write, writefilename, "w");
	if (err_read != 0)
	{
		return;//文件打开失败
	}
	if (err_write != 0)
	{
		return;//文件打开失败
	}
	unsigned char temp;
	unsigned int sum = 0;
	fprintf_s(fp_write, "{");
	int first_time = 0;
	while (fscanf_s(fp_read, "%c", &temp) != EOF)
	{
		if (first_time == 0)
		{
			first_time = 1;
		}
		else
		{
			fprintf_s(fp_write, ",");
		}
		fprintf_s(fp_write, "0x");
		fprintf_s(fp_write, "%02x", temp);
		sum++;
	}
	fprintf_s(fp_write, "};");
	fprintf_s(fp_write, "\n");
	fprintf_s(fp_write, "sum:%u", sum);
	fclose(fp_read);
	fclose(fp_write);
	return;
}