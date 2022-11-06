#include <stdio.h>
#include <stdlib.h>
#include "file.h"


union File
{
	FileTXT* fileTxt;
	FileBIN* fileBin;
} f;

int binFileOperations(void)
{
	char* FILE_PATH = "dialogue.bin";
	FileBIN* bfp = initBinFile(FILE_PATH,"rb");
	
	if(bfp == NULL)
	{
		return 1;
	}
	
	f.fileBin = bfp;

	int res = fileBinRead(f.fileBin);
	
	deinitBinFile(f.fileBin);
	
	if(res < 0)
	{
		return 1;
	}

	bfp = initBinFile(FILE_PATH,"ab");
	
	if(bfp == NULL)
	{
		return 1;
	}
	
	f.fileBin = bfp;

	res = fileBinWrite(f.fileBin,"B: Til venstre");
	
	if(res < 0)
	{
		return 1;
	}
	
	deinitBinFile(f.fileBin);

	return 0;
}

int txtFileOperations(void)
{
	char* FILE_PATH = "dialogue.txt";
	FileTXT* tfp = initTextFile(FILE_PATH,"r");
	
	if(tfp == NULL)
	{
		return 1;
	}
	
	f.fileTxt = tfp;

	int res = fileTxtRead(f.fileTxt);
	
	deinitTextFile(f.fileTxt);
	
	if(res < 0)
	{
		return 1;
	}

	tfp = initTextFile(FILE_PATH,"a");
	
	if(tfp == NULL)
	{
		return 1;
	}

	f.fileTxt = tfp;
	
	res = fileTxtWrite(f.fileTxt,"B:Hei! Tak bare bra.");
	
	deinitTextFile(f.fileTxt);
	
	if(res < 0)
	{
		return 1;
	}

	return 0;
}

int main(void)
{
	int txtRes = txtFileOperations();
	int binRes = binFileOperations();
}