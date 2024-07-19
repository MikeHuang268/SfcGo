
#include "stdafx.h"




#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <limits.h>

#include "sgftree.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


#if TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#define STRICT_SGF 's'
#define LAX_SGF    'l'

/* Set this to 1 if you want warnings for missing GM and FF properties. */
#define VERBOSE_WARNINGS 0



#ifdef HAVE_GLIB_H
#include <glib.h>
#endif

/* Avoid compiler warnings with unused parameters */
#define UNUSED(x)  (void)x

/* Define TERMINFO or ANSI_COLOR to enable coloring of pieces.
 * This is normally done in config.h.
 */

 /* enabling color */

 /* linux console :
  *  0=black
  *  1=red
  *  2=green
  *  3=yellow/brown
  *  4=blue
  *  5=magenta
  *  6=cyan
  *  7=white
  */
#ifdef TERMINFO

#ifdef _AIX
#define _TPARM_COMPAT
#endif

#if HAVE_CURSES_H
#include <curses.h>
#elif HAVE_NCURSES_CURSES_H
#include <ncurses/curses.h>
#else
#endif

#if HAVE_TERM_H
#include <term.h>
#elif HAVE_NCURSES_TERM_H
#include <ncurses/term.h>
#else
#endif


  /* terminfo attributes */
static char* setaf;		/* terminfo string to set color */
static char* op;		/* terminfo string to reset colors */

static int init = 0;

#endif /* TERMINFO */

/* for gg_cputime */

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_SYS_TIMES_H
#include <sys/times.h>
#elif defined(WIN32)
#include <windows.h>
#endif





 /* Algorithm parameters. */
#define N 25
static const int m = 7;
static const int s = 7;
static const int t = 15;
static const unsigned int a = 0x8ebfd028U;
static const unsigned int b = 0x2b5b2500U;
static const unsigned int c = 0xdb8b0000U;


/* Global state for the random number generator. */
static unsigned int x[N];
static int k;


/* Set when properly seeded. */
static int rand_initialized = 0;

/* We use this to detect whether unsigned ints are bigger than 32
 * bits. If they are we need to clear higher order bits, otherwise we
 * can optimize by not doing the masking.
 */
#define BIG_UINT (UINT_MAX > 0xffffffffU)


 /* Iterate the TGFSR once to get a new state which can be used to
  * produce another 25 random numbers.
  */

static void
iterate_tgfsr(void)
{
    int i;
    for (i = 0; i < N - m; i++)
        x[i] = x[i + m] ^ (x[i] >> 1) ^ ((x[i] & 1) ? a : 0);
    for (; i < N; i++)
        x[i] = x[i + m - N] ^ (x[i] >> 1) ^ ((x[i] & 1) ? a : 0);
}


/* Produce a random number from the next word of the internal state.
 */

static unsigned int
next_rand(void)
{
    int y;
    if (!rand_initialized) {
        assert(rand_initialized); /* Abort. */
        gg_srand(1);              /* Initialize silently if assertions disabled. */
    }
    if (++k == N) {
        iterate_tgfsr();
        k = 0;
    }
    y = x[k] ^ ((x[k] << s) & b);
    y ^= ((y << t) & c);
#if BIG_UINT
    y &= 0xffffffffU;
#endif
    return y;
}


/* Seed the random number generator. The first word of the internal
 * state is set by the (lower) 32 bits of seed. The remaining 24 words
 * are generated from the first one by a linear congruential pseudo
 * random generator.
 *
 * FIXME: The constants in this generator has not been checked, but
 * since they only are used to produce a very short sequence, which in
 * turn only is a seed to a stronger generator, it probably doesn't
 * matter much.
 */

void
gg_srand(unsigned int seed)
{
    int i;
    for (i = 0; i < N; i++) {
#if BIG_UINT
        seed &= 0xffffffffU;
#endif
        x[i] = seed;
        seed *= 1313;
        seed += 88897;
    }
    k = N - 1; /* Force an immediate iteration of the TGFSR. */
    rand_initialized = 1;
}


/* Obtain one random integer value in the interval [0, 2^31-1].
 */

int
gg_rand(void)
{
    return (int)(next_rand() & 0x7fffffff);
}


/* Obtain one random integer value in the interval [0, 2^32-1].
 */

unsigned int
gg_urand(void)
{
    return next_rand();
}


/* Obtain one random floating point value in the half open interval
 * [0.0, 1.0).
 *
 * If the value is converted to a floating point type with less than
 * 32 bits mantissa (or if the double type should happen to be
 * unusually short), the value 1.0 may be attained.
 */

double
gg_drand(void)
{
    return next_rand() * 2.328306436538696e-10;
}


/* Retrieve the internal state of the random generator.
 */

void
gg_get_rand_state(struct gg_rand_state* state)
{
    int i;
    for (i = 0; i < N; i++)
        state->x[i] = x[i];
    state->k = k;
}


/* Set the internal state of the random number generator.
 */

void
gg_set_rand_state(struct gg_rand_state* state)
{
    int i;
    for (i = 0; i < N; i++)
        x[i] = state->x[i];
    k = state->k;
}


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */


//gg_utils
void
gg_init_color()
{
#ifdef TERMINFO

    /* compiler is set to make string literals  const char *
     * But system header files dont prototype things correctly.
     * These are equivalent to a non-const string literals
     */

    static char setaf_literal[] = "setaf";
    static char op_literal[] = "op";
    static char empty_literal[] = "";

    if (init)
        return;

    init = 1;

    setupterm(NULL, 2, NULL);
    setaf = tigetstr(setaf_literal);
    if (!setaf)
        setaf = empty_literal;
    op = tigetstr(op_literal);
    if (!op)
        op = empty_literal;

#endif /* TERMINFO */
}



#ifdef WIN32
#ifdef VC
#include <crtdbg.h>

verifyW32(BOOL b)
{
    if (!b) {
        _ASSERTE(0 && "Win32 Error");
        fprintf(stderr, "Win32 Err: %ld\n", GetLastError());
    }
}

#else
/* mingw32 lacks crtdbg.h and _ASSERTE */
void verifyW32(BOOL b)
{
    if (!b) {
        fprintf(stderr, "Win32 Err: %ld\n", GetLastError());
    }
}

#endif

#endif

