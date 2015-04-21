#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "RandomNumberGrabber.h"
#include "Organizer.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;

int main(int argc, char **argv)
{
  int aflag = 0;
  int fvalue = 32;
  char *avalue = NULL;
  char *ovalue = NULL;
  int index;
  int c;

  opterr = 0;
  while ((c = getopt (argc, argv, "a:f:o:")) != -1)
    switch (c)
      {
      case 'a':
        avalue = optarg;
        aflag = 1;
        break;
      case 'f':
        fvalue = atoi(optarg);
        break;
      case 'o':
        ovalue = optarg;
        break;
      case '?':
        if (optopt == 'o' || optopt == 'a' || optopt == 'f')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  //printf ("aflag = %d, avalue = %s, fvalue = %d, ovalue = %s\n",
  //        aflag, avalue, fvalue, ovalue);

  // for (index = optind; index < argc; index++)
  //  printf ("Non-option argument %s\n", argv[index]);

    char* input_file = argv[argc - 2];
    char* random_file = argv[argc - 1];
    Organizer org(input_file, random_file, ovalue, avalue, fvalue);

    return 0;
    // Printing out to test
}


