// Copyright 2024 Hicham Saidi
// All rights reserved.
#ifndef RESTORE_H_   /* Include guard */
#define RESTORE_H_

#include <stdio.h>
#include <stdlib.h>
#include "basher.h"
#include "color.h"
/*
  In this function you will find all the restoration functions
   
  void full_restore(const char* path); 
   
  void incremental_restore(const char* path);
   
  void differential_restore(const char* path);

    ----> Here path is where to put data generate from the backup.
*/

char* select_backup(int i) {
  // Allocate memory for the path
  char *path = (char*) malloc(256);  // Change size as needed
  if (path == NULL) return NULL;  // Return NULL if memory allocation fails
  char command[255];
  switch (i)
  {
    case 1:
      snprintf(path, 256, "full");
      break;
    case 2:
      snprintf(path, 256, "incremental");
      break;
    case 3: 
      snprintf(path, 256, "differential");
      break;
    default:
      printf(RED "dev error: verify select_backup options" RESET);
      return NULL;
      break;
  }
  printf("\tList of all Backups: \n");
  snprintf(command, sizeof(command), "ls /etc/backup/%s", path);
  execute_command(command);
  // Prompt the user for the backup path
  printf("Enter the back up to restore here in the form of date_time (yyyy-mm-dd_hh-min-ss):\n");
  scanf("%255s", path);  // Limit input to prevent buffer overflow
  return path;  // Return the chosen path
}

// This will do a restoration from the Full Back up
void full_restore(const char* path) {
  // Construct the command string
  char command[255];
  char* backup_date = select_backup(1);
  snprintf(command, sizeof(command), "sudo ./backup.sh restore 1 %s %s",backup_date , path);
  execute_command(command);
}



// This will do a restoration from the Incremental Back up
void incremental_restore(const char* path) {
  // Construct the command string
  char command[255];
  char* backup_date = select_backup(2);
  snprintf(command, sizeof(command), "sudo ./backup.sh restore 2 %s %s",backup_date, path);
  execute_command(command);
}

// This will do a restoration from the Differential Back up
void differential_restore(const char* path) {
  // Construct the command string
  char command[255];
  char* backup_date = select_backup(3);
  snprintf(command, sizeof(command), "sudo ./backup.sh restore 3 %s %s",backup_date ,path);
  execute_command(command);
}

#endif