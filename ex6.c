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

  // Get size of the file, catch a nonzero return code
  if (fseek(input, 0, SEEK_END) != 0) {
    perror("fseek failed to SEEK_END");
    fclose(input);
    return EXIT_FAILURE;
  }
  long size = ftell(input);
  // Catch a failed ftell call
  if (size == -1) {
    perror("ftell failed");
    fclose(input);
    return EXIT_FAILURE;
  }
  // Iterate from end to start and printf each byte
  for (; size > 0; size--) {
    // Initialize cur_char as output parameter for fread
    char cur_char;
    // Moves cursor from end to start of file one at a time, catch a nonzero return code
    if (fseek(input, size - 1, SEEK_SET) != 0) {
      fprintf(stderr, "Failed to fseek to position %ld in file %s", size - 1, argv[1]);
      perror("");
      fclose(input);
      return EXIT_FAILURE;
    }
    // Read current byte in file and store in cur_char, catch when fread doesn't return exactly one byte
    // Should only see one or a zero meaning end of file or failed read
    if (fread(&cur_char, sizeof(char), 1, input) != 1) {
      fprintf(stderr, "Read of position %ld failed", size - 1);
      perror("");
      fclose(input);
      return EXIT_FAILURE;
    }
    // Print current byte stored in cur_char
    printf("%c", cur_char);
  }

  // Close file and prepare for successful exit
  fclose(input);
  return EXIT_SUCCESS;
}