void
write_color_char_no_space(int c, int x)
{
#ifdef TERMINFO

    fprintf(stderr, "%s%c", tparm(setaf, c, 0, 0, 0, 0, 0, 0, 0, 0), x);
    fputs(tparm(op, 0, 0, 0, 0, 0, 0, 0, 0, 0), stderr);

#elif defined(ANSI_COLOR)

    fprintf(stderr, "\033[%dm%c\033[0m", 30 + c, x);

#elif defined(WIN32)

    static HANDLE hStdErr = 0;
    DWORD iCharsWritten;
    BOOL succeed32;
    CONSOLE_SCREEN_BUFFER_INFO bufInfo;
    if (!hStdErr) {
        hStdErr = GetStdHandle(STD_ERROR_HANDLE);
        if (hStdErr == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Unable to open stderr.\n");
        }
    }

    /* Red & Blue are switched from what MS-Windows wants:
     *   FOREGROUND_BLUE      0x0001 // text color contains blue.
     *   FOREGROUND_GREEN     0x0002 // text color contains green.
     *   FOREGROUND_RED       0x0004 // text color contains red
     * This magic switches the bits back:
     */
    c = (c & 1) * 4 + (c & 2) + (c & 4) / 4;
    c += FOREGROUND_INTENSITY;
    succeed32 = GetConsoleScreenBufferInfo(hStdErr, &bufInfo);
    if (!succeed32) {  /* Probably redirecting output, just give plain text. */
        fprintf(stderr, "%c", x);
        return;
    }
    verifyW32(SetConsoleTextAttribute(hStdErr, (WORD)c));
    verifyW32(WriteConsole(hStdErr, &x, 1, &iCharsWritten, 0));
    verifyW32(SetConsoleTextAttribute(hStdErr, bufInfo.wAttributes));

#else

    fprintf(stderr, "%c", x);

#endif
}

void
write_color_string(int c, const char* str)
{
    while (*str)
        write_color_char_no_space(c, *str++);
}

void
write_color_char(int c, int x)
{
    fprintf(stderr, " ");
    write_color_char_no_space(c, x);
}

/*
 * A wrapper around vsnprintf.
 */

void
gg_vsnprintf(char* dest, unsigned long len, const char* fmt, va_list args)
{

#ifdef HAVE_VSNPRINTF
    vsnprintf(dest, len, fmt, args);
#elif HAVE_G_VSNPRINTF
    g_vsnprintf(dest, len, fmt, args);
#elif HAVE__VSNPRINTF
    _vsnprintf_s(dest, len,len, fmt, args);
#else
    UNUSED(len);
    vsprintf(dest, fmt, args);
#endif

}

void
gg_snprintf(char* dest, unsigned long len, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    gg_vsnprintf(dest, len, fmt, args);
    va_end(args);
}

/* Get the time of day, calling gettimeofday from sys/time.h
 * if available, otherwise substituting a workaround for portability.
 */

double
gg_gettimeofday(void)
{
    struct timeval tv;
#ifdef HAVE_GETTIMEOFDAY
    gettimeofday(&tv, NULL);
#else
    tv.tv_sec = time(NULL);
    tv.tv_usec = 0;
#endif
    return tv.tv_sec + 1.e-6 * tv.tv_usec;
}

const char*
gg_version(void)
{
    return VERSION;
}

/* return cputime used in secs */

double
gg_cputime(void)
{
#if HAVE_SYS_TIMES_H && HAVE_TIMES && HAVE_UNISTD_H
    struct tms t;
    times(&t);
    return (t.tms_utime + t.tms_stime + t.tms_cutime + t.tms_cstime)
        / ((double)sysconf(_SC_CLK_TCK));
#elif defined(WIN32)
    FILETIME creationTime, exitTime, kernelTime, userTime;
    ULARGE_INTEGER uKernelTime, uUserTime, uElapsedTime;
    GetProcessTimes(GetCurrentProcess(), &creationTime, &exitTime,
        &kernelTime, &userTime);
    uKernelTime.LowPart = kernelTime.dwLowDateTime;
    uKernelTime.HighPart = kernelTime.dwHighDateTime;
    uUserTime.LowPart = userTime.dwLowDateTime;
    uUserTime.HighPart = userTime.dwHighDateTime;
    uElapsedTime.QuadPart = uKernelTime.QuadPart + uUserTime.QuadPart;
    /*_ASSERTE(0 && "Debug Times");*/
    /* convert from multiples of 100nanosecs to seconds: */
    return (signed __int64)(uElapsedTime.QuadPart) * 1.e-7;
#else
    static int warned = 0;
    if (!warned) {
        fprintf(stderr, "CPU timing unavailable - returning wall time.");
        warned = 1;
    }
    /* return wall clock seconds */
    return gg_gettimeofday();
#endif
}

/* Before we sort floating point values (or just compare them) we
 * may need to normalize them. This may sound cryptic but is
 * required to avoid an obscure platform dependency.
 *
 * The underlying problem is that most fractional decimal numbers
 * can't be represented exactly in a floating point number with base
 * two. The error may be small but it is there. When such numbers
 * are added or subtracted, the errors accumulate and even if the
 * result (counting exactly) should be a number which can be
 * represented exactly, this cannot be assumed to be the case.
 *
 * To give an example of this, the computation 0.3 + 0.05 - 0.35 may
 * sum to 0, a small negative value, or a small positive value.
 * Moreover, which case we encounter depends on the number of
 * mantissa bits in the floating point type used and the exact
 * details of the floating point arithmetic on the platform.
 *
 * In the context of sorting, assume that two values both should be
 * 0.35, but one has been computed as 0.3 + 0.05 and the other
 * directly assigned 0.35. Then it depends on the platform whether
 * they compare as equal or one of them is larger than the other.
 *
 * This code normalizes the values to avoid this problem. It is
 * assumed that all values encountered are integer multiples of a.
 */
float
gg_normalize_float(float x, float a)
{
    return a * ((int)(0.5 + x / a));
}

int
gg_normalize_float2int(float x, float a)
{
    return ((int)(0.5 + x / a));
}

/* A sorting algorithm, call-compatible with the libc qsort() function.
 *
 * The reason to prefer this to standard qsort() is that quicksort is
 * an unstable sorting algorithm, i.e. the relative ordering of
 * elements with the same comparison value may change. Exactly how the
 * ordering changes depends on implementation specific details like
 * the strategy for choosing the pivot element. Thus a list with
 * "equal" values may be sorted differently between platforms, which
 * potentially can lead to significant differences in the move
 * generation.
 *
 * This is an implementation of the combsort algorithm.
 *
 * Testing shows that it is faster than the GNU libc qsort() function
 * on small data sets and within a factor of two slower for large
 * random data sets. Its performance does not degenerate for common
 * special cases (i.e. sorted or reversed data) but it seems to be
 * susceptible to O(N^2) behavior for repetitive data with specific
 * cycle lengths.
 *
 * Like qsort() this algorithm is unstable, but since the same
 * implementation (this one) is used on all platforms, the reordering
 * of equal elements will be consistent.
 */
void
gg_sort(void* base, size_t nel, size_t width,
    int (*cmp)(const void*, const void*))
{
    int gap = nel;
    int swap_made;
    char* end = (char*)base + width * (nel - 1);
    do {
        char* a, * b;
        swap_made = 0;
        gap = (10 * gap + 3) / 13;
        for (a = (char*)base, b = a + gap * width; b <= end; a += width, b += width) {
            if (cmp((void*)a, (void*)b) > 0) {
                char* c = a;
                char* d = b;
                size_t size = width;
                while (size-- > 0) {
                    char tmp = *c;
                    *c++ = *d;
                    *d++ = tmp;
                }
                swap_made = 1;
            }
        }
    } while (gap > 1 || swap_made);
}


