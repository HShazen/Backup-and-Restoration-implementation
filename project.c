// Copyright 2024 Hicham Saidi
// All rights reserved.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "backup.h" // Function declarations
#include "option.h"

int main() {
  printf("\tThis is a backup application that can implimente 3 backup type.\n");
  printf("\tAll backups are stored in the /etc/ file where each type has its own directory.\n");
  bash_launcher();
  choose_option();
  return 0;
}
