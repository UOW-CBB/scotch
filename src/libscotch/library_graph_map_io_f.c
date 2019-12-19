/* Copyright 2012,2018,2019 IPB, Universite de Bordeaux, INRIA & CNRS
**
** This file is part of the Scotch software package for static mapping,
** graph partitioning and sparse matrix ordering.
**
** This software is governed by the CeCILL-C license under French law
** and abiding by the rules of distribution of free software. You can
** use, modify and/or redistribute the software under the terms of the
** CeCILL-C license as circulated by CEA, CNRS and INRIA at the following
** URL: "http://www.cecill.info".
** 
** As a counterpart to the access to the source code and rights to copy,
** modify and redistribute granted by the license, users are provided
** only with a limited warranty and the software's author, the holder of
** the economic rights, and the successive licensors have only limited
** liability.
** 
** In this respect, the user's attention is drawn to the risks associated
** with loading, using, modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean that it is complicated to manipulate, and that also
** therefore means that it is reserved for developers and experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards
** their requirements in conditions enabling the security of their
** systems and/or data to be ensured and, more generally, to use and
** operate it in the same conditions as regards security.
** 
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
*/
/************************************************************/
/**                                                        **/
/**   NAME       : library_graph_map_io_f.c                **/
/**                                                        **/
/**   AUTHOR     : Francois PELLEGRINI                     **/
/**                                                        **/
/**   FUNCTION   : This module is the Fortran API for the  **/
/**                graph i/o routines of the libSCOTCH     **/
/**                library.                                **/
/**                                                        **/
/**   DATES      : # Version 6.0  : from : 03 jul 2012     **/
/**                                 to     24 sep 2019     **/
/**                                                        **/
/************************************************************/

/*
**  The defines and includes.
*/

#define LIBRARY

#include "module.h"
#include "common.h"
#include "scotch.h"

/**************************************/
/*                                    */
/* These routines are the Fortran API */
/* for the mapping routines.          */
/*                                    */
/**************************************/

SCOTCH_FORTRAN (                      \
GRAPHTABLOAD, graphtabload, (         \
const SCOTCH_Graph * const  grafptr,  \
SCOTCH_Num * const          parttab,  \
const int * const           fileptr,  \
int * const                 revaptr), \
(grafptr, parttab, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHTABLOAD)) ": cannot duplicate handle");
    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "r")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHTABLOAD)) ": cannot open input stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_graphTabLoad (grafptr, parttab, stream);

  fclose (stream);                                /* This closes file descriptor too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                      \
GRAPHTABSAVE, graphtabsave, (         \
const SCOTCH_Graph * const  grafptr,  \
const SCOTCH_Num * const    parttab,  \
const int * const           fileptr,  \
int * const                 revaptr), \
(grafptr, parttab, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHTABSAVE)) ": cannot duplicate handle");

    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "w")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHTABSAVE)) ": cannot open output stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_graphTabSave (grafptr, parttab, stream);

  fclose (stream);                                /* This closes filenum too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                      \
GRAPHMAPLOAD, graphmapload, (         \
const SCOTCH_Graph * const  grafptr,  \
SCOTCH_Mapping * const      mappptr,  \
const int * const           fileptr,  \
int * const                 revaptr), \
(grafptr, mappptr, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHMAPLOAD)) ": cannot duplicate handle");
    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "r")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHMAPLOAD)) ": cannot open input stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_graphMapLoad (grafptr, mappptr, stream);

  fclose (stream);                                /* This closes file descriptor too */

  *revaptr = o;
}

/*
**
*/

SCOTCH_FORTRAN (                      \
GRAPHMAPSAVE, graphmapsave, (         \
const SCOTCH_Graph * const  grafptr,  \
SCOTCH_Mapping * const      mappptr,  \
const int * const           fileptr,  \
int * const                 revaptr), \
(grafptr, mappptr, fileptr, revaptr))
{
  FILE *              stream;                     /* Stream to build from handle */
  int                 filenum;                    /* Duplicated handle           */
  int                 o;

  if ((filenum = dup (*fileptr)) < 0) {           /* If cannot duplicate file descriptor */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHMAPSAVE)) ": cannot duplicate handle");

    *revaptr = 1;                                 /* Indicate error */
    return;
  }
  if ((stream = fdopen (filenum, "w")) == NULL) { /* Build stream from handle */
    errorPrint (STRINGIFY (SCOTCH_NAME_PUBLICFU (GRAPHMAPSAVE)) ": cannot open output stream");
    close      (filenum);
    *revaptr = 1;
    return;
  }

  o = SCOTCH_graphMapSave (grafptr, mappptr, stream);

  fclose (stream);                                /* This closes filenum too */

  *revaptr = o;
}
