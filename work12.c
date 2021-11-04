#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[]) {

  char directory[100];

  if (argc > 1) {
    strcpy(directory, argv[1]);
  }
  else {
    printf("Directory not found. Please enter directory: ");
    fgets(directory, sizeof(directory)-1, stdin);
    directory[strlen(directory)-1] = 0;
  }

  printf("===============================================================\n");

  struct dirent *dent;
  DIR *d = opendir(directory);

  if (d == NULL) {
    printf("Error: %s\n", strerror(errno));
  }

  else {
    printf("Statistics for directory: %s\n", directory);
    printf("===============================================================\n");

    printf(" File/Dir: %-20s | Size: %-10s | d_type: \n", "File/Dir Name", "# of bytes");

    struct stat sb;

    unsigned long long size = 0;

    dent = readdir(d);
    while (dent) {
      stat(dent->d_name, &sb);
      if (dent->d_type == 8) {
        size += sb.st_size;
        printf("     File: %-20s | Size: %-10llu | d_type: %d\n", dent->d_name, sb.st_size, dent->d_type);
      }
      else if (dent->d_type == 4) {
        printf("Directory: %-20s | Size: %-10llu | d_type: %d\n", dent->d_name, sb.st_size, dent->d_type);
      }
      dent = readdir(d);
    }

    printf("===============================================================\n");
    printf("Total Directory Size: %llu Bytes\n", size);
    printf("===============================================================\n");

    // Test Run:
    // printf("\t%s\t%d\n", dent->d_name, dent->d_type);

    // Results from test run:
    // Directories: d_type == 8
    // Regular files: d_type == 4

    printf("Directories:\n");

    rewinddir(d);

    dent = readdir(d);
    while (dent) {
      if (dent->d_type == 4) {
        printf("\t%s\n", dent->d_name);
      }
      dent = readdir(d);
    }

    printf("===============================================================\n");

    printf("Regular files:\n");

    rewinddir(d);

    dent = readdir(d);
    while (dent) {
      if (dent->d_type == 8) {
        printf("\t%s\n", dent->d_name);
      }
      dent = readdir(d);
    }

    closedir(d);

    printf("===============================================================\n");
  }

  return 0;
}
