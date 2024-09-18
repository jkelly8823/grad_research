/* Generated by re2c 0.15.3 on Mon Sep  4 22:44:17 2017 */
#line 1 "ext/date/lib/parse_date.re"
/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Derick Rethans
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* $Id$ */

#include "timelib.h"
#include "timelib_private.h"

#include <ctype.h>
#include <math.h>
#include <assert.h>

#if defined(_MSC_VER)
# define strtoll(s, f, b) _atoi64(s)
#elif !defined(HAVE_STRTOLL)
# if defined(HAVE_ATOLL)
#  define strtoll(s, f, b) atoll(s)
# else
#  define strtoll(s, f, b) strtol(s, f, b)
# endif
#endif

#define EOI      257
#define TIME     258
#define DATE     259

#define TIMELIB_XMLRPC_SOAP    260
#define TIMELIB_TIME12         261
#define TIMELIB_TIME24         262
#define TIMELIB_GNU_NOCOLON    263
#define TIMELIB_GNU_NOCOLON_TZ 264
#define TIMELIB_ISO_NOCOLON    265

#define TIMELIB_AMERICAN       266
#define TIMELIB_ISO_DATE       267
#define TIMELIB_DATE_FULL      268
#define TIMELIB_DATE_TEXT      269
#define TIMELIB_DATE_NOCOLON   270
#define TIMELIB_PG_YEARDAY     271
#define TIMELIB_PG_TEXT        272
#define TIMELIB_PG_REVERSE     273
#define TIMELIB_CLF            274
#define TIMELIB_DATE_NO_DAY    275
#define TIMELIB_SHORTDATE_WITH_TIME 276
#define TIMELIB_DATE_FULL_POINTED 277
#define TIMELIB_TIME24_WITH_ZONE 278
#define TIMELIB_ISO_WEEK       279
#define TIMELIB_LF_DAY_OF_MONTH 280
#define TIMELIB_WEEK_DAY_OF_MONTH 281

#define TIMELIB_TIMEZONE       300
#define TIMELIB_AGO            301

#define TIMELIB_RELATIVE       310

#define TIMELIB_ERROR          999

/* Some compilers like AIX, defines uchar in sys/types.h */
#undef uchar
typedef unsigned char uchar;

#define   BSIZE	   8192

#define   YYCTYPE      uchar
#define   YYCURSOR     cursor
#define   YYLIMIT      s->lim
#define   YYMARKER     s->ptr
#define   YYFILL(n)    return EOI;

#define   RET(i)       {s->cur = cursor; return i;}

#define timelib_string_free timelib_free

#define TIMELIB_HAVE_TIME() { if (s->time->have_time) { add_error(s, TIMELIB_ERR_DOUBLE_TIME, "Double time specification"); timelib_string_free(str); return TIMELIB_ERROR; } else { s->time->have_time = 1; s->time->h = 0; s->time->i = 0; s->time->s = 0; s->time->us = 0; } }
#define TIMELIB_UNHAVE_TIME() { s->time->have_time = 0; s->time->h = 0; s->time->i = 0; s->time->s = 0; s->time->us = 0; }
#define TIMELIB_HAVE_DATE() { if (s->time->have_date) { add_error(s, TIMELIB_ERR_DOUBLE_DATE, "Double date specification"); timelib_string_free(str); return TIMELIB_ERROR; } else { s->time->have_date = 1; } }
#define TIMELIB_UNHAVE_DATE() { s->time->have_date = 0; s->time->d = 0; s->time->m = 0; s->time->y = 0; }
#define TIMELIB_HAVE_RELATIVE() { s->time->have_relative = 1; }
#define TIMELIB_HAVE_WEEKDAY_RELATIVE() { s->time->have_relative = 1; s->time->relative.have_weekday_relative = 1; }
#define TIMELIB_HAVE_SPECIAL_RELATIVE() { s->time->have_relative = 1; s->time->relative.have_special_relative = 1; }
#define TIMELIB_HAVE_TZ() { s->cur = cursor; if (s->time->have_zone) { s->time->have_zone > 1 ? add_error(s, TIMELIB_ERR_DOUBLE_TZ, "Double timezone specification") : add_warning(s, TIMELIB_WARN_DOUBLE_TZ, "Double timezone specification"); timelib_string_free(str); s->time->have_zone++; return TIMELIB_ERROR; } else { s->time->have_zone++; } }