/* Linearly interpolate f(x) from the data given in interpolation_data. */
float
gg_interpolate(struct interpolation_data* f, float x)
{
    int i;
    float ratio;
    float diff;
    if (x < f->range_lowerbound)
        return f->values[0];
    else if (x > f->range_upperbound)
        return f->values[f->sections];
    else {
        ratio = ((float)f->sections) * (x - f->range_lowerbound)
            / (f->range_upperbound - f->range_lowerbound);
        i = (int)ratio;
        diff = ratio - ((float)i);
        if (0)
            fprintf(stderr, "Floating point Ratio: %f, integer: %d, diff %f",
                ratio, i, diff);
        return ((1 - diff) * f->values[i] + diff * f->values[i + 1]);
    }
}


/* This is the simplest function that returns appr. a when a is small,
 * and approximately b when a is large.
 */
float
soft_cap(float a, float b)
{
    return ((a * b) / (a + b));
}


/* Reorientation of point (i, j) into (*ri, *rj) */
void
rotate(int i, int j, int* ri, int* rj, int bs, int rot)
{
    int bs1;
    assert(bs > 0);
    assert(ri != NULL && rj != NULL);
    assert(rot >= 0 && rot < 8);
    /* PASS case */
    if (i == -1 && j == -1) {
        *ri = i;
        *rj = j;
        return;
    }

    assert(i >= 0 && i < bs);
    assert(j >= 0 && j < bs);

    bs1 = bs - 1;
    if (rot == 0) {
        /* identity map */
        *ri = i;
        *rj = j;
    }
    else if (rot == 1) {
        /* rotation over 90 degrees */
        *ri = bs1 - j;
        *rj = i;
    }
    else if (rot == 2) {
        /* rotation over 180 degrees */
        *ri = bs1 - i;
        *rj = bs1 - j;
    }
    else if (rot == 3) {
        /* rotation over 270 degrees */
        *ri = j;
        *rj = bs1 - i;
    }
    else if (rot == 4) {
        /* flip along diagonal */
        *ri = j;
        *rj = i;
    }
    else if (rot == 5) {
        /* flip */
        *ri = bs1 - i;
        *rj = j;
    }
    else if (rot == 6) {
        /* flip along diagonal */
        *ri = bs1 - j;
        *rj = bs1 - i;
    }
    else if (rot == 7) {
        /* flip */
        *ri = i;
        *rj = bs1 - j;
    }
}

/* inverse reorientation of reorientation rot */
void
inv_rotate(int i, int j, int* ri, int* rj, int bs, int rot)
{
    /* every reorientation is it's own inverse except rotations
       over 90 and 270 degrees */
    if (rot == 1)
        rotate(i, j, ri, rj, bs, 3);
    else if (rot == 3)
        rotate(i, j, ri, rj, bs, 1);
    else
        rotate(i, j, ri, rj, bs, rot);
}


/* Intermediate layer to random.c. gg_srand() should only be called via the
 * functions below.
 */

 /* Private variable remembering the random seed. */
static unsigned int random_seed;

unsigned int
get_random_seed()
{
    return random_seed;
}

void
set_random_seed(unsigned int seed)
{
    random_seed = seed;
    gg_srand(seed);
}

/* Update the random seed. This should be called at the start of each
 * new game.
 * We reset the random seed before obtaining a new one, to make the
 * next random seed depend deterministically on the old one.
 */
void
update_random_seed(void)
{
    gg_srand(random_seed);
    random_seed = gg_rand();
    /* Since random seed 0 has a special interpretation when given as
     * command line argument with the -r option, we make sure to avoid
     * it.
     */
    if (random_seed == 0)
        random_seed = 1;
    gg_srand(random_seed);
}


/* Restart the pseudo-random sequence with the initialization given
 * by the random seed. Should be called at each move.
 */
void
reuse_random_seed()
{
    gg_srand(random_seed);
}



/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */


//sgftree
void
sgftree_clear(SGFTree* tree)
{
    tree->root = NULL;
    tree->lastnode = NULL;
}

int
sgftree_readfile(SGFTree* tree, const char* infilename)
{
    SGFNode* savetree = tree->root;

    tree->root = readsgffile(infilename);
    if (tree->root == NULL) {
        tree->root = savetree;
        return 0;
    }

    sgfFreeNode(savetree);
    tree->lastnode = NULL;
    return 1;
}


/* Go back one node in the tree. If lastnode is NULL, go to the last
 * node (the one in main variant which has no children).
 */

int
sgftreeBack(SGFTree* tree)
{
    if (tree->lastnode) {
        if (tree->lastnode->parent)
            tree->lastnode = tree->lastnode->parent;
        else
            return 0;
    }
    else
        while (sgftreeForward(tree))
            ;

    return 1;
}


/* Go forward one node in the tree. If lastnode is NULL, go to the
 * tree root.
 */

int
sgftreeForward(SGFTree* tree)
{
    if (tree->lastnode) {
        if (tree->lastnode->child)
            tree->lastnode = tree->lastnode->child;
        else
            return 0;
    }
    else
        tree->lastnode = tree->root;

    return 1;
}


/* ================================================================ */
/*                        High level functions                      */
/* ================================================================ */

/*
 * Returns the node to modify. Use lastnode if available, otherwise
 * follow the main variation to the current end of the game.
 */

SGFNode*
sgftreeNodeCheck(SGFTree* tree)
{
    SGFNode* node = NULL;
    assert(tree->root);

    if (tree->lastnode)
        node = tree->lastnode;
    else {
        node = tree->root;
        while (node->child)
            node = node->child;
    }

    return node;
}


/*
 * Add a stone to the current or the given node.
 * Return the node where the stone was added.
 */

void
sgftreeAddStone(SGFTree* tree, int color, int movex, int movey)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfAddStone(node, color, movex, movey);
}


/*
 * Add a move to the gametree.
 */

void
sgftreeAddPlay(SGFTree* tree, int color, int movex, int movey)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    tree->lastnode = sgfAddPlay(node, color, movex, movey);
}


/*
 * Add a move to the gametree. New variations are added after the old
 * ones rather than before.
 */

void
sgftreeAddPlayLast(SGFTree* tree, int color, int movex, int movey)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    tree->lastnode = sgfAddPlayLast(node, color, movex, movey);
}


void
sgftreeCreateHeaderNode(SGFTree* tree, int boardsize, float komi, int handicap)
{
    SGFNode* root = sgfNewNode();

    sgfAddPropertyInt(root, "SZ", boardsize);
    sgfAddPropertyFloat(root, "KM", komi);
    sgfAddPropertyInt(root, "HA", handicap);
    tree->root = root;
    tree->lastnode = root;
}


/*
 * Add a comment to a gametree.
 */

void
sgftreeAddComment(SGFTree* tree, const char* comment)
{
    SGFNode* node;
    assert(tree && tree->root);

    node = sgftreeNodeCheck(tree);
    sgfAddComment(node, comment);
}


/*
 * Place text on the board at position (i, j).
 */

void
sgftreeBoardText(SGFTree* tree, int i, int j, const char* text)
{
    SGFNode* node;
    assert(tree->root);

    node = sgftreeNodeCheck(tree);
    sgfBoardText(node, i, j, text);
}


