#include "functions.h"

/**
 * Project Specific Functions
 */
void CreateBinaryTextFile(char* filename)
{
	srand(time(NULL));
	int randnum;
	randnum = (rand() % 50);

	FILE *fp;
	fp=fopen(filename, "wb");

	int i;
	for(i = 0; i < randnum; i++){
		int randcolor;
		randcolor = (rand() % 5);
		printf("%d\n", randcolor);
		fwrite(&randcolor, 1, sizeof(randcolor), fp);
	}
}

int getIntFromBinaryFile(FILE* binaryFile)
{
	int buffer[1];
	if(fread(buffer, sizeof(buffer[0]), sizeof(buffer)/sizeof(buffer[0]), binaryFile) != 0)
		return buffer[0];
	else
		return -1;
}

char* getFilename(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "ERROR: No filename given\n");
		exit(1);
	}
	else if (argc > 2)
	{
		fprintf(stderr, "ERROR: Too many parameters passed\n");
		exit(1);
	}
	char* filename;
	
	filename = argv[1];

	return filename;
}

int childGetCount(int color, char* filename)
{
	int count;
	char* cwd;
	cwd = malloc(sizeof(char) * 1024);
	cwd = getcwd(cwd, 1024);

	count = getCountForDir(cwd, filename, color);

	free(cwd);

	return count;
}

int getCountForDir(char* dirpath, char* filename, int color)
{
	int i;
	int count;
	count = 0;

	if(isInDir(filename, dirpath))
	{
		char* filepath;
		filepath = addToPath(dirpath, filename);
		count = getCountForFile(filepath, color);
		free(filepath);
	}
	
	char** subdirs;
	int numSubdirs;
	numSubdirs = getSubdirs(dirpath, &subdirs);
	
	for(i = 0; i < numSubdirs; i++)
	{
		count += getCountForDir(subdirs[i], filename, color);
		free(subdirs[i]);
	}

	free(subdirs);
	
	return count;
}

int isInDir(char* filename, char* dirpath)
{
	int wasFound;
	char* filepath;
	filepath = addToPath(dirpath, filename);

	if(access(filepath, F_OK) == -1)
		wasFound = 0;
	else
		wasFound = 1;

	free(filepath);
	return wasFound;
}

char* addToPath(char* dirpath, char* subpath)
{
	char* path;
	int pathlen;
	pathlen = 1;
	pathlen += strlen(dirpath);
	pathlen += strlen("/");
	pathlen += strlen(subpath);
	path = malloc(sizeof(char) * pathlen);
	strcpy(path, dirpath);
	strcat(path, "/");
	strcat(path, subpath);
	return path;
}

int getCountForFile(char* filepath, int color)
{
	FILE *fp;
	fp=fopen(filepath, "rb");

	int count;
	count = 0;

	int i;
	do
	{
		i = getIntFromBinaryFile(fp);
		if(i == color)
			count++;
	}while(i != -1);

	fclose(fp);

	return count;
}

int getSubdirs(char* dirpath, char*** subdirsNames)
{
	DIR* dirp;
	DIR* subdir;
	struct dirent* dp;

	char** subdirs;
	int subdirCap;
	subdirCap = 1;
	subdirs = malloc(sizeof(char*) * subdirCap);
	int count;
	count = 0;

	dirp = opendir(dirpath);
	do
	{
		errno = 0;
		dp = readdir(dirp);
		if (dp != NULL)
		{
			if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			{
				char* subdirpath;
				subdirpath = addToPath(dirpath, dp->d_name);
				subdir = opendir(subdirpath);

				if(subdir != 0)
				{
					if(count >= subdirCap)
					{
						expandSubdirArray(&subdirs, subdirCap);
						subdirCap *= 2;
					}
					subdirs[count] = malloc(sizeof(char) * strlen(subdirpath) + 1);
					strcpy(subdirs[count], subdirpath);
					count ++;
				}

				free(subdirpath);
				closedir(subdir);
			}
		}
		else
		{
			if(errno != 0)
				printf("Read Error\n");

			closedir(dirp);
		}
	} while(dp);
	*subdirsNames = subdirs;

	return count;
}

void expandSubdirArray(char*** subdirs, int cap)
{
	char** temp;
	temp = malloc(sizeof(char*) * (cap * 2) + 1);
	int i;
	for(i = 0; i < cap; i++)
	{
		temp[i] = malloc(sizeof(char) * strlen(subdirs[0][i]) + 1);
		strcpy(temp[i], subdirs[0][i]);
		free(subdirs[0][i]);
	}
	free(subdirs[0]);
	subdirs[0] = malloc(sizeof(char*) * (cap * 2));
	for(i = 0; i < cap; i++)
	{
		subdirs[0][i] = malloc(sizeof(char) * strlen(temp[i]) + 1);
		strcpy(subdirs[0][i], temp[i]);
		free(temp[i]);
	}
	free(temp);
}

































