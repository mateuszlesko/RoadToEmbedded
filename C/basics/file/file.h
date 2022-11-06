#ifndef FILE_HELPER

#define FILE_HELPER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define BUFFER_FILE_SIZE 255

typedef struct FileTXT
{
	FILE* fileP;
	char* path;
	char* permission;
}FileTXT;

typedef struct FileBIN
{
	FILE* fileP;
	char* path;
	char* permission;
}FileBIN;
	
FileTXT* initTextFile(char* path,char* permission);

void deinitTextFile(FileTXT* f);

int fileTxtRead(FileTXT* f);

int fileTxtWrite(FileTXT* f, char* message);

struct FileBIN* initBinFile(char* path, char* permission);

void deinitBinFile(FileBIN* f);

int fileBinRead(FileBIN* f);

int fileBinWrite(FileBIN* f, char* binMessage);
#endif