/*
 * Place a character on the board at position (i, j).
 */

void
sgftreeBoardChar(SGFTree* tree, int i, int j, char c)
{
    SGFNode* node;
    assert(tree->root);

    node = sgftreeNodeCheck(tree);
    sgfBoardChar(node, i, j, c);
}


/*
 * Place a number on the board at position (i, j).
 */

void
sgftreeBoardNumber(SGFTree* tree, int i, int j, int number)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfBoardNumber(node, i, j, number);
}


/*
 * Place a circle mark on the board at position (i, j).
 */

void
sgftreeTriangle(SGFTree* tree, int i, int j)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfTriangle(node, i, j);
}


/*
 * Place a circle mark on the board at position (i, j).
 */

void
sgftreeCircle(SGFTree* tree, int i, int j)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfCircle(node, i, j);
}


/*
 * Place a square mark on the board at position (i, j).
 */

void
sgftreeSquare(SGFTree* tree, int i, int j)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfSquare(node, i, j);
}


/*
 * Place a (square) mark on the board at position (i, j).
 */

void
sgftreeMark(SGFTree* tree, int i, int j)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    sgfMark(node, i, j);
}


/*
 * Start a new variant.
 */

void
sgftreeStartVariant(SGFTree* tree)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    tree->lastnode = sgfStartVariant(node);
}


/*
 * Start a new variant as first child.
 */

void
sgftreeStartVariantFirst(SGFTree* tree)
{
    SGFNode* node = sgftreeNodeCheck(tree);
    tree->lastnode = sgfStartVariantFirst(node);
}


/*
 * Write result of the game to the game tree.
 */

void
sgftreeWriteResult(SGFTree* tree, float score, int overwrite)
{
    assert(tree->root);

    sgfWriteResult(tree->root, score, overwrite);
}


void
sgftreeSetLastNode(SGFTree* tree, SGFNode* last_node)
{
    tree->lastnode = last_node;
}


/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
  * This is GNU Go, a Go program. Contact gnugo@gnu.org, or see       *
  * http://www.gnu.org/software/gnugo/ for more information.          *
  *                                                                   *
  * Copyright 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007,   *
  * 2008 and 2009 by the Free Software Foundation.                    *
  *                                                                   *
  * This program is free software; you can redistribute it and/or     *
  * modify it under the terms of the GNU General Public License as    *
  * published by the Free Software Foundation - version 3 or          *
  * (at your option) any later version.                               *
  *                                                                   *
  * This program is distributed in the hope that it will be useful,   *
  * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
  * GNU General Public License in file COPYING for more details.      *
  *                                                                   *
  * You should have received a copy of the GNU General Public         *
  * License along with this program; if not, write to the Free        *
  * Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
  * Boston, MA 02111, USA.                                            *
 \* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 /*  Parts of this code were given to us by Tommy Thorn */

/* ================================================================ */
/*                     Some utility functions.                      */
/* ================================================================ */

/*
 * Utility: a checking, initializing malloc
 */

void*
xalloc(unsigned int size)
{
    void* pt = malloc(size);

    if (!pt) {
        fprintf(stderr, "xalloc: Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    memset(pt, 0, (unsigned long)size);
    return pt;
}

void*
xrealloc(void* pt, unsigned int size)
{
    void* ptnew = realloc(pt, size);

    if (!ptnew) {
        fprintf(stderr, "xrealloc: Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    return ptnew;
}


/* ================================================================ */
/*                           SGF Nodes                              */
/* ================================================================ */


/*
 * Allocate memory for a new SGF node.
 */

SGFNode*
sgfNewNode()
{
    SGFNode* newnode;
    newnode = (
        SGFNode*)xalloc(sizeof(SGFNode));
    newnode->next = NULL;
    newnode->props = NULL;
    newnode->parent = NULL;
    newnode->child = NULL;
    return newnode;
}

/*
 * Recursively free an sgf node
 */

void
sgfFreeNode(SGFNode* node)
{
    if (node == NULL)
        return;
    sgfFreeNode(node->next);
    sgfFreeNode(node->child);
    sgfFreeProperty(node->props);
    free(node);
}


/*
 * Add a generic text property to an SGF node.
 */

void
sgfAddProperty(SGFNode* node, const char* name, const char* value)
{
    SGFProperty* prop = node->props;

    if (prop)
        while (prop->next)
            prop = prop->next;

    sgfMkProperty(name, value, node, prop);
}


/*
 * Add an integer property to an SGF node.
 */

void
sgfAddPropertyInt(SGFNode* node, const char* name, long val)
{
    char buffer[10];

    gg_snprintf(buffer, 10, "%ld", val);
    sgfAddProperty(node, name, buffer);
}


/*
 * Add a float property to an SGF node.
 */

void
sgfAddPropertyFloat(SGFNode* node, const char* name, float val)
{
    char buffer[10];

    gg_snprintf(buffer, 10, "%3.1f", val);
    sgfAddProperty(node, name, buffer);
}


/*
 * Read a property as int from an SGF node.
 */

int
sgfGetIntProperty(SGFNode* node, const char* name, int* value)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            *value = atoi(prop->value);
            return 1;
        }

    return 0;
}


/*
 * Read a property as float from an SGF node.
 */

int
sgfGetFloatProperty(SGFNode* node, const char* name, float* value)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            *value = (float)atof(prop->value);
            /* MS-C warns of loss of data (double to float) */
            return 1;
        }

    return 0;
}


/*
 * Read a property as text from an SGF node.
 */

int
sgfGetCharProperty(SGFNode* node, const char* name, char** value)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            *value = prop->value;
            return 1;
        }

    return 0;
}


/*
 * Is there a property of this type in the node?
 */

static int
sgfHasProperty(SGFNode* node, const char* name)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam)
            return 1;

    return 0;
}


/*
 * Overwrite a property from an SGF node with text or create a new
 * one if it does not exist.
 */

void
sgfOverwriteProperty(SGFNode* node, const char* name, const char* text)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            prop->value = (char*)xrealloc(prop->value, strlen(text) + 1);
            strcpy(prop->value,text);
            return;
        }

    sgfAddProperty(node, name, text);
}


/*
 * Overwrite an int property in an SGF node with val or create a new
 * one if it does not exist.
 */

void
sgfOverwritePropertyInt(SGFNode* node, const char* name, int val)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            prop->value = (char*)xrealloc(prop->value, 12);
            gg_snprintf(prop->value, 12, "%d", val);
            return;
        }

    sgfAddPropertyInt(node, name, val);
}


/*
 * Overwrite a float property in the gametree with val or create
 * a new one if it does not exist.
 */

void
sgfOverwritePropertyFloat(SGFNode* node, const char* name, float val)
{
    SGFProperty* prop;
    short nam = name[0] | name[1] << 8;

    for (prop = node->props; prop; prop = prop->next)
        if (prop->name == nam) {
            prop->value = (char*)xrealloc(prop->value, 15);
            gg_snprintf(prop->value, 15, "%3.1f", val);
            return;
        }

    sgfAddPropertyFloat(node, name, val);
}


