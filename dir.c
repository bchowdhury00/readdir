#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readDir(char * dirname){
  DIR * directory;
  if (!(directory = opendir(dirname)))
    return 0;
  struct dirent * entry;
  struct stat meta;
  while ((entry = readdir(directory))){
    stat(entry->d_name,&meta);
    if (S_ISDIR(meta.st_mode)){
      printf("Directory %s\n",entry->d_name);
      if ((strcmp(entry->d_name,".") != 0) && (strcmp(entry->d_name,"..") != 0))
	readDir(entry->d_name);
    }
    else
      printf("File %s\n",entry->d_name);
  }
  closedir(directory);
  return 1;

}

off_t dirSize(char * dirname){
  DIR * directory;
  if (!(directory = opendir(dirname)))
    return 0;
  struct dirent * entry;
  off_t dirSize= 0;
  struct stat meta;
  while ((entry = readdir(directory))){
    stat(entry->d_name,&meta);
    if (!S_ISDIR(meta.st_mode))
      dirSize+=meta.st_size;
  }
  closedir(directory);
  return dirSize;
}

int main(){
  char * dirname = ".";
  readDir(dirname);
  off_t size = dirSize(dirname);
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
  printf("The size of the regular files in this directory is : %lld %s\n",size,unit);
}
  
