#include "file.h"

//REGION TEXT FILE HELPER:
FileTXT* initTextFile(char* path,char* permission)
{

	int pathLength = sizeof(path) / sizeof(char);
	
	char* fpathP = (char*) calloc(pathLength,sizeof(char));

	if(fpathP == NULL)
	{
		return NULL;
	}

	strcpy(fpathP,path);

	int permissionLength = sizeof(permission) / sizeof(char*);

	if(permissionLength >= 4)
	{
		free(fpathP);
		return NULL;
	}

	bool isBinary = false;

	if(strstr(permission, "b") != NULL)
	{
		free(fpathP);
		assert("For binary files use FILEBIN");
		return NULL;
	}

	char* fpermissionP = (char*) calloc(permissionLength,sizeof(char));

	if(fpermissionP == NULL)
	{
		free(fpathP);
		return NULL;
	}

	strcpy(fpermissionP,permission);

	FILE *fptrP = (FILE*) calloc(1,sizeof(FILE*));
	
	if(fptrP == NULL)
	{
		free(fpathP);
		free(fpermissionP);
		return NULL;
	}

	
	FileTXT* fTXTp = (FileTXT*) calloc(1,sizeof(FileTXT*));

	if(fTXTp == NULL)
	{
		free(fpathP);
		free(fpermissionP);
		free(fptrP);
		return NULL;
	}

	fTXTp->path = fpathP;

	fTXTp->permission = fpermissionP;
	fTXTp->fileP = fptrP;

	return fTXTp;
}

int fileTxtRead(FileTXT* f)
{
	if((f->fileP = fopen(f->path,f->permission)) == NULL)
	{
		printf("error while trying read file");
		return -1;
	}

	char buffer[BUFFER_FILE_SIZE];
	
	while (fgets(buffer, BUFFER_FILE_SIZE, f->fileP) != NULL)
 	{
   		printf("%s \n",buffer);
 	}
 	
 	if (feof(f->fileP))
 	{
   		fclose(f->fileP);
 	}

	return 0;
}

int fileTxtWrite(FileTXT* f, char* message)
{
	int messageLenght = sizeof message / sizeof(char);

	if(messageLenght > 255)
	{
		printf("Too long message");
		return -1;
	}

   	if((f->fileP = fopen(f->path,f->permission)) == NULL)
    {
		printf("error while trying write file");
		return -1;
	}
   	
   fprintf(f->fileP,"\n");
   fprintf(f->fileP,"%s \n",message);
   fclose(f->fileP);
   return 0;
}

void deinitTextFile(FileTXT* f)
{
	free(f->path);
	free(f->permission);
	//free(f->pFile); // removed cause fclose got rid off already
	free(f);
}

//END REGION TEXT FILE HELPER:

//REGION BIN FILE HELPER:
FileBIN* initBinFile(char* path,char* permission)
{

	int pathLength = sizeof(path) / sizeof(char);
	
	char* fpathP = (char*) calloc(pathLength,sizeof(char));

	if(fpathP == NULL)
	{
		return NULL;
	}

	strcpy(fpathP,path);

	int permissionLength = sizeof(permission) / sizeof(char*);

	if(permissionLength >= 4)
	{
		free(fpathP);
		return NULL;
	}

	if(strstr(permission, "b") == NULL)
	{
		free(fpathP);
		assert("For not binary files use FILETXT");
		return NULL;
	}

	char* fpermissionP = (char*) calloc(permissionLength,sizeof(char));

	if(fpermissionP == NULL)
	{
		free(fpathP);
		return NULL;
	}

	strcpy(fpermissionP,permission);

	FILE *fptrP = (FILE*) calloc(1,sizeof(FILE*));
	
	if(fptrP == NULL)
	{
		free(fpathP);
		free(fpermissionP);
		return NULL;
	}

	
	FileBIN* fBINp = (FileBIN*) calloc(1,sizeof(FileBIN*));

	if(fBINp == NULL)
	{
		free(fpathP);
		free(fpermissionP);
		free(fptrP);
		return NULL;
	}

	fBINp->path = fpathP;

	fBINp->permission = fpermissionP;
	fBINp->fileP = fptrP;

	return fBINp;
}

int fileBinRead(FileBIN* f)
{
	if((f->fileP = fopen(f->path,f->permission)) == NULL)
	{
		printf("error while trying read file");
		return -1;
	}

	char buffer[BUFFER_FILE_SIZE];
	
	fread(buffer, BUFFER_FILE_SIZE*sizeof(char), 1,f->fileP);
 	
 	printf("%s",buffer);

	return 0;
}

int fileBinWrite(FileBIN* f, char* binMessage)
{
	
   	if((f->fileP = fopen(f->path,f->permission)) == NULL)
    {
		printf("error while trying write file");
		return -1;
	}
   
   char newline = '\n';	
   fwrite(&newline,1,sizeof(char),f->fileP);	
   fwrite(binMessage,1,sizeof(binMessage),f->fileP);
   fclose(f->fileP);
   return 0;
}

void deinitBinFile(FileBIN* f)
{
	free(f->path);
	free(f->permission);
	//free(f->pFile); // removed cause fclose got rid off already
	free(f);
}

//END REGION BIN FILE HELPER: