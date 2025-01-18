// Copyright 2025 Landon Davidson
// landond@uw.edu

#include <stdio.h>
#include <stdlib.h>

// Open a file and print the bytes in reverse order
int main(int argc, char** argv) {
  // Check there is only one argument, exit with a failure code if not
  if (argc != 2) {
    fprintf(stderr, "You entered %d arguments, this only takes 1\n", argc - 1);
    return EXIT_FAILURE;
  }
  // Open file specified by first argument
  FILE *input = fopen(argv[1], "rb");

  // If fopen failed print an error and exit with failure code
  if (input == NULL) {
    fprintf(stderr, "The file %s ", argv[1]);
    perror("failed to open for reading");
    return EXIT_FAILURE;
  }

  // Get size of the file
  fseek(input, 0, SEEK_END);
  long size = ftell(input);
  // Iterate from end to start and printf each byte
  for (; size > 0; size--) {
    // Initialize cur_char as output parameter for fread
    char cur_char;
    // Moves cursor from end to start of file one at a time
    fseek(input, size - 1, SEEK_SET);
    // Read current byte in file and store in cur_char
    fread(&cur_char, sizeof(char), 1, input);
    // Print current byte stored in cur_char
    printf("%c", cur_char);
  }

  // Close file and prepare for successful exit
  fclose(input);
  return EXIT_SUCCESS;
}