/*
 * Goto previous node.
 */

SGFNode*
sgfPrev(SGFNode* node)
{
    SGFNode* q;
    SGFNode* prev;

    if (!node->parent)
        return NULL;

    q = node->parent->child;
    prev = NULL;
    while (q && q != node) {
        prev = q;
        q = q->next;
    }

    return prev;
}


/*
 * Goto root node.
 */

SGFNode*
sgfRoot(SGFNode* node)
{
    while (node->parent)
        node = node->parent;

    return node;
}


/* ================================================================ */
/*                         SGF Properties                           */
/* ================================================================ */


/*
 * Make an SGF property.
 */
static SGFProperty*
do_sgf_make_property(short sgf_name, const char* value,
    SGFNode* node, SGFProperty* last)
{
    SGFProperty* prop;

    prop = (SGFProperty*)xalloc(sizeof(SGFProperty));
    prop->name = sgf_name;
    prop->value = (char*)xalloc(strlen(value) + 1);
    strcpy(prop->value, value);
    prop->next = NULL;

    if (last == NULL)
        node->props = prop;
    else
        last->next = prop;

    return prop;
}


/* Make an SGF property.  In case of a property with a range it
 * expands it and makes several properties instead.
 */
SGFProperty*
sgfMkProperty(const char* name, const  char* value,
    SGFNode* node, SGFProperty* last)
{
    static const short properties_allowing_ranges[12] = {
        /* Board setup properties. */
        SGFAB, SGFAW, SGFAE,

        /* Markup properties. */
        SGFCR, SGFMA, SGFSQ, SGFTR, SGFDD, SGFSL,

        /* Miscellaneous properties. */
        SGFVW,

        /* Go-specific properties. */
        SGFTB, SGFTW
    };

    int k;
    short sgf_name;

    if (strlen(name) == 1)
        sgf_name = name[0] | (short)(' ' << 8);
    else
        sgf_name = name[0] | name[1] << 8;

    for (k = 0; k < 12; k++) {
        if (properties_allowing_ranges[k] == sgf_name)
            break;
    }

    if (k < 12
        && strlen(value) == 5
        && value[2] == ':') {
        char x1 = value[0];
        char y1 = value[1];
        char x2 = value[3];
        char y2 = value[4];
        char new_value[] = "xy";

        if (x1 <= x2 && y1 <= y2) {
            for (new_value[0] = x1; new_value[0] <= x2; new_value[0]++) {
                for (new_value[1] = y1; new_value[1] <= y2; new_value[1]++)
                    last = do_sgf_make_property(sgf_name, new_value, node, last);
            }

            return last;
        }
    }

    /* Not a range property. */
    return do_sgf_make_property(sgf_name, value, node, last);
}


/*
 * Recursively free an SGF property.
 *
 */

void
sgfFreeProperty(SGFProperty* prop)
{
    if (prop == NULL)
        return;
    sgfFreeProperty(prop->next);
    free(prop->value);
    free(prop);
}


/* ================================================================ */
/*                        High level functions                      */
/* ================================================================ */


/*
 * Add a stone to the current or the given node.
 * Return the node where the stone was added.
 */

SGFNode*
sgfAddStone(SGFNode* node, int color, int movex, int movey)
{
    char move[3];

    sprintf_s(move, "%c%c", movey + 'a', movex + 'a');
    sgfAddProperty(node, (color == BLACK) ? "AB" : "AW", move);

    return node;
}


/*
 * Add a move to the gametree.
 */

SGFNode*
sgfAddPlay(SGFNode* node, int who, int movex, int movey)
{
    char move[3];
    SGFNode* new1;

    /* a pass move? */
    if (movex == -1 && movey == -1)
        move[0] = 0;
    else
        sprintf_s(move, "%c%c", movey + 'a', movex + 'a');

    if (node->child)
        new1 = sgfStartVariantFirst(node->child);
    else {
        new1 = sgfNewNode();
        node->child = new1;
        new1->parent = node;
    }

    sgfAddProperty(new1, (who == BLACK) ? "B" : "W", move);

    return new1;
}


/*
 * Add a move to the gametree. New variations are added after the old
 * ones rather than before.
 */

SGFNode*
sgfAddPlayLast(SGFNode* node, int who, int movex, int movey)
{
    char move[3];
    SGFNode* new1;

    /* a pass move? */
    if (movex == -1 && movey == -1)
        move[0] = 0;
    else
        sprintf_s(move, "%c%c", movey + 'a', movex + 'a');

    new1 = sgfAddChild(node);
    sgfAddProperty(new1, (who == BLACK) ? "B" : "W", move);

    return new1;
}


SGFNode*
sgfCreateHeaderNode(int boardsize, float komi, int handicap)
{
    SGFNode* root = sgfNewNode();

    sgfAddPropertyInt(root, "SZ", boardsize);
    sgfAddPropertyFloat(root, "KM", komi);
    sgfAddPropertyInt(root, "HA", handicap);

    return root;
}


/*
 * Add a comment to an SGF node.
 */

SGFNode*
sgfAddComment(SGFNode* node, const char* comment)
{
    sgfAddProperty(node, "C ", comment);

    return node;
}


/*
 * Place text on the board at position (i, j).
 */

SGFNode*
sgfBoardText(SGFNode* node, int i, int j, const char* text)
{
    void* str = xalloc(strlen(text) + 3);

    sprintf((char*)str, "%c%c:%s", j + 'a', i + 'a', text);
    sgfAddProperty(node, "LB", (char*)str);
    free(str);

    return node;
}


/*
 * Place a character on the board at position (i, j).
 */

SGFNode*
sgfBoardChar(SGFNode* node, int i, int j, char c)
{
    char text[2] = "";

    text[0] = c;
    text[1] = 0;

    return sgfBoardText(node, i, j, text);
}


/*
 * Place a number on the board at position (i, j).
 */

SGFNode*
sgfBoardNumber(SGFNode* node, int i, int j, int number)
{
    char text[10];

    gg_snprintf(text, 10, "%c%c:%i", j + 'a', i + 'a', number);
    sgfAddProperty(node, "LB", text);

    return node;
}


/*
 * Place a triangle mark on the board at position (i, j).
 */

SGFNode*
sgfTriangle(SGFNode* node, int i, int j)
{
    char text[3];

    gg_snprintf(text, 3, "%c%c", j + 'a', i + 'a');
    sgfAddProperty(node, "TR", text);

    return node;
}


/*
 * Place a label on the board at position (i, j).
 */

SGFNode*
sgfLabel(SGFNode* node, const char* label, int i, int j)
{
    /* allows 12 chars labels - more than enough */
    char text[16];

    gg_snprintf(text, 16, "%c%c:%s", j + 'a', i + 'a', label);
    sgfAddProperty(node, "LB", text);

    return node;
}


/*
 * Place a numeric label on the board at position (i, j).
 */