#define TIMELIB_INIT  s->cur = cursor; str = timelib_string(s); ptr = str
#define TIMELIB_DEINIT timelib_string_free(str)
#define TIMELIB_ADJUST_RELATIVE_WEEKDAY() if (in->time.have_weekday_relative && (in.rel.d > 0)) { in.rel.d -= 7; }

#define TIMELIB_PROCESS_YEAR(x, l) { \
	if (((x) == TIMELIB_UNSET) || ((l) >= 4)) { \
	/*	(x) = 0; */          \
	} else if ((x) < 100) {  \
		if ((x) < 70) {      \
			(x) += 2000;     \
		} else {             \
			(x) += 1900;     \
		}                    \
	}                        \
}

#ifdef DEBUG_PARSER
#define DEBUG_OUTPUT(s) printf("%s\n", s);
#define YYDEBUG(s,c) { if (s != -1) { printf("state: %d ", s); printf("[%c]\n", c); } }
#else
#define DEBUG_OUTPUT(s)
#define YYDEBUG(s,c)
#endif

typedef struct _timelib_elems {
	unsigned int   c; /* Number of elements */
	char         **v; /* Values */
} timelib_elems;

typedef struct _Scanner {
	int           fd;
	uchar        *lim, *str, *ptr, *cur, *tok, *pos;
	unsigned int  line, len;
	timelib_error_container *errors;

	timelib_time        *time;
	const timelib_tzdb  *tzdb;
} Scanner;

typedef struct _timelib_lookup_table {
    const char *name;
    int         type;
    int         value;
} timelib_lookup_table;

typedef struct _timelib_relunit {
	const char *name;
	int         unit;
	int         multiplier;
} timelib_relunit;

/* The timezone table. */
static const timelib_tz_lookup_table timelib_timezone_lookup[] = {
#include "timezonemap.h"
	{ NULL, 0, 0, NULL },
};

static const timelib_tz_lookup_table timelib_timezone_fallbackmap[] = {
#include "fallbackmap.h"
	{ NULL, 0, 0, NULL },
};

static const timelib_tz_lookup_table timelib_timezone_utc[] = {
	{ "utc", 0, 0, "UTC" },
};

static timelib_relunit const timelib_relunit_lookup[] = {
	{ "ms",           TIMELIB_MICROSEC, 1000 },
	{ "msec",         TIMELIB_MICROSEC, 1000 },
	{ "msecs",        TIMELIB_MICROSEC, 1000 },
	{ "millisecond",  TIMELIB_MICROSEC, 1000 },
	{ "milliseconds", TIMELIB_MICROSEC, 1000 },
	{ "µs",           TIMELIB_MICROSEC,    1 },
	{ "usec",         TIMELIB_MICROSEC,    1 },
	{ "usecs",        TIMELIB_MICROSEC,    1 },
	{ "µsec",         TIMELIB_MICROSEC,    1 },
	{ "µsecs",        TIMELIB_MICROSEC,    1 },
	{ "microsecond",  TIMELIB_MICROSEC,    1 },
	{ "microseconds", TIMELIB_MICROSEC,    1 },
	{ "sec",         TIMELIB_SECOND,  1 },
	{ "secs",        TIMELIB_SECOND,  1 },
	{ "second",      TIMELIB_SECOND,  1 },
	{ "seconds",     TIMELIB_SECOND,  1 },
	{ "min",         TIMELIB_MINUTE,  1 },
	{ "mins",        TIMELIB_MINUTE,  1 },
	{ "minute",      TIMELIB_MINUTE,  1 },
	{ "minutes",     TIMELIB_MINUTE,  1 },
	{ "hour",        TIMELIB_HOUR,    1 },
	{ "hours",       TIMELIB_HOUR,    1 },
	{ "day",         TIMELIB_DAY,     1 },
	{ "days",        TIMELIB_DAY,     1 },
	{ "week",        TIMELIB_DAY,     7 },
	{ "weeks",       TIMELIB_DAY,     7 },
	{ "fortnight",   TIMELIB_DAY,    14 },
	{ "fortnights",  TIMELIB_DAY,    14 },
	{ "forthnight",  TIMELIB_DAY,    14 },
	{ "forthnights", TIMELIB_DAY,    14 },
	{ "month",       TIMELIB_MONTH,   1 },
	{ "months",      TIMELIB_MONTH,   1 },
	{ "year",        TIMELIB_YEAR,    1 },
	{ "years",       TIMELIB_YEAR,    1 },

	{ "monday",      TIMELIB_WEEKDAY, 1 },
	{ "mon",         TIMELIB_WEEKDAY, 1 },
	{ "tuesday",     TIMELIB_WEEKDAY, 2 },
	{ "tue",         TIMELIB_WEEKDAY, 2 },
	{ "wednesday",   TIMELIB_WEEKDAY, 3 },
	{ "wed",         TIMELIB_WEEKDAY, 3 },
	{ "thursday",    TIMELIB_WEEKDAY, 4 },
	{ "thu",         TIMELIB_WEEKDAY, 4 },
	{ "friday",      TIMELIB_WEEKDAY, 5 },
	{ "fri",         TIMELIB_WEEKDAY, 5 },
	{ "saturday",    TIMELIB_WEEKDAY, 6 },
	{ "sat",         TIMELIB_WEEKDAY, 6 },
	{ "sunday",      TIMELIB_WEEKDAY, 0 },
	{ "sun",         TIMELIB_WEEKDAY, 0 },

	{ "weekday",     TIMELIB_SPECIAL, TIMELIB_SPECIAL_WEEKDAY },
	{ "weekdays",    TIMELIB_SPECIAL, TIMELIB_SPECIAL_WEEKDAY },
	{ NULL,          0,          0 }
};

