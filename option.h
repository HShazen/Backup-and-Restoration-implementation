// Copyright 2024 Hicham Saidi
// All rights reserved.
#ifndef OPTION_H_   /* Include guard */
#define OPTION_H_

#define MAX_ATTEMPTS 9

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "backup.h"
#include "restore.h"
#include "color.h"
/*
   In this function you will find all the selection and choosing functions
   char* date();

   void choose_option();

   char* choose_path();

   void choose_backup(const char* path);
   
   void choose_restoration(const char* path);

   char* when_to_backup();
*/
// Function declarations
  void choose_option();
  char* choose_path(int opt);
  void choose_backup(const char* path);
  void choose_restore(const char* path);

void stop_attempt(int i) {
  if (!(i < MAX_ATTEMPTS)) {
    printf(RED "\tMaximum attempts reached 10. Exiting..." RESET);
    exit(0);
  }
}

void choose_option() {
  int opt = -1;
  int i = 0, j = 0;
  while(opt != 0) {
    i++;
    stop_attempt(i);
    printf("Choose an option:\n");
    printf("1. Back up\n");
    printf("2. Restore\n");
    printf("0. Exit\n");
    // Input handling
    j = 0;
    while (scanf("%d", &opt) != 1) { //|| !(opt >= 0 && opt <= 2)
      stop_attempt(j++);
      printf(RED "Invalid input.\n" RESET);
      while (getchar() != '\n'); // Clear the input buffer
    }
    switch (opt){
      case 1:
        printf("\t -----> Backup options:\n");
        char* path = choose_path(1);
        choose_backup(path);
        break;
      case 2:
        printf("\t -----> Restore options:\n");
        char* restoration_path = choose_path(2);
        choose_restore(restoration_path);
        break;
      case 0:
        printf(BLU "\nExiting ...\n" RESET);
        exit(0);
        break;
      default:
        printf(YEL "\nError please choose a valide number between 0 and 2.\n" RESET);
    }
  }
}

void choose_backup(const char* path) {
  int opt = -1, i = 0;
  char *p = (char*) path;
  while(opt != 0) {  
    i++;
    stop_attempt(i);
    printf("\n\n\tChoose the backup type to configure by selecting a number:\n");
    printf("\t1. Full Back up\n");
    printf("\t2. Incremental Back up\n");
    printf("\t3. Differential Back up\n");
    printf("\t4. Change the path (The data we need to back up)\n");
    printf("\t0. Exit\n");
    // Input handling
    while (scanf("%d", &opt) != 1) { // || !(opt >= 0 && opt <= 4)
      stop_attempt(i++);
      printf(RED "Invalid input.\n" RESET);
      while (getchar() != '\n'); // Clear the input buffer
    }
    switch (opt){
      case 1:
        full_backup(p);
        break;
      case 2:
        incremental_backup(p);
        break;
      case 3:
        differential_backup(p);
        break;
      case 4:
        p = choose_path(1);
        break;
      case 0:
        printf(BLU "\nExiting ...\n\n" RESET);
        break;
      default:
        printf(YEL "\nError please choose a valide number between 0 and 4..\n" RESET);
    }
  }
}

// Choose path
char* choose_path(int opt) {
    // Allocate memory for the path
    char *path = (char*) malloc(256);  // Change size as needed
    if (path == NULL) {
        return NULL;  // Return NULL if memory allocation fails
    }

    // Prompt the user for the backup path
    switch (opt)
    {
    case 1:
      printf("Enter the path of what to back up here: ");
      break;
    case 2:
      printf("Enter the path to where generate the restoration here: ");
      break;
    default:
      printf(RED "\ndev_error: input error in function choose_path (please see the function in option.h)\n" RESET);
      break;
    }
    scanf("%255s", path);  // Limit input to prevent buffer overflow

    return path;  // Return the chosen path
}

void choose_restore(const char* path) {
  int opt = -1;
  char* p = (char*) path;
  while(opt != 0) {  
    printf("\n\tChoose the back up you will restore the data from by selecting a number:\n");
    printf("\t1. Full Back up\n");
    printf("\t2. Incremental Back up\n");
    printf("\t3. Differential Back up\n");
    printf("\t4. Change the restoration path (where to restore all the data)\n");
    printf("\t0. Exit\n");
    // Input handling
    while (scanf("%d", &opt) != 1) { // || !(opt >= 0 && opt <= 4)
      printf(RED "Invalid input.\n" RESET);
      while (getchar() != '\n'); // Clear the input buffer
    }
    switch (opt){
      case 1:
        full_restore(p);
        break;
      case 2:
        incremental_restore(p);
        break;
      case 3:
        differential_restore(p);
        break;
      case 4:
        p = choose_path(2);
        break;
      case 0:
        printf(BLU "\nExiting ...\n\n" RESET);
        break;
      default:
        printf(YEL "\nError please choose a valide number between 0 and 4.\n" RESET);
    }
  }
}
#endif

/*
void choose_restoration(const char* path) {
  int opt = -1, i = 0;
  char *p = (char*) path;
  while(opt != 0) {  
    i++;
    stop_attempt(i);
    printf("\n\n\tChoose the backup you will restore the data from by selecting a number:\n");
    printf("\t1. Full Backup\n");
    printf("\t2. Incremental Backup\n");
    printf("\t3. Differential Backup\n");
    printf("\t4. Change the restoration path (where to restore all the data)\n");
    printf("\t0. Exit\n");
    // Input handling
    while (scanf("%d", &opt) != 1 || !(opt >= 0 && opt <= 4)) {
      printf("Invalid input. Plaese enter a number between 0 and 4.\n");
      while (getchar() != '\n'); // Clear the input buffer
    }

    switch (opt){
      case 1:
        full_backup(p);
        break;
      case 2:
        incremental_backup(p);
        break;
      case 3:
        differential_backup(p);
        break;
      case 4:
        p = choose_path();
        break;
      case 0:
        printf("\nExiting after choosing 0.\n");
        break;
      default:
        printf("\nError please choose a valide number.\n");
    }
  }
}

*/