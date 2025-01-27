//-*- compile-command: "gcc -O -Wall -W -pedantic main.c" -*-
// Purpose: Collect files/directories in a buffer and perform and action on it

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO: add types to functions
// TODO: make tui library for an interface

void help() {
  printf("Usage: sel[]\nAdd files to a buffer then perform an action on it\n"
         "-a\t Add item to buffer\n"
         "-d\t Delete item from buffer\n"
         "-c<command>\t Perform <command> on everything on the buffer\n"
         "-w\t Wipe the buffer\n"
         "-h\t print help\n");
}

void Append_tofile(char *var) {
  if (var == NULL || strcmp(var, " ") == 0) {
    printf("Argument missing: Missing value to append\n");
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
}

void Delete_item() {
  FILE *fptr = fopen("cand", "r");
  int bufsize = 100;
  char nline[bufsize];
  /* char strings [no_of_strings] [max_size_of_each_string]; */
  char indexarr[10][bufsize]; // change so its dynamically allocated //FIX: this
  // doesn't work
  if (fptr != NULL) {
    int count = 1;
    while (fgets(nline, sizeof(nline), fptr)) {
      printf("%d %s", count, nline);
      indexarr[count][bufsize] = *nline; // FIX: this doesn't work
      count++;
    }
    fclose(fptr);
  } else {
    printf("Unable to open file!\n");
  }
  printf("Enter the index of the file you want to delete: ");
  int index;
  scanf("%d", &index);
  printf("\nyour val: %c\n", indexarr[index][bufsize]);
  for (int i; i <= 8; i++) {
    printf("%c", indexarr[i][bufsize]);
  }
}

void Wipe_file() {
  bool sanity = true;
  while (sanity == true) {
    printf("Are you sure you want to wipe?(y/n): "); // FIX: for some reason it
    // prints twice and fix the
    // formatting
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
}

int main(int argc, char *argv[]) {
  if (strcmp(argv[1], "-c") == 0) {
    printf("ooga");
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