SGFNode*
sgfLabelInt(SGFNode* node, int num, int i, int j)
{
    char text[16];

    gg_snprintf(text, 16, "%c%c:%d", j + 'a', i + 'a', num);
    sgfAddProperty(node, "LB", text);

    return node;
}


/*
 * Place a circle mark on the board at position (i, j).
 */

SGFNode*
sgfCircle(SGFNode* node, int i, int j)
{
    char text[3];

    gg_snprintf(text, 3, "%c%c", j + 'a', i + 'a');
    sgfAddProperty(node, "CR", text);

    return node;
}


/*
 * Place a square mark on the board at position (i, j).
 */

SGFNode*
sgfSquare(SGFNode* node, int i, int j)
{
    return sgfMark(node, i, j);   /* cgoban 1.9.5 does not understand SQ */
}


/*
 * Place a (square) mark on the board at position (i, j).
 */

SGFNode*
sgfMark(SGFNode* node, int i, int j)
{
    char text[3];

    gg_snprintf(text, 3, "%c%c", j + 'a', i + 'a');
    sgfAddProperty(node, "MA", text);

    return node;
}


/*
 * Start a new variant. Returns a pointer to the new node.
 */

SGFNode*
sgfStartVariant(SGFNode* node)
{
    assert(node);
    assert(node->parent);

    while (node->next)
        node = node->next;
    node->next = sgfNewNode();
    node->next->parent = node->parent;

    return node->next;
}


/*
 * Start a new variant as first child. Returns a pointer to the new node.
 */

SGFNode*
sgfStartVariantFirst(SGFNode* node)
{
    SGFNode* old_first_child = node;
    SGFNode* new_first_child = sgfNewNode();

    assert(node);
    assert(node->parent);

    new_first_child->next = old_first_child;
    new_first_child->parent = old_first_child->parent;

    new_first_child->parent->child = new_first_child;

    return new_first_child;
}


/*
 * If no child exists, add one. Otherwise add a sibling to the
 * existing children. Returns a pointer to the new node.
 */

SGFNode*
sgfAddChild(SGFNode* node)
{
    SGFNode* new_node = sgfNewNode();
    assert(node);

    new_node->parent = node;

    if (!node->child)
        node->child = new_node;
    else {
        node = node->child;
        while (node->next)
            node = node->next;
        node->next = new_node;
    }

    return new_node;
}


/*
 * Write result of the game to the game tree.
 */

void
sgfWriteResult(SGFNode* node, float score, int overwrite)
{
    char text[8];
    char winner;
    float s;
    int dummy;

    /* If not writing to the SGF file, skip everything and return now. */
    if (!node)
        return;

    /* If not overwriting and there already is a result property, return. */
    if (!overwrite)
        if (sgfGetIntProperty(node, "RE", &dummy))
            return;

    if (score > 0.0) {
        winner = 'W';
        s = score;
    }
    else if (score < 0.0) {
        winner = 'B';
        s = -score;
    }
    else {
        winner = '0';
        s = 0;
    }

    if (winner == '0')
        gg_snprintf(text, 8, "0");
    else if (score < 1000.0 && score > -1000.0)
        gg_snprintf(text, 8, "%c+%3.1f", winner, s);
    else
        gg_snprintf(text, 8, "%c+%c", winner, 'R');
    sgfOverwriteProperty(node, "RE", text);
}


static void
sgf_write_header_reduced(SGFNode* root, int overwrite)
{
    time_t curtime = time(NULL);
    struct tm* loctime = localtime(& curtime);
    char str[128];
    int dummy;

    gg_snprintf(str, 128, "%4.4i-%2.2i-%2.2i",
        loctime->tm_year + 1900, loctime->tm_mon + 1, loctime->tm_mday);
    if (overwrite || !sgfGetIntProperty(root, "DT", &dummy))
        sgfOverwriteProperty(root, "DT", str);
    if (overwrite || !sgfGetIntProperty(root, "AP", &dummy))
        sgfOverwriteProperty(root, "AP", "SFC Go:");
    sgfOverwriteProperty(root, "FF", "4");
}


void
sgf_write_header(SGFNode* root, int overwrite, int seed, float komi,
    int handicap, int level, int rules)
{
    char str[128];
    int dummy;

    gg_snprintf(str, 128, "GNU Go %s Random Seed %d level %d",
        VERSION, seed, level);
    if (overwrite || !sgfGetIntProperty(root, "GN", &dummy))
        sgfOverwriteProperty(root, "GN", str);
    if (overwrite || !sgfGetIntProperty(root, "RU", &dummy))
        sgfOverwriteProperty(root, "RU", rules ? "Chinese" : "Japanese");
    sgfOverwritePropertyFloat(root, "KM", komi);
    sgfOverwritePropertyInt(root, "HA", handicap);

    sgf_write_header_reduced(root, overwrite);
}


/* ================================================================ */
/*                          Read SGF tree                           */
/* ================================================================ */


#define MAX_FILE_BUFFER 200000 /* buffer for reading SGF file. */

/*
 * SGF grammar:
 *
 * Collection = GameTree { GameTree }
 * GameTree   = "(" Sequence { GameTree } ")"
 * Sequence   = Node { Node }
 * Node       = ";" { Property }
 * Property   = PropIdent PropValue { PropValue }
 * PropIdent  = UcLetter { UcLetter }
 * PropValue  = "[" CValueType "]"
 * CValueType = (ValueType | Compose)
 * ValueType  = (None | Number | Real | Double | Color | SimpleText |
 *               Text | Point  | Move | Stone)
 *
 * The above grammar has a number of simple properties which enables us
 * to write a simpler parser:
 *   1) There is never a need for backtracking
 *   2) The only recursion is on gametree.
 *   3) Tokens are only one character
 *
 * We will use a global state to keep track of the remaining input
 * and a global char variable, `lookahead' to hold the next token.
 * The function `nexttoken' skips whitespace and fills lookahead with
 * the new token.
 */


static void parse_error(const char* msg, int arg);
static void nexttoken(void);
static void match(int expected);


static FILE* sgffile;


#define sgf_getch() (getc(sgffile))


static char* sgferr;
#ifdef TEST_SGFPARSER
static int sgferrarg;
#endif
static int sgferrpos;

static int lookahead;


/* ---------------------------------------------------------------- */
/*                       Parsing primitives                         */
/* ---------------------------------------------------------------- */


static void
parse_error(const char* msg, int arg)
{
    fprintf(stderr, msg, arg);
    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}


static void
nexttoken()
{
    do
        lookahead = sgf_getch();
    while (isspace(lookahead));
}


static void
match(int expected)
{
    if (lookahead != expected)
        parse_error("expected: %c", expected);
    else
        nexttoken();
}

/* ---------------------------------------------------------------- */
/*                        The parser proper                         */
/* ---------------------------------------------------------------- */


static void
propident(char* buffer, int size)
{
    if (lookahead == EOF || !isupper(lookahead))
        parse_error("Expected an upper case letter.", 0);

    while (lookahead != EOF && isalpha(lookahead)) {
        if (isupper(lookahead) && size > 1) {
            *buffer++ = lookahead;
            size--;
        }
        nexttoken();
    }
    *buffer = '\0';
}


