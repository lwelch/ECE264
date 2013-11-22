#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "pa09.h"
#include "tree.h"

int main (int argc, char ** argv)
{
  //check arguments
  if (argc != 3)
    {
      printf("usage: ./pa09 <input file> <output file>\n");
      return EXIT_FAILURE;
    }
  
  FILE *fh = fopen(argv[1], "r");

  if(fh == NULL)
    {
      printf("The input file failed to open correctly\n");
      return EXIT_FAILURE;
    }

  HuffNode * base = NULL;
  int byte1 = fgetc(fh);
  rewind(fh);
  if (byte1 == '1')
    {
      base = TreeCreate(fh);
    }
  else
    {
      base = bitCreate(fh);
    }

  FILE * savefile = fopen(argv[2], "w");
  //Huff_postOrderPrint(base);
  HuffPrintToFile(base, savefile);

  TreeDelete(base);
  fclose(fh);
  fclose(savefile);

  return EXIT_SUCCESS;
}

