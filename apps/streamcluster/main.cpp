/**
 * main.cpp -
 * @author: James Wood
 * @version: Thu July 23 13:25:00 2020
 *
 * Copyright 2020 Jonathan Beard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
#include <math.h>
#include <sys/resource.h>
#include <climits>
#include <vector>
#include <raft>
#include <raftio>
#include <limits>

#include "raftlib_src.hpp"

int main(int argc, char **argv)
{
  char *outfilename = new char[MAXNAMESIZE];
  char *infilename = new char[MAXNAMESIZE];
  long kmin, kmax, n, chunksize, clustersize;
  int dim, nproc;

  if (argc<10) {
    fprintf(stderr, "usage: %s k1 k2 d n chunksize clustersize infile "
            "outfile nproc\n", argv[0]);
    fprintf(stderr, "  k1:          Min. number of centers allowed\n");
    fprintf(stderr, "  k2:          Max. number of centers allowed\n");
    fprintf(stderr, "  d:           Dimension of each data point\n");
    fprintf(stderr, "  n:           Number of data points\n");
    fprintf(stderr, "  chunksize:   Number of data points to handle per "
            "step\n");
    fprintf(stderr, "  clustersize: Maximum number of intermediate centers\n");
    fprintf(stderr, "  infile:      Input file (if n<=0)\n");
    fprintf(stderr, "  outfile:     Output file\n");
    fprintf(stderr, "  nproc:       Number of parallel kernels to use\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "if n > 0, points will be randomly generated instead of "
            "reading from infile.\n");
    exit(1);
  }

  kmin = atoi(argv[1]);
  kmax = atoi(argv[2]);
  dim = atoi(argv[3]);
  n = atoi(argv[4]);
  chunksize = atoi(argv[5]);
  clustersize = atoi(argv[6]);
  strcpy(infilename, argv[7]);
  strcpy(outfilename, argv[8]);
  nproc = atoi(argv[9]);

  if (nproc > MAX_PARALLEL_KERNELS)
  {
    std::cerr << "Number of requested kernels exceeds max set in code. "
        "Change max in streamcluster.hpp to continue!" << std::endl;
    exit(EXIT_FAILURE);
  }


  srand48(SEED);
  PStream* stream;
  if( n > 0 ) {
    stream = new SimStream(n);
  }
  else {
    stream = new FileStream(infilename);
  }

  streamCluster_raftlib(stream, kmin, kmax, dim, chunksize, clustersize,
                        outfilename, nproc);

  delete stream;

  return 0;
}