static void
propvalue(char* buffer, int size)
{
    char* p = buffer;

    match('[');
    while (lookahead != ']' && lookahead != EOF) {
        if (lookahead == '\\') {
            lookahead = sgf_getch();
            /* Follow the FF4 definition of backslash */
            if (lookahead == '\r') {
                lookahead = sgf_getch();
                if (lookahead == '\n')
                    lookahead = sgf_getch();
            }
            else if (lookahead == '\n') {
                lookahead = sgf_getch();
                if (lookahead == '\r')
                    lookahead = sgf_getch();
            }
        }
        if (size > 1) {
            *p++ = lookahead;
            size--;
        }
        lookahead = sgf_getch();
    }
    match(']');

    /* Remove trailing whitespace. The double cast below is needed
     * because "char" may be represented as a signed char, in which case
     * characters between 128 and 255 would be negative and a direct
     * cast to int would cause a negative value to be passed to isspace,
     * possibly causing an assertion failure.
     */
    --p;
    while (p > buffer && isspace((int)(unsigned char)*p))
        --p;
    *++p = '\0';
}


static SGFProperty*
property(SGFNode* n, SGFProperty* last)
{
    char name[3];
    char buffer[4000];

    propident(name, sizeof(name));
    do {
        propvalue(buffer, sizeof(buffer));
        last = sgfMkProperty(name, buffer, n, last);
    } while (lookahead == '[');
    return last;
}


static void
node(SGFNode* n)
{
    SGFProperty* last = NULL;
    match(';');
    while (lookahead != EOF && isupper(lookahead))
        last = property(n, last);
}


static SGFNode*
sequence(SGFNode* n)
{
    node(n);
    while (lookahead == ';') {
        SGFNode* new1 = sgfNewNode();
        new1->parent = n;
        n->child = new1;
        n = new1;
        node(n);
    }
    return n;
}


static void
gametree(SGFNode** p, SGFNode* parent, int mode)
{
    if (mode == STRICT_SGF)
        match('(');
    else
        for (;;) {
            if (lookahead == EOF) {
                parse_error("Empty file?", 0);
                break;
            }
            if (lookahead == '(') {
                while (lookahead == '(')
                    nexttoken();
                if (lookahead == ';')
                    break;
            }
            nexttoken();
        }

    /* The head is parsed */
    {
        SGFNode* head = sgfNewNode();
        SGFNode* last;

        head->parent = parent;
        *p = head;

        last = sequence(head);
        p = &last->child;
        while (lookahead == '(') {
            gametree(p, last, STRICT_SGF);
            p = &((*p)->next);
        }
        if (mode == STRICT_SGF)
            match(')');
    }
}


/*
 * Fuseki readers
 * Reads an SGF file for extract_fuseki in a compact way
 */

static void
gametreefuseki(SGFNode** p, SGFNode* parent, int mode,
    int moves_per_game, int i)
{
    if (mode == STRICT_SGF)
        match('(');
    else
        for (;;) {
            if (lookahead == EOF) {
                parse_error("Empty file?", 0);
                break;
            }
            if (lookahead == '(') {
                while (lookahead == '(')
                    nexttoken();
                if (lookahead == ';')
                    break;
            }
            nexttoken();
        }

    /* The head is parsed */
    {

        SGFNode* head = sgfNewNode();
        SGFNode* last;
        head->parent = parent;
        *p = head;

        last = sequence(head);
        p = &last->child;
        while (lookahead == '(') {
            if (last->props
                && (last->props->name == SGFB || last->props->name == SGFW))
                i++;
            /* break after number_of_moves moves in SGF file */
            if (i >= moves_per_game) {
                last->child = NULL;
                last->next = NULL;
                break;
            }
            else {
                gametreefuseki(p, last, mode, moves_per_game, i);
                p = &((*p)->next);
            }
        }
        if (mode == STRICT_SGF)
            match(')');
    }
}

SGFNode*
readsgffilefuseki(const char* filename, int moves_per_game)
{
    SGFNode* root;
    int tmpi = 0;

    if (strcmp(filename, "-") == 0)
        sgffile = stdin;
    else
        sgffile = fopen(filename, "r");

    if (!sgffile)
        return NULL;


    nexttoken();
    gametreefuseki(&root, NULL, LAX_SGF, moves_per_game, 0);

    fclose(sgffile);

    if (sgferr) {
        fprintf(stderr, "Parse error: %s at position %d\n", sgferr, sgferrpos);
        sgfFreeNode(root);
        return NULL;
    }

    /* perform some simple checks on the file */
    if (!sgfGetIntProperty(root, "GM", &tmpi)) {
        if (VERBOSE_WARNINGS)
            fprintf(stderr, "Couldn't find the game type (GM) attribute!\n");
    }
    else if (tmpi != 1) {
        fprintf(stderr, "SGF file might be for game other than go: %d\n", tmpi);
        fprintf(stderr, "Trying to load anyway.\n");
    }

    if (!sgfGetIntProperty(root, "FF", &tmpi)) {
        if (VERBOSE_WARNINGS)
            fprintf(stderr, "Can not determine SGF spec version (FF)!\n");
    }
    else if ((tmpi < 3 || tmpi > 4) && VERBOSE_WARNINGS)
        fprintf(stderr, "Unsupported SGF spec version: %d\n", tmpi);

    return root;
}





/*
 * Wrapper around readsgf which reads from a file rather than a string.
 * Returns NULL if file will not open, or some other parsing error.
 * Filename "-" means read from stdin, and leave it open when done.
 */

SGFNode*
readsgffile(const char* filename)
{
    SGFNode* root;
    int tmpi = 0;

    if (strcmp(filename, "-") == 0)
        sgffile = stdin;
    else
        sgffile = fopen(filename, "r");

    if (!sgffile)
        return NULL;


    nexttoken();
    gametree(&root, NULL, LAX_SGF);

    if (sgffile != stdin)
        fclose(sgffile);

    if (sgferr) {
        fprintf(stderr, "Parse error: %s at position %d\n", sgferr, sgferrpos);
        sgfFreeNode(root);
        return NULL;
    }

    /* perform some simple checks on the file */
    if (!sgfGetIntProperty(root, "GM", &tmpi)) {
        if (VERBOSE_WARNINGS)
            fprintf(stderr, "Couldn't find the game type (GM) attribute!\n");
    }
    else if (tmpi != 1) {
        fprintf(stderr, "SGF file might be for game other than go: %d\n", tmpi);
        fprintf(stderr, "Trying to load anyway.\n");
    }

    if (!sgfGetIntProperty(root, "FF", &tmpi)) {
        if (VERBOSE_WARNINGS)
            fprintf(stderr, "Can not determine SGF spec version (FF)!\n");
    }
    else if ((tmpi < 3 || tmpi > 4) && VERBOSE_WARNINGS)
        fprintf(stderr, "Unsupported SGF spec version: %d\n", tmpi);

    return root;
}



/* ================================================================ */
/*                          Write SGF tree                          */
/* ================================================================ */


