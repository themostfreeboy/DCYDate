#include "WriteFile.h"
#include "stdafx.h"

void WriteFile(const char writefilename[], char data[], int length)
{
	errno_t err_write;
	FILE *fp_write = NULL;
	err_write = fopen_s(&fp_write, writefilename, "wb");
	if (err_write != 0)
	{
		return;//文件打开失败
	}
	char *p;
	unsigned int i = 0;
	p = data;
	for (i = 0; i<length; i++)
	{
		fprintf_s(fp_write, "%c", *p);
		p++;
	}
	fclose(fp_write);
	return;
}