/* The relative text table. */
static timelib_lookup_table const timelib_reltext_lookup[] = {
	{ "first",    0,  1 },
	{ "next",     0,  1 },
	{ "second",   0,  2 },
	{ "third",    0,  3 },
	{ "fourth",   0,  4 },
	{ "fifth",    0,  5 },
	{ "sixth",    0,  6 },
	{ "seventh",  0,  7 },
	{ "eight",    0,  8 },
	{ "eighth",   0,  8 },
	{ "ninth",    0,  9 },
	{ "tenth",    0, 10 },
	{ "eleventh", 0, 11 },
	{ "twelfth",  0, 12 },
	{ "last",     0, -1 },
	{ "previous", 0, -1 },
	{ "this",     1,  0 },
	{ NULL,       1,  0 }
};

/* The month table. */
static timelib_lookup_table const timelib_month_lookup[] = {
	{ "jan",  0,  1 },
	{ "feb",  0,  2 },
	{ "mar",  0,  3 },
	{ "apr",  0,  4 },
	{ "may",  0,  5 },
	{ "jun",  0,  6 },
	{ "jul",  0,  7 },
	{ "aug",  0,  8 },
	{ "sep",  0,  9 },
	{ "sept", 0,  9 },
	{ "oct",  0, 10 },
	{ "nov",  0, 11 },
	{ "dec",  0, 12 },
	{ "i",    0,  1 },
	{ "ii",   0,  2 },
	{ "iii",  0,  3 },
	{ "iv",   0,  4 },
	{ "v",    0,  5 },
	{ "vi",   0,  6 },
	{ "vii",  0,  7 },
	{ "viii", 0,  8 },
	{ "ix",   0,  9 },
	{ "x",    0, 10 },
	{ "xi",   0, 11 },
	{ "xii",  0, 12 },

	{ "january",   0,  1 },
	{ "february",  0,  2 },
	{ "march",     0,  3 },
	{ "april",     0,  4 },
	{ "may",       0,  5 },
	{ "june",      0,  6 },
	{ "july",      0,  7 },
	{ "august",    0,  8 },
	{ "september", 0,  9 },
	{ "october",   0, 10 },
	{ "november",  0, 11 },
	{ "december",  0, 12 },
	{  NULL,       0,  0 }
};

#if 0
static char* timelib_ltrim(char *s)
{
	char *ptr = s;
	while (ptr[0] == ' ' || ptr[0] == '\t') {
		ptr++;
	}
	return ptr;
}
#endif

#if 0
uchar *fill(Scanner *s, uchar *cursor){
	if(!s->eof){
		unsigned int cnt = s->tok - s->bot;
		if(cnt){
			memcpy(s->bot, s->tok, s->lim - s->tok);
			s->tok = s->bot;
			s->ptr -= cnt;
			cursor -= cnt;
			s->pos -= cnt;
			s->lim -= cnt;
		}
		if((s->top - s->lim) < BSIZE){
			uchar *buf = (uchar*) timelib_malloc(((s->lim - s->bot) + BSIZE)*sizeof(uchar));
			memcpy(buf, s->tok, s->lim - s->tok);
			s->tok = buf;
			s->ptr = &buf[s->ptr - s->bot];
			cursor = &buf[cursor - s->bot];
			s->pos = &buf[s->pos - s->bot];
			s->lim = &buf[s->lim - s->bot];
			s->top = &s->lim[BSIZE];
			timelib_free(s->bot);
			s->bot = buf;
		}
		if((cnt = read(s->fd, (char*) s->lim, BSIZE)) != BSIZE){
			s->eof = &s->lim[cnt]; *(s->eof)++ = '\n';
		}
		s->lim += cnt;
	}
	return cursor;
}
#endif