#define OPTION_STRICT_FF4 0

static int sgf_column = 0;

static void
sgf_putc(int c, FILE* file)
{
    if (c == '\n' && sgf_column == 0)
        return;

    fputc(c, file);

    if (c == '\n')
        sgf_column = 0;
    else
        sgf_column++;

    if (c == ']' && sgf_column > 60) {
        fputc('\n', file);
        sgf_column = 0;
    }
}

static void
sgf_puts(const char* s, FILE* file)
{
    for (; *s; s++) {
        if (*s == '[' || *s == ']' || *s == '\\') {
            fputc('\\', file);
            sgf_column++;
        }
        fputc((int)*s, file);
        sgf_column++;
    }
}

/* Print all properties with the given name in a node to file and mark
 * them as printed.
 *
 * If is_comment is 1, multiple properties are concatenated with a
 * newline. I.e. we write
 *
 * C[comment1
 * comment2]
 *
 * instead of
 *
 * C[comment1][comment2]
 *
 * Most other property types should be written in the latter style.
 */

static void
sgf_print_name(FILE* file, short name)
{
    sgf_putc(name & 0xff, file);
    if (name >> 8 != ' ')
        sgf_putc(name >> 8, file);
}

static void
sgf_print_property(FILE* file, SGFNode* node, short name, int is_comment)
{
    int n = 0;
    SGFProperty* prop;

    for (prop = node->props; prop; prop = prop->next) {
        if (prop->name == name) {
            prop->name |= 0x20;  /* Indicate already printed. */
            if (n == 0) {
                sgf_print_name(file, name);
                sgf_putc('[', file);
            }
            else if (is_comment)
                sgf_putc('\n', file);
            else {
                sgf_putc(']', file);
                sgf_putc('[', file);
            }

            sgf_puts(prop->value, file);
            n++;
        }
    }

    if (n > 0)
        sgf_putc(']', file);

    /* Add a newline after certain properties. */
    if (name == SGFAB || name == SGFAW || name == SGFAE || (is_comment && n > 1))
        sgf_putc('\n', file);
}

/*
 * Print all remaining unprinted property values at node N to file.
 */

static void
sgfPrintRemainingProperties(FILE* file, SGFNode* node)
{
    SGFProperty* prop;

    for (prop = node->props; prop; prop = prop->next)
        if (!(prop->name & 0x20))
            sgf_print_property(file, node, prop->name, 0);
}


/*
 * Print the property values of NAME at node N and mark it as printed.
 */

static void
sgfPrintCharProperty(FILE* file, SGFNode* node, const char* name)
{
    short nam = name[0] | name[1] << 8;

    sgf_print_property(file, node, nam, 0);
}


/*
 * Print comments from Node node.
 *
 * NOTE: cgoban does not print "C[comment1][comment2]" and I don't know
 *       what the sgfspec says.
 */

static void
sgfPrintCommentProperty(FILE* file, SGFNode* node, const char* name)
{
    short nam = name[0] | name[1] << 8;

    sgf_print_property(file, node, nam, 1);
}


static void
unparse_node(FILE* file, SGFNode* node)
{
    sgf_putc(';', file);
    sgfPrintCharProperty(file, node, "B ");
    sgfPrintCharProperty(file, node, "W ");
    sgfPrintCommentProperty(file, node, "N ");
    sgfPrintCommentProperty(file, node, "C ");
    sgfPrintRemainingProperties(file, node);
}


static void
unparse_root(FILE* file, SGFNode* node)
{
    sgf_putc(';', file);

    if (sgfHasProperty(node, "GM"))
        sgfPrintCharProperty(file, node, "GM");
    else {
        fputs("GM[1]", file);
        sgf_column += 5;
    }

    sgfPrintCharProperty(file, node, "FF");
    sgf_putc('\n', file);

    sgfPrintCharProperty(file, node, "SZ");
    sgf_putc('\n', file);

    sgfPrintCharProperty(file, node, "GN");
    sgf_putc('\n', file);

    sgfPrintCharProperty(file, node, "DT");
    sgf_putc('\n', file);

    sgfPrintCommentProperty(file, node, "PB");
    sgfPrintCommentProperty(file, node, "BR");
    sgf_putc('\n', file);

    sgfPrintCommentProperty(file, node, "PW");
    sgfPrintCommentProperty(file, node, "WR");
    sgf_putc('\n', file);

    sgfPrintCommentProperty(file, node, "N ");
    sgfPrintCommentProperty(file, node, "C ");
    sgfPrintRemainingProperties(file, node);

    sgf_putc('\n', file);
}


/*
 * p->child is the next move.
 * p->next  is the next variation
 */

static void
unparse_game(FILE* file, SGFNode* node, int root)
{
    if (!root)
        sgf_putc('\n', file);
    sgf_putc('(', file);
    if (root)
        unparse_root(file, node);
    else
        unparse_node(file, node);

    node = node->child;
    while (node != NULL && node->next == NULL) {
        unparse_node(file, node);
        node = node->child;
    }

    while (node != NULL) {
        unparse_game(file, node, 0);
        node = node->next;
    }
    sgf_putc(')', file);
    if (root)
        sgf_putc('\n', file);
}

/* Printed properties are marked by adding the 0x20 bit to the
 * property name (changing an upper case letter to lower case). This
 * function removes this mark so that we can print the property next
 * time too. It recurses to all properties in the linked list.
 */
static void
restore_property(SGFProperty* prop)
{
    if (prop) {
        restore_property(prop->next);
        prop->name &= ~0x20;
    }
}

/* When called with the tree root, recurses to all properties in the
 * tree and removes all print marks.
 */
static void
restore_node(SGFNode* node)
{
    if (node) {
        restore_property(node->props);
        restore_node(node->child);
        restore_node(node->next);
    }
}


/*
 * Opens filename and writes the game stored in the sgf structure.
 */

int
writesgf(SGFNode* root, const char* filename)
{
    FILE* outfile;

    if (strcmp(filename, "-") == 0)
        outfile = stdout;
    else
        outfile = fopen(filename, "w");

    if (!outfile) {
        fprintf(stderr, "Can not open %s\n", filename);
        return 0;
    }

    sgf_write_header_reduced(root, 0);

    sgf_column = 0;
    unparse_game(outfile, root, 1);
    if (outfile != stdout)
        fclose(outfile);

    /* Remove "printed" marks so that the tree can be written multiple
     * times.
     */
    restore_node(root);

    return 1;
}


#ifdef TEST_SGFPARSER
int
main()
{
    static char buffer[25000];
    static char output[25000];
    SGFNode* game;

    sgffile = stdin;

    nexttoken();
    gametree(&game, LAX_SGF);
    if (sgferr) {
        fprintf(stderr, "Parse error:");
        fprintf(stderr, sgferr, sgferrarg);
        fprintf(stderr, " at position %d\n", sgferrpos);
    }
    else {
        unparse_game(stdin, game, 1);
        write(1, output, outputp - output);
    }
}
#endif



/*
 * Local Variables:
 * tab-width: 8
 * c-basic-offset: 2
 * End:
 */
