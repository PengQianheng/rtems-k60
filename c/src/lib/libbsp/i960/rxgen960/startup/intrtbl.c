/*-------------------------------------*/
/* intrtbl.c                           */
/* Last change : 12.10.94              */
/*-------------------------------------*/
/*
 *  $Id$
 */

#include "ihandler.h"
#include "intrtbl.h"
/*-------------------------------------*/

  /* Interrupt Table. Dedicated Interrupts are cached.
   * So NMI handler has to be defined here.
   */
InterruptTbl interruptTbl = {
  0,					/* Pending Priorities */
  0, 0, 0, 0, 0, 0, 0, 0,		/* Pending Interrupts */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*   8 -  15 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  16 -  23 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  24 -  31 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  32 -  39 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  40 -  47 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  48 -  55 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  56 -  63 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  64 -  71 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  72 -  79 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  80 -  87 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  88 -  95 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/*  96 - 103 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 104 - 111 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 112 - 119 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 120 - 127 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 128 - 135 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 136 - 143 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 144 - 151 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 152 - 159 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 160 - 167 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 168 - 175 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 176 - 183 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 184 - 191 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 192 - 199 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 200 - 207 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 208 - 215 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 216 - 223 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 224 - 231 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 232 - 239 */
  0, 0, 0, 0, 0, 0, 0, 0, 		/* 240 - 247 */
  nmiHandler + NORMAL_IH,		/* 248 : NMI handler */
     0, 0, 0, 0, 0, 0, 0, 		/* 249 - 255 */

};
/*-------------*/
/* End of file */
/*-------------*/