static void add_warning(Scanner *s, int error_code, char *error)
{
	s->errors->warning_count++;
	s->errors->warning_messages = timelib_realloc(s->errors->warning_messages, s->errors->warning_count * sizeof(timelib_error_message));
	s->errors->warning_messages[s->errors->warning_count - 1].error_code = error_code;
	s->errors->warning_messages[s->errors->warning_count - 1].position = s->tok ? s->tok - s->str : 0;
	s->errors->warning_messages[s->errors->warning_count - 1].character = s->tok ? *s->tok : 0;
	s->errors->warning_messages[s->errors->warning_count - 1].message = timelib_strdup(error);
}

static void add_error(Scanner *s, int error_code, char *error)
{
	s->errors->error_count++;
	s->errors->error_messages = timelib_realloc(s->errors->error_messages, s->errors->error_count * sizeof(timelib_error_message));
	s->errors->error_messages[s->errors->error_count - 1].error_code = error_code;
	s->errors->error_messages[s->errors->error_count - 1].position = s->tok ? s->tok - s->str : 0;
	s->errors->error_messages[s->errors->error_count - 1].character = s->tok ? *s->tok : 0;
	s->errors->error_messages[s->errors->error_count - 1].message = timelib_strdup(error);
}

static void add_pbf_warning(Scanner *s, int error_code, char *error, char *sptr, char *cptr)
{
	s->errors->warning_count++;
	s->errors->warning_messages = timelib_realloc(s->errors->warning_messages, s->errors->warning_count * sizeof(timelib_error_message));
	s->errors->warning_messages[s->errors->warning_count - 1].error_code = error_code;
	s->errors->warning_messages[s->errors->warning_count - 1].position = cptr - sptr;
	s->errors->warning_messages[s->errors->warning_count - 1].character = *cptr;
	s->errors->warning_messages[s->errors->warning_count - 1].message = timelib_strdup(error);
}

static void add_pbf_error(Scanner *s, int error_code, char *error, char *sptr, char *cptr)
{
	s->errors->error_count++;
	s->errors->error_messages = timelib_realloc(s->errors->error_messages, s->errors->error_count * sizeof(timelib_error_message));
	s->errors->error_messages[s->errors->error_count - 1].error_code = error_code;
	s->errors->error_messages[s->errors->error_count - 1].position = cptr - sptr;
	s->errors->error_messages[s->errors->error_count - 1].character = *cptr;
	s->errors->error_messages[s->errors->error_count - 1].message = timelib_strdup(error);
}

static timelib_sll timelib_meridian(char **ptr, timelib_sll h)
{
	timelib_sll retval = 0;

	while (!strchr("AaPp", **ptr)) {
		++*ptr;
	}
	if (**ptr == 'a' || **ptr == 'A') {
		if (h == 12) {
			retval = -12;
		}
	} else if (h != 12) {
		retval = 12;
	}
	++*ptr;
	if (**ptr == '.') {
		++*ptr;
	}
	if (**ptr == 'M' || **ptr == 'm') {
		++*ptr;
	}
	if (**ptr == '.') {
		++*ptr;
	}
	return retval;
}

static timelib_sll timelib_meridian_with_check(char **ptr, timelib_sll h)
{
	timelib_sll retval = 0;

	while (**ptr && !strchr("AaPp", **ptr)) {
		++*ptr;
	}
	if(!**ptr) {
		return TIMELIB_UNSET;
	}
	if (**ptr == 'a' || **ptr == 'A') {
		if (h == 12) {
			retval = -12;
		}
	} else if (h != 12) {
		retval = 12;
	}
	++*ptr;
	if (**ptr == '.') {
		++*ptr;
		if (**ptr != 'm' && **ptr != 'M') {
			return TIMELIB_UNSET;
		}
		++*ptr;
		if (**ptr != '.' ) {
			return TIMELIB_UNSET;
		}
		++*ptr;
	} else if (**ptr == 'm' || **ptr == 'M') {
		++*ptr;
	} else {
		return TIMELIB_UNSET;
	}