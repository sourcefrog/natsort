/* -*- mode: c; c-file-style: "k&r" -*-

   natsort.c -- Example strnatcmp application.
   
   Copyright (C) 2000 by Martin Pool <mbp@humbug.org.au>

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.
   
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   
   1. The origin of this software must not be misrepresented; you must not
      claim that you wrote the original software. If you use this software
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.
*/

/* Partial change history:
 *
 * 2003-03-18: Add --reverse option, from Alessandro Pisani.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "strnatcmp.h"

#if defined(__GNUC__)
#  define UNUSED __attribute__((__unused__))
#endif

static int fold_case = 0, verbose = 0, reverse = 0;

static void trace_result(char const *a, char const *b, int ret)
{
     char const *op;

     if (ret < 0)
	  op = "<";
     else if (ret > 0)
	  op = ">";
     else
	  op = "==";
     
     fprintf(stderr, "\tstrncatcmp: \"%s\" %s \"%s\"\n",
	     a, op, b);
}



static int compare_strings(const void *a, const void *b)
{
     char const *pa = *(char const **)a, *pb = *(char const **)b;
     int ret;

     if (fold_case)
	  ret = strnatcasecmp(pa, pb);
     else
	  ret = strnatcmp(pa, pb);

	 if (reverse)
	  ret *= -1;

	 if (verbose)
	  trace_result(pa, pb, ret);

     return ret;
}


static void usage(void)
{
     fprintf(stderr, "Usage: natsort [OPTIONS]\n"
	     "Performs a natural sort on standard input, and writes to \n"
	     "standard output.\n"
	     "\n"
	     "  --help, -h       show help text\n"
	     "  --verbose, -v    show comparisons\n"
	     "  --fold-case, -f  ignore case differences for letters\n"
		 "  --reverse, -r	 reverse the result of comparisons\n");
}


int main(int argc, char **argv)
{
     int nlines = 0;
     char *line;
     char **list = 0;
     int linelen = 0, i;
     int c, opt_ind;
     int bufsize;

     static struct option long_options[] = {
	  { "verbose", 0, NULL, 'v'},
	  { "reverse", 0, NULL, 'r'},
	  { "fold-case", 0, NULL, 'f'},
	  { "help", 0, 0, 'h' },
	  { 0, 0, 0, 0 }
     };

     /* process arguments */
     while ((c = getopt_long(argc, argv, "frvh", long_options, &opt_ind)) != -1) {	  
	  switch (c) {
	  case 'f':
	       fold_case = 1;
	       break;
	  case 'h':
	       usage();
	       return 0;
	  case 'r':
	  	   reverse = 1;
		   break;
	  case 'v':
	       verbose = 1;
	       break;
	  case '?':
	       return 1;
	  default:
	       abort();
	  }
     }	       
     
     /* read lines into an array */
     while (1) {
	  line = NULL;
	  bufsize = 0;
	  if ((linelen = getline(&line, &bufsize, stdin)) <= 0)
	       break;
	  if (line[linelen-1] == '\n')
	       line[--linelen] = 0;
	  nlines++;
	  list = (char **) realloc(list, nlines * sizeof list[0]);
	  if (!list) {
	       perror("allocate list");
	       return 1;
	  }	       
	  list[nlines-1] = line;
     }

     if (ferror(stdin)) {
	  perror("input");
	  return 1;
     }
     fclose(stdin);
     
     /* quicksort */
     qsort(list, nlines, sizeof list[0], compare_strings);
     
     /* and output */
     for (i = 0; i < nlines; i++) {
	  puts(list[i]);
     }
     if (ferror(stdout)) {
	  perror("output");
	  return 1;
     }

     return 0;
}
