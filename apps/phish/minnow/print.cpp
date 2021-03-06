// MINNOW print
// print datums to screen or file

#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "phish/phish.h"

void print(int);
void close_file();

/* ---------------------------------------------------------------------- */

FILE *fp = NULL;

/* ---------------------------------------------------------------------- */

int main(int narg, char **args)
{
  phish_init(&narg,&args);
  phish_input(0,print,close_file,1);
  phish_check();

  int iarg = 1;
  while (iarg < narg) {
    if (strcmp(args[iarg],"-f") == 0) {
      if (iarg+1 > narg) phish_error("Print syntax: print -f filename");
      fp = fopen(args[iarg+1],"w");
      iarg += 2;
    } else phish_error("Print syntax: print -f filename");
  }

  if (fp == NULL) fp = stdout;

  phish_loop();
  phish_exit();
}

/* ---------------------------------------------------------------------- */

void print(int nvalues)
{
  char *value;
  int len;

  for (int i = 0; i < nvalues; i++) {
    int type = phish_unpack(&value,&len);
    switch (type) {
    case PHISH_RAW:    // assume it's a string, append '\0' and print
      value[len] = '\0';
      fprintf(fp,"%s ",value);
      break;
    case PHISH_INT8:
      fprintf(fp,"%c ",*value);
      break;
    case PHISH_INT32:
      fprintf(fp,"%d ",*(int32_t *) value);
      break;
    case PHISH_UINT64:
      fprintf(fp,"%lu ",*(uint64_t *) value);
      break;
    case PHISH_FLOAT:
      fprintf(fp,"%g ",*(float *) value);
      break;
    case PHISH_DOUBLE:
      fprintf(fp,"%g ",*(double *) value);
      break;
    case PHISH_STRING:
      fprintf(fp,"%s ",value);
      break;
    case PHISH_INT32_ARRAY: {
      int *ivec = (int32_t *) value;
      for (int j = 0; j < len; j++) fprintf(fp,"%d ",ivec[j]);
    } break;
    case PHISH_UINT64_ARRAY: {
      uint64_t *lvec = (uint64_t *) value;
      for (int j = 0; j < len; j++) fprintf(fp,"%lu ",lvec[j]);
    } break;
    case PHISH_DOUBLE_ARRAY: {
      double *dvec = (double *) value;
      for (int j = 0; j < len; j++) fprintf(fp,"%g ",dvec[j]);
    } break;
    }
  }

  fprintf(fp,"\n");
}

/* ---------------------------------------------------------------------- */

void close_file()
{
  if (fp != stdout) fclose(fp);
}
