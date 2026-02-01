//-*- compile-command: "gcc -O -Wall -W -pedantic main.c" -*-
// Purpose: Collect files/directories in a buffer and perform and action on it

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int help() {
  printf("Usage: sel[]\nAdd files to a buffer then perform an action on it\n"
         "-a\t Add item to buffer\n"
         "-d\t Delete item from buffer\n"
         "-c<command>\t Perform <command> on everything on the buffer\n"
         "-w\t Wipe the buffer\n"
         "-h\t print help\n");
  return 0;
}

int Append_tofile(char *var) {
  if (var == NULL || strcmp(var, " ") == 0) {
    printf("Argument missing: Missing value to append\n");
    return -1;
  } else {
    FILE *fptr;
    fptr = fopen("cand", "r");
    if (fptr != NULL) {
      fclose(fptr);
      fptr = fopen("cand", "a");
      fprintf(fptr, "%s\n", var);
      fclose(fptr);
    } else {
      fptr = fopen("cand", "w");
      fclose(fptr);
    }
  }
  return 0;
}

int Delete_item() {
  FILE *fptr = fopen("cand", "r");
  int bufsize = 1024;
  char nline[bufsize];
  char *indexarr[10]; // change so its dynamically allocated
  int sizeofarr = sizeof(indexarr) / sizeof(indexarr[0]);
  int count = 0;
  if (fptr != NULL) {
    while (fgets(nline, sizeof(nline), fptr)) {
      printf("%d %s", count, nline);
      indexarr[count] = strdup(nline);
      count++;
    }
    fclose(fptr);
  } else {
    printf("Unable to open file\n");
    return -1;
  }
  int user_index;
  printf("Enter the index of the file you want to delete: ");
  scanf("%d", &user_index);

  indexarr[user_index] = NULL; // remove selected item from array

  FILE *Sfptr = fopen("cand", "a");
  if (fptr != NULL) {
    for (int i; i <= 8; i++) {
      fprintf(Sfptr, "%s\n", indexarr[i]);
    }

    fclose(Sfptr);
  } else {
    printf("Unable to open file!\n");
    return -1;
  }
  return 0;
}
int Wipe_file() {
  bool sanity = true;
  while (sanity == true) {
    printf("Are you sure you want to wipe?(y/n): ");
    char userinput;
    scanf("%c", &userinput);
    if (userinput == 'y' || userinput == 'Y') {
      FILE *fptr;
      fptr = fopen("cand", "w");
      fclose(fptr);
      sanity = false;
    } else if (userinput == 'n') {
      sanity = false;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (strcmp(argv[1], "-c") == 0) {
    printf("preform command on buffer\n");
  } else if (strcmp(argv[1], "-a") == 0) {
    Append_tofile(argv[2]);
  } else if (strcmp(argv[1], "-d") == 0) {
    Delete_item();
  } else if (strcmp(argv[1], "-w") == 0) {
    Wipe_file();
  } else if (strcmp(argv[1], "-h") == 0) {
    help();
  }
  /* char *RealPath = realpath(argv[1], NULL); */
  /* printf("%s\n",RealPath); */
  return 0;
}
