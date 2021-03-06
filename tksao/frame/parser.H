/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     REAL = 258,
     INT = 259,
     STRING = 260,
     POINTER = 261,
     ANGDEGREE = 262,
     ANGRADIAN = 263,
     SEXSTR = 264,
     HMSSTR = 265,
     DMSSTR = 266,
     ABOUT_ = 267,
     AIP_ = 268,
     ALLOC_ = 269,
     ALLOCGZ_ = 270,
     ALIGN_ = 271,
     ALL_ = 272,
     ALT_ = 273,
     AMPLIFIER_ = 274,
     ANALYSIS_ = 275,
     ANGLE_ = 276,
     ANNULUS_ = 277,
     APPEND_ = 278,
     ARCMIN_ = 279,
     ARCSEC_ = 280,
     ARRAY_ = 281,
     ARROW_ = 282,
     ASINH_ = 283,
     AST_ = 284,
     AUTO_ = 285,
     AUX_ = 286,
     AVERAGE_ = 287,
     AXES_ = 288,
     AZIMUTH_ = 289,
     B1950_ = 290,
     BACK_ = 291,
     BACKGROUND_ = 292,
     BASE_ = 293,
     BBOX_ = 294,
     BEGIN_ = 295,
     BG_ = 296,
     BIG_ = 297,
     BIGENDIAN_ = 298,
     BIN_ = 299,
     BITPIX_ = 300,
     BLOCK_ = 301,
     BORDER_ = 302,
     BOX_ = 303,
     BOXANNULUS_ = 304,
     BOXCAR_ = 305,
     BOXCIRCLE_ = 306,
     BPANDA_ = 307,
     BUFFER_ = 308,
     BW_ = 309,
     CALLBACK_ = 310,
     CANVAS_ = 311,
     CATALOG_ = 312,
     CELESTRIAL_ = 313,
     CENTER_ = 314,
     CENTROID_ = 315,
     CHANNEL_ = 316,
     CIRCLE_ = 317,
     CIAO_ = 318,
     CLEAR_ = 319,
     CLIP_ = 320,
     COLOR_ = 321,
     COLORBAR_ = 322,
     COLORMAP_ = 323,
     COLORSCALE_ = 324,
     COLORSPACE_ = 325,
     COLS_ = 326,
     COLUMN_ = 327,
     COMMAND_ = 328,
     COMPASS_ = 329,
     COMPOSITE_ = 330,
     COMPRESS_ = 331,
     CONTOUR_ = 332,
     CONTRAST_ = 333,
     COORDINATES_ = 334,
     COPY_ = 335,
     COUNT_ = 336,
     CPANDA_ = 337,
     CREATE_ = 338,
     CROP_ = 339,
     CROSS_ = 340,
     CROSSHAIR_ = 341,
     CUBE_ = 342,
     CURSOR_ = 343,
     CUT_ = 344,
     CMYK_ = 345,
     DASH_ = 346,
     DASHLIST_ = 347,
     DATA_ = 348,
     DATAMIN_ = 349,
     DATASEC_ = 350,
     DEBUG_ = 351,
     DEGREES_ = 352,
     DEFAULT_ = 353,
     DELETE_ = 354,
     DEPTH_ = 355,
     DETECTOR_ = 356,
     DIAMOND_ = 357,
     DIM_ = 358,
     DS9_ = 359,
     EDIT_ = 360,
     ECLIPTIC_ = 361,
     ELEVATION_ = 362,
     ELLIPSE_ = 363,
     ELLIPSEANNULUS_ = 364,
     END_ = 365,
     ENVI_ = 366,
     EPANDA_ = 367,
     EPSILON_ = 368,
     EQUATORIAL_ = 369,
     ERASE_ = 370,
     EXT_ = 371,
     FACTOR_ = 372,
     FALSE_ = 373,
     FILE_ = 374,
     FILTER_ = 375,
     FIT_ = 376,
     FITS_ = 377,
     FITSY_ = 378,
     FIXED_ = 379,
     FK4_ = 380,
     FK4_NO_E_ = 381,
     FK5_ = 382,
     FONT_ = 383,
     FRONT_ = 384,
     FULL_ = 385,
     FUNCTION_ = 386,
     GALACTIC_ = 387,
     GAUSSIAN_ = 388,
     GET_ = 389,
     GLOBAL_ = 390,
     GRAPHICS_ = 391,
     GRAY_ = 392,
     GRID_ = 393,
     GZ_ = 394,
     HANDLE_ = 395,
     HAS_ = 396,
     HEAD_ = 397,
     HEADER_ = 398,
     HEIGHT_ = 399,
     HELIOECLIPTIC_ = 400,
     HIDE_ = 401,
     HIGHLITE_ = 402,
     HISTEQU_ = 403,
     HISTOGRAM_ = 404,
     HORIZONTAL_ = 405,
     ICRS_ = 406,
     ID_ = 407,
     IIS_ = 408,
     IMAGE_ = 409,
     INCLUDE_ = 410,
     INCR_ = 411,
     INFO_ = 412,
     INTEGER_ = 413,
     ITERATION_ = 414,
     IRAF_ = 415,
     IRAFMIN_ = 416,
     J2000_ = 417,
     KEY_ = 418,
     KEYWORD_ = 419,
     LABEL_ = 420,
     LENGTH_ = 421,
     LEVEL_ = 422,
     LITTLE_ = 423,
     LITTLEENDIAN_ = 424,
     LINE_ = 425,
     LINEAR_ = 426,
     LIST_ = 427,
     LOAD_ = 428,
     LOCAL_ = 429,
     LOG_ = 430,
     MACOSX_ = 431,
     MAGNIFIER_ = 432,
     MATCH_ = 433,
     MAP_ = 434,
     MARK_ = 435,
     MARKER_ = 436,
     MASK_ = 437,
     MESSAGE_ = 438,
     METHOD_ = 439,
     MINMAX_ = 440,
     MIP_ = 441,
     MMAP_ = 442,
     MMAPINCR_ = 443,
     MOSAIC_ = 444,
     MODE_ = 445,
     MOTION_ = 446,
     MOVE_ = 447,
     NAME_ = 448,
     NAN_ = 449,
     NATIVE_ = 450,
     NAXES_ = 451,
     NEW_ = 452,
     NEXT_ = 453,
     NO_ = 454,
     NONE_ = 455,
     NOW_ = 456,
     NRRD_ = 457,
     NUMBER_ = 458,
     OBJECT_ = 459,
     OFF_ = 460,
     ON_ = 461,
     ONLY_ = 462,
     OPTION_ = 463,
     ORIENT_ = 464,
     PAN_ = 465,
     PANNER_ = 466,
     PARSER_ = 467,
     PASTE_ = 468,
     PERF_ = 469,
     PHOTO_ = 470,
     PHYSICAL_ = 471,
     PIXEL_ = 472,
     PLOT2D_ = 473,
     PLOT3D_ = 474,
     POINT_ = 475,
     POINTER_ = 476,
     POLYGON_ = 477,
     POSTSCRIPT_ = 478,
     POW_ = 479,
     PRINT_ = 480,
     PRESERVE_ = 481,
     PROJECTION_ = 482,
     PROPERTY_ = 483,
     PUBLICATION_ = 484,
     PROS_ = 485,
     QUERY_ = 486,
     RADIAL_ = 487,
     RADIUS_ = 488,
     REGION_ = 489,
     REPLACE_ = 490,
     RESAMPLE_ = 491,
     RESET_ = 492,
     RESOLUTION_ = 493,
     RGB_ = 494,
     ROOT_ = 495,
     ROTATE_ = 496,
     RULER_ = 497,
     SAMPLE_ = 498,
     SAOIMAGE_ = 499,
     SAOTNG_ = 500,
     SAVE_ = 501,
     SCALE_ = 502,
     SCAN_ = 503,
     SCIENTIFIC_ = 504,
     SCOPE_ = 505,
     SEGMENT_ = 506,
     SELECT_ = 507,
     SET_ = 508,
     SEXAGESIMAL_ = 509,
     SHAPE_ = 510,
     SHARED_ = 511,
     SHIFT_ = 512,
     SHMID_ = 513,
     SHOW_ = 514,
     SINH_ = 515,
     SIZE_ = 516,
     SLICE_ = 517,
     SMMAP_ = 518,
     SMOOTH_ = 519,
     SOCKET_ = 520,
     SOCKETGZ_ = 521,
     SOURCE_ = 522,
     SQRT_ = 523,
     SQUARED_ = 524,
     SSHARED_ = 525,
     STATS_ = 526,
     STATUS_ = 527,
     SUPERGALACTIC_ = 528,
     SUM_ = 529,
     SYSTEM_ = 530,
     TABLE_ = 531,
     TAG_ = 532,
     TEMPLATE_ = 533,
     TEXT_ = 534,
     THREADS_ = 535,
     THREED_ = 536,
     THRESHOLD_ = 537,
     THICK_ = 538,
     TRANSPARENCY_ = 539,
     TO_ = 540,
     TOGGLE_ = 541,
     TOPHAT_ = 542,
     TRUE_ = 543,
     TYPE_ = 544,
     UNDO_ = 545,
     UNHIGHLITE_ = 546,
     UNLOAD_ = 547,
     UNSELECT_ = 548,
     UPDATE_ = 549,
     USER_ = 550,
     VALUE_ = 551,
     VAR_ = 552,
     VIEW_ = 553,
     VECTOR_ = 554,
     VERSION_ = 555,
     VERTEX_ = 556,
     VERTICAL_ = 557,
     WARP_ = 558,
     WCS_ = 559,
     WCSA_ = 560,
     WCSB_ = 561,
     WCSC_ = 562,
     WCSD_ = 563,
     WCSE_ = 564,
     WCSF_ = 565,
     WCSG_ = 566,
     WCSH_ = 567,
     WCSI_ = 568,
     WCSJ_ = 569,
     WCSK_ = 570,
     WCSL_ = 571,
     WCSM_ = 572,
     WCSN_ = 573,
     WCSO_ = 574,
     WCSP_ = 575,
     WCSQ_ = 576,
     WCSR_ = 577,
     WCSS_ = 578,
     WCST_ = 579,
     WCSU_ = 580,
     WCSV_ = 581,
     WCSW_ = 582,
     WCSX_ = 583,
     WCSY_ = 584,
     WCSZ_ = 585,
     WCS0_ = 586,
     WFPC2_ = 587,
     WIDTH_ = 588,
     WIN32_ = 589,
     XML_ = 590,
     XY_ = 591,
     YES_ = 592,
     ZMAX_ = 593,
     ZSCALE_ = 594,
     ZOOM_ = 595
   };
