// Copyright 2025 Landon Davidson
// landond@uw.edu

#include <stdio.h>
#include <stdlib.h>

// Open a file and print the bytes in reverse order
int main(int argc, char** argv) {
  // Check there is only one argument, exit with a failure code if not
  if (argc != 2) {
    fprintf(stderr, "You entered %d arguments, ex6 only takes 1\n", argc - 1);
    return EXIT_FAILURE;
  }
  // Open file specified by first argument
  FILE* file = fopen(argv[1], "rb");

  // If fopen failed print an error and exit with failure code
  if (file == NULL) {
    fprintf(stderr, "The file %s ", argv[1]);
    perror("failed to open for read");
    return EXIT_FAILURE;
  }



  // Close file and prepare for successful exit
  fclose(file);
  return EXIT_SUCCESS;
}

