#include "file.h"

#ifndef lint
FILE_RCSID("@(#)$File: print.c,v 1.99 2023/07/17 16:40:57 christos Exp $")
#endif  /* lint */

#include <string.h>
#include <stdarg.h>
#include "cdf.h"

#ifndef COMPILE_ONLY
file_protected void
file_mdump(struct magic *m)
{
	static const char optyp[] = { FILE_OPS };
	char tbuf[256];

	(void) fprintf(stderr, "%u: %.*s %d", m->lineno,
	    (m->cont_level & 7) + 1, ">>>>>>>>", m->offset);

	if (m->flag & INDIR) {
		(void) fprintf(stderr, "(%s,",
		    "*bad in_type*");
		if (m->in_op & FILE_OPINVERSE)
			(void) fputc('~', stderr);
		(void) fprintf(stderr, "%c%d),",
		    (CAST(size_t, m->in_op & FILE_OPS_MASK) <
		    __arraycount(optyp)) ?
		    optyp[m->in_op & FILE_OPS_MASK] : '?', m->in_offset);
	}
		case FILE_BESHORT:
		case FILE_BELONG:
		case FILE_INDIRECT:
			(void) fprintf(stderr, "%d", CAST(int32_t, m->value.l));
			break;
		case FILE_BEQUAD:
		case FILE_LEQUAD:
		case FILE_QUAD:
#endif

/*VARARGS*/
file_protected void
file_magwarn(struct magic_set *ms, const char *f, ...)
{
	va_list va;
	char *expanded_format = NULL;
	}
}

file_protected const char *
file_fmtvarint(char *buf, size_t blen, const unsigned char *us, int t)
{
	snprintf(buf, blen, "%jd", CAST(intmax_t,
	    file_varint2uintmax_t(us, t, NULL)));
	return buf;
}

file_protected const char *
file_fmtdatetime(char *buf, size_t bsize, uint64_t v, int flags)
{
	char *pp;
	time_t t;
		t = CAST(time_t, v);
	}

	if (t > MAX_CTIME)
		goto out;

	if (flags & FILE_T_LOCAL) {
		tm = php_localtime_r(&t, &tmz);
	} else {
		tm = php_gmtime_r(&t, &tmz);
 * https://docs.microsoft.com/en-us/windows/win32/api/winbase/\
 *	nf-winbase-dosdatetimetofiletime?redirectedfrom=MSDN
 */
file_protected const char *
file_fmtdate(char *buf, size_t bsize, uint16_t v)
{
	struct tm tm;

	return buf;
}

file_protected const char *
file_fmttime(char *buf, size_t bsize, uint16_t v)
{
	struct tm tm;


}

file_protected const char *
file_fmtnum(char *buf, size_t blen, const char *us, int base)
{
	char *endptr;
	unsigned long long val;