#endif
/* Tokens.  */
#define REAL 258
#define INT 259
#define STRING 260
#define POINTER 261
#define ANGDEGREE 262
#define ANGRADIAN 263
#define SEXSTR 264
#define HMSSTR 265
#define DMSSTR 266
#define ABOUT_ 267
#define AIP_ 268
#define ALLOC_ 269
#define ALLOCGZ_ 270
#define ALIGN_ 271
#define ALL_ 272
#define ALT_ 273
#define AMPLIFIER_ 274
#define ANALYSIS_ 275
#define ANGLE_ 276
#define ANNULUS_ 277
#define APPEND_ 278
#define ARCMIN_ 279
#define ARCSEC_ 280
#define ARRAY_ 281
#define ARROW_ 282
#define ASINH_ 283
#define AST_ 284
#define AUTO_ 285
#define AUX_ 286
#define AVERAGE_ 287
#define AXES_ 288
#define AZIMUTH_ 289
#define B1950_ 290
#define BACK_ 291
#define BACKGROUND_ 292
#define BASE_ 293
#define BBOX_ 294
#define BEGIN_ 295
#define BG_ 296
#define BIG_ 297
#define BIGENDIAN_ 298
#define BIN_ 299
#define BITPIX_ 300
#define BLOCK_ 301
#define BORDER_ 302
#define BOX_ 303
#define BOXANNULUS_ 304
#define BOXCAR_ 305
#define BOXCIRCLE_ 306
#define BPANDA_ 307
#define BUFFER_ 308
#define BW_ 309
#define CALLBACK_ 310
#define CANVAS_ 311
#define CATALOG_ 312
#define CELESTRIAL_ 313
#define CENTER_ 314
#define CENTROID_ 315
#define CHANNEL_ 316
#define CIRCLE_ 317
#define CIAO_ 318
#define CLEAR_ 319
#define CLIP_ 320
#define COLOR_ 321
#define COLORBAR_ 322
#define COLORMAP_ 323
#define COLORSCALE_ 324
#define COLORSPACE_ 325
#define COLS_ 326
#define COLUMN_ 327
#define COMMAND_ 328
#define COMPASS_ 329
#define COMPOSITE_ 330
#define COMPRESS_ 331
#define CONTOUR_ 332
#define CONTRAST_ 333
#define COORDINATES_ 334
#define COPY_ 335
#define COUNT_ 336
#define CPANDA_ 337
#define CREATE_ 338
#define CROP_ 339
#define CROSS_ 340
#define CROSSHAIR_ 341
#define CUBE_ 342
#define CURSOR_ 343
#define CUT_ 344
#define CMYK_ 345
#define DASH_ 346
#define DASHLIST_ 347
#define DATA_ 348
#define DATAMIN_ 349
#define DATASEC_ 350
#define DEBUG_ 351
#define DEGREES_ 352
#define DEFAULT_ 353
#define DELETE_ 354
#define DEPTH_ 355
#define DETECTOR_ 356
#define DIAMOND_ 357
#define DIM_ 358
#define DS9_ 359
#define EDIT_ 360
#define ECLIPTIC_ 361
#define ELEVATION_ 362
#define ELLIPSE_ 363
#define ELLIPSEANNULUS_ 364
#define END_ 365
#define ENVI_ 366
#define EPANDA_ 367
#define EPSILON_ 368
#define EQUATORIAL_ 369
#define ERASE_ 370
#define EXT_ 371
#define FACTOR_ 372
#define FALSE_ 373
#define FILE_ 374
#define FILTER_ 375
#define FIT_ 376
#define FITS_ 377
#define FITSY_ 378
#define FIXED_ 379
#define FK4_ 380
#define FK4_NO_E_ 381
#define FK5_ 382
#define FONT_ 383
#define FRONT_ 384
#define FULL_ 385
#define FUNCTION_ 386
#define GALACTIC_ 387
#define GAUSSIAN_ 388
#define GET_ 389
#define GLOBAL_ 390
#define GRAPHICS_ 391
#define GRAY_ 392
#define GRID_ 393
#define GZ_ 394
#define HANDLE_ 395
#define HAS_ 396
#define HEAD_ 397
#define HEADER_ 398
#define HEIGHT_ 399
#define HELIOECLIPTIC_ 400
#define HIDE_ 401
#define HIGHLITE_ 402
#define HISTEQU_ 403
#define HISTOGRAM_ 404
#define HORIZONTAL_ 405
#define ICRS_ 406
#define ID_ 407
#define IIS_ 408
#define IMAGE_ 409
#define INCLUDE_ 410
#define INCR_ 411
#define INFO_ 412
#define INTEGER_ 413
#define ITERATION_ 414
#define IRAF_ 415
#define IRAFMIN_ 416
#define J2000_ 417
#define KEY_ 418
#define KEYWORD_ 419
#define LABEL_ 420
#define LENGTH_ 421
#define LEVEL_ 422
#define LITTLE_ 423
#define LITTLEENDIAN_ 424
#define LINE_ 425
#define LINEAR_ 426
#define LIST_ 427
#define LOAD_ 428
#define LOCAL_ 429
#define LOG_ 430
#define MACOSX_ 431
#define MAGNIFIER_ 432
#define MATCH_ 433
#define MAP_ 434
#define MARK_ 435
#define MARKER_ 436
#define MASK_ 437
#define MESSAGE_ 438
#define METHOD_ 439
#define MINMAX_ 440
#define MIP_ 441
#define MMAP_ 442
#define MMAPINCR_ 443
#define MOSAIC_ 444
#define MODE_ 445
#define MOTION_ 446
#define MOVE_ 447
#define NAME_ 448
#define NAN_ 449
#define NATIVE_ 450
#define NAXES_ 451
#define NEW_ 452
#define NEXT_ 453
#define NO_ 454
#define NONE_ 455
#define NOW_ 456
#define NRRD_ 457
#define NUMBER_ 458
#define OBJECT_ 459
#define OFF_ 460
#define ON_ 461
#define ONLY_ 462
#define OPTION_ 463
#define ORIENT_ 464
#define PAN_ 465
#define PANNER_ 466
#define PARSER_ 467
#define PASTE_ 468
#define PERF_ 469
#define PHOTO_ 470
#define PHYSICAL_ 471
#define PIXEL_ 472
#define PLOT2D_ 473
#define PLOT3D_ 474
#define POINT_ 475
#define POINTER_ 476
#define POLYGON_ 477
#define POSTSCRIPT_ 478
#define POW_ 479
#define PRINT_ 480
#define PRESERVE_ 481
#define PROJECTION_ 482
#define PROPERTY_ 483
#define PUBLICATION_ 484
#define PROS_ 485
#define QUERY_ 486
#define RADIAL_ 487
#define RADIUS_ 488
#define REGION_ 489
#define REPLACE_ 490
#define RESAMPLE_ 491
#define RESET_ 492
#define RESOLUTION_ 493
#define RGB_ 494
#define ROOT_ 495
#define ROTATE_ 496
#define RULER_ 497
#define SAMPLE_ 498
#define SAOIMAGE_ 499
#define SAOTNG_ 500
#define SAVE_ 501
#define SCALE_ 502
#define SCAN_ 503
#define SCIENTIFIC_ 504
#define SCOPE_ 505
#define SEGMENT_ 506
#define SELECT_ 507
#define SET_ 508
#define SEXAGESIMAL_ 509
#define SHAPE_ 510
#define SHARED_ 511
#define SHIFT_ 512
#define SHMID_ 513
#define SHOW_ 514
#define SINH_ 515
#define SIZE_ 516
#define SLICE_ 517
#define SMMAP_ 518
#define SMOOTH_ 519
#define SOCKET_ 520
#define SOCKETGZ_ 521
#define SOURCE_ 522
#define SQRT_ 523
#define SQUARED_ 524
#define SSHARED_ 525
#define STATS_ 526
#define STATUS_ 527
#define SUPERGALACTIC_ 528
#define SUM_ 529
#define SYSTEM_ 530
#define TABLE_ 531
#define TAG_ 532
#define TEMPLATE_ 533
#define TEXT_ 534
#define THREADS_ 535
#define THREED_ 536
#define THRESHOLD_ 537
#define THICK_ 538
#define TRANSPARENCY_ 539
#define TO_ 540
#define TOGGLE_ 541
#define TOPHAT_ 542
#define TRUE_ 543
#define TYPE_ 544
#define UNDO_ 545
#define UNHIGHLITE_ 546
#define UNLOAD_ 547
#define UNSELECT_ 548
#define UPDATE_ 549
#define USER_ 550
#define VALUE_ 551
#define VAR_ 552
#define VIEW_ 553
#define VECTOR_ 554
#define VERSION_ 555
#define VERTEX_ 556
#define VERTICAL_ 557
#define WARP_ 558
#define WCS_ 559
#define WCSA_ 560
#define WCSB_ 561
#define WCSC_ 562
#define WCSD_ 563
#define WCSE_ 564
#define WCSF_ 565
#define WCSG_ 566
#define WCSH_ 567
#define WCSI_ 568
#define WCSJ_ 569
#define WCSK_ 570
#define WCSL_ 571
#define WCSM_ 572
#define WCSN_ 573
#define WCSO_ 574
#define WCSP_ 575
#define WCSQ_ 576
#define WCSR_ 577
#define WCSS_ 578
#define WCST_ 579
#define WCSU_ 580
#define WCSV_ 581
#define WCSW_ 582
#define WCSX_ 583
#define WCSY_ 584
#define WCSZ_ 585
#define WCS0_ 586
#define WFPC2_ 587
#define WIDTH_ 588
#define WIN32_ 589
#define XML_ 590
#define XY_ 591
#define YES_ 592
#define ZMAX_ 593
#define ZSCALE_ 594
#define ZOOM_ 595




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 51 "frame/parser.Y"
{
#define FRBUFSIZE 4096
  char chr;
  char str[FRBUFSIZE];
  void* ptr;
  int integer;
  double real;
  double vector[3];
  int dash[2];
}
/* Line 1529 of yacc.c.  */
#line 740 "frame/parser.H"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



