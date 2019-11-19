#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int readDir(char * dirname){
  DIR * directory;
  if ((directory = opendir(dirname)) == NULL){
    printf("%s\n",strerror(errno));
    return 0;
  }
  struct dirent * entry;
  struct stat meta;
  while ((entry = readdir(directory)) != NULL){
    stat(entry->d_name,&meta);
    if (entry->d_type == 4){
      printf("Directory %s\n",entry->d_name);
      if (strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0){
	readDir(entry->d_name);
      }
    }
    else
      printf("File %s\n",entry->d_name);
  }
  closedir(directory);
  return 1;
}

off_t dirSize(char * dirname){
  DIR * directory;
  if ((directory = opendir(dirname)) == NULL)
    return 0;
  struct dirent * entry;
  off_t dirsize= 0;
  struct stat meta;
  while ((entry = readdir(directory))){
    stat(entry->d_name,&meta);
    if (entry->d_type == 8){
      dirsize+=meta.st_size;
    }
    if (entry->d_type == 4){
      if (strcmp(entry->d_name,".") != 0 && strcmp(entry->d_name,"..") != 0){
	dirsize += dirSize(entry->d_name);
      }
    }
  }
  closedir(directory);
  return dirsize;
}

int main(int argc, char *argv[]){
  printf("Reading the current directory: \n");
  if (readDir(".") == 0)
    return 0;
  off_t size = dirSize(".");
  int counter = 0;
  while ((size % 1024) > 1024){
    size /= 1024;
    counter++;
  }
  char * unit = "B";
  if (counter == 1)
    unit = "KB";
  if (counter == 2)
    unit = "MB";
  if (counter ==3)
    unit = "GB";
  printf("The size of the files in this directory is and its subdirectories is : %lld %s\n\n",size,unit);
  if (argc > 2)
    printf("Too many directories entered");
  char buffer[500];
  printf("enter the directory you wish to read: \n");
  fgets(&buffer,500,stdin);
  if (readDir(buffer) == 0)
    return 0;
  size = dirSize(buffer);
  counter = 0;
  while ((size % 1024) > 1024){
    size /= 1024;
    counter++;
  }
  unit = "B";
  if (counter == 1)
    unit = "KB";
  if (counter == 2)
    unit = "MB";
  if (counter ==3)
    unit = "GB";
  printf("The size of the files in this directory is and its subdirectories is : %lld %s\n",size,unit);
  return 0;
}
  
