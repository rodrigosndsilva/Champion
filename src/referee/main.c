#include "main.h"

int main(int argc, char *argv[]) {
  readingArguments(argc, argv, &t);
  readingenvvars(&t);
  return EXIT_FAILURE;
}
