// Copyright 2024 Hicham Saidi
// All rights reserved.
#ifndef BACKUP_H_   /* Include guard */
#define BACKUP_H_

#include <stdio.h>
#include <stdlib.h>
#include "basher.h"

/*
  In this function you will find all the backup functions

  void full_backup(const char* path);
   
  void incremental_backup(const char* path);
   
  void differential_backup(const char* path);
  
  ----> Here path is where is the data to backup.
*/
/*
DESTINATION="/etc/backup"

# Create backup directories if they don't exist
mkdir -p "$DESTINATION/full" "$DESTINATION/incremental" "$DESTINATION/differential"

*/
// This will do a Full Back up
void full_backup(const char* path) {
  // Construct the command string
  char command[1024];
  snprintf(command, sizeof(command), "sudo ./backup.sh %s 1", path);
  execute_command(command);
}

// This will do an Incremental back up
void incremental_backup(const char* path) {
  // Construct the command string
  char command[1024];
  snprintf(command, sizeof(command), "sudo ./backup.sh %s 2", path);
  execute_command(command);
}

// This will do a Differential Back up
void differential_backup(const char* path) {
  // Construct the command string
  char command[1024];
  snprintf(command, sizeof(command), "sudo ./backup.sh %s 3", path);
  execute_command(command);
}
#endif