// Copyright 2024 Hicham Saidi
// All rights reserved.
#ifndef BASH_HELP_H_   /* Include guard */
#define BASH_HELP_H_

#include <stdio.h>
#include <stdlib.h>

/*
  In this function you will find all the backup and restoration functions
  void execute_command(const char* command);

  void bash_launcher();
*/

void execute_command(const char* command) {
  // Execute the command
  int result = system(command);
  // Check if the command was successful
  if (result == -1) {
    perror("Error executing command");
  }
}
// Bash launcher to be able to execute it.
void bash_launcher() {
  // Construct the command string
  char command[100];
  snprintf(command, sizeof(command), "chmod +x ./backup.sh");
  execute_command(command);
}
#endif