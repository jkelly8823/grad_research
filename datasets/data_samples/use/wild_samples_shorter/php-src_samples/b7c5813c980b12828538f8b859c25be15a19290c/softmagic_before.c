#include "file.h"

#ifndef	lint
FILE_RCSID("@(#)$File: softmagic.c,v 1.328 2022/09/13 18:46:07 christos Exp $")
#endif	/* lint */

#include "magic.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "der.h"

private int match(struct magic_set *, struct magic *, size_t,
    const struct buffer *, size_t, int, int, int, uint16_t *,
    uint16_t *, int *, int *, int *, int *);
private int mget(struct magic_set *, struct magic *, const struct buffer *,
    const unsigned char *, size_t,
    size_t, unsigned int, int, int, int, uint16_t *,
    uint16_t *, int *, int *, int *, int *);
private int msetoffset(struct magic_set *, struct magic *, struct buffer *,
    const struct buffer *, size_t, unsigned int);
private int magiccheck(struct magic_set *, struct magic *);
private int mprint(struct magic_set *, struct magic *);
private int moffset(struct magic_set *, struct magic *, const struct buffer *,
    int32_t *);
private void mdebug(uint32_t, const char *, size_t);
private int mcopy(struct magic_set *, union VALUETYPE *, int, int,
    const unsigned char *, uint32_t, size_t, struct magic *);
private int mconvert(struct magic_set *, struct magic *, int);
private int print_sep(struct magic_set *, int);
private int handle_annotation(struct magic_set *, struct magic *, int);
private int cvt_8(union VALUETYPE *, const struct magic *);
private int cvt_16(union VALUETYPE *, const struct magic *);
private int cvt_32(union VALUETYPE *, const struct magic *);
private int cvt_64(union VALUETYPE *, const struct magic *);

#define OFFSET_OOB(n, o, i)	((n) < CAST(uint32_t, (o)) || (i) > ((n) - (o)))
#define BE64(p) ( \
    (CAST(uint64_t, (p)->hq[0])<<56)| \
 * Passed the name and FILE * of one file to be typed.
 */
/*ARGSUSED1*/		/* nbytes passed for regularity, maybe need later */
protected int
file_softmagic(struct magic_set *ms, const struct buffer *b,
    uint16_t *indir_count, uint16_t *name_count, int mode, int text)
{
	struct mlist *ml;
	int rv = 0, printed_something = 0, need_separator = 0;
	uint16_t nc, ic;

	if (name_count == NULL) {
		nc = 0;
	for (ml = ms->mlist[0]->next; ml != ms->mlist[0]; ml = ml->next) {
		int ret = match(ms, ml->magic, ml->nmagic, b,
		    0, mode, text, 0, indir_count, name_count,
		    &printed_something, &need_separator, NULL, NULL);
		switch (ret) {
		case -1:
			return ret;
		case 0:
#if defined(FILE_FMTDEBUG) && defined(HAVE_FMTCHECK)
#define F(a, b, c) file_fmtcheck((a), (b), (c), __FILE__, __LINE__)

private const char * __attribute__((__format_arg__(3)))
file_fmtcheck(struct magic_set *ms, const char *desc, const char *def,
	const char *file, size_t line)
{
	const char *ptr;
 *	If a continuation matches, we bump the current continuation level
 *	so that higher-level continuations are processed.
 */
private int
match(struct magic_set *ms, struct magic *magic,
    size_t nmagic, const struct buffer *b, size_t offset, int mode, int text,
    int flip, uint16_t *indir_count, uint16_t *name_count,
    int *printed_something, int *need_separator, int *returnval,
    int *found_match)
{
	uint32_t magindex = 0;
	unsigned int cont_level = 0;
	int found_matchv = 0; /* if a match is found it is set to 1*/
	int returnvalv = 0, e;
	/* a flag to print X\n  X\n- X */
	int firstline = !(*printed_something || *need_separator);
	struct buffer bb;
	int print = (ms->flags & MAGIC_NODESC) == 0;

	/*
		switch (mget(ms, m, b, CAST(const unsigned char *, bb.fbuf),
		    bb.flen, offset, cont_level,
		    mode, text, flip, indir_count, name_count,
		    printed_something, need_separator, returnval, found_match))
		{
		case -1:
			return -1;
		case 0:
			goto flush;
		}

		if ((e = handle_annotation(ms, m, firstline)) != 0)
		{
			*found_match = 1;
			*need_separator = 1;
			*printed_something = 1;
			*returnval = 1;
			return e;
		}

		/*
				*returnval = 1;
				*need_separator = 1;
				*printed_something = 1;
				if (print_sep(ms, firstline) == -1)
					return -1;
				if (mprint(ms, m) == -1)
					return -1;
			}
			    bb.fbuf), bb.flen, offset,
			    cont_level, mode, text, flip, indir_count,
			    name_count, printed_something, need_separator,
			    returnval, found_match)) {
			case -1:
				return -1;
			case 0:
				if (m->reln != '!')
				} else
					ms->c.li[cont_level].got_match = 1;

				if ((e = handle_annotation(ms, m, firstline))
				    != 0) {
					*found_match = 1;
					*need_separator = 1;
					*printed_something = 1;
					 */
					if (!*printed_something) {
						*printed_something = 1;
						if (print_sep(ms, firstline)
						    == -1)
							return -1;
					}
					/* space if previous printed */
			}
		}
		if (*printed_something) {
			firstline = 0;
		}
		if (*found_match) {
			if ((ms->flags & MAGIC_CONTINUE) == 0)
				return *returnval;
			// So that we print a separator
			*printed_something = 0;
			firstline = 0;
		}
		cont_level = 0;
	}
	return *returnval;
}

private int
check_fmt(struct magic_set *ms, const char *fmt)
{
	pcre_cache_entry *pce;
	int rv = -1;
			php_pcre_free_match_data(match_data);
		}
	}
	zend_string_release(pattern);
	return rv;
}

#if !defined(HAVE_STRNDUP) || defined(__aiws__) || defined(_AIX)
}


private int
mprint(struct magic_set *ms, struct magic *m)
{
	uint64_t v;
	float vf;
	return 0;
}

private int
moffset(struct magic_set *ms, struct magic *m, const struct buffer *b,
    int32_t *op)
{
	size_t nbytes = b->flen;
	return 1;
}

private uint32_t
cvt_id3(struct magic_set *ms, uint32_t v)
{
	v = ((((v >>  0) & 0x7f) <<  0) |
	     (((v >>  8) & 0x7f) <<  7) |
	return v;
}

private int
cvt_flip(int type, int flip)
{
	if (flip == 0)
		return type;
	if (m->mask_op & FILE_OPINVERSE) \
		p->fld = ~p->fld \

private int
cvt_8(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(b, uint8_t);
	return 0;
}

private int
cvt_16(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(h, uint16_t);
	return 0;
}

private int
cvt_32(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(l, uint32_t);
	return 0;
}

private int
cvt_64(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT(q, uint64_t);
	return 0;
			break; \
		} \

private int
cvt_float(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT2(f, float);
	return 0;
}

private int
cvt_double(union VALUETYPE *p, const struct magic *m)
{
	DO_CVT2(d, double);
	return 0;
 * While we're here, let's apply the mask operation
 * (unless you have a better idea)
 */
private int
mconvert(struct magic_set *ms, struct magic *m, int flip)
{
	union VALUETYPE *p = &ms->ms_value;

}


private void
mdebug(uint32_t offset, const char *str, size_t len)
{
	(void) fprintf(stderr, "mget/%" SIZE_T_FORMAT "u @%d: ", len, offset);
	file_showstr(stderr, str, len);
	(void) fputc('\n', stderr);
}

private int
mcopy(struct magic_set *ms, union VALUETYPE *p, int type, int indir,
    const unsigned char *s, uint32_t offset, size_t nbytes, struct magic *m)
{
	/*
	 * Note: FILE_SEARCH and FILE_REGEX do not actually copy
	 * anything, but setup pointers into the source
	 */
		}
		case FILE_STRING:	/* XXX - these two should not need */
		case FILE_PSTRING:	/* to copy anything, but do anyway. */
		default:
			break;
		}
	}
		(void)memset(p, '\0', sizeof(*p));
		return 0;
	}
	if (nbytes - offset < sizeof(*p))
		nbytes = nbytes - offset;
	else
		nbytes = sizeof(*p);

	(void)memcpy(p, s + offset, nbytes);

	/*
	return 0;
}

private uint32_t
do_ops(struct magic *m, intmax_t lhs, intmax_t off)
{
	intmax_t offset;
	if (off) {
		switch (m->in_op & FILE_OPS_MASK) {
		case FILE_OPAND:
			offset = lhs & off;
		offset = lhs;
	if (m->in_op & FILE_OPINVERSE)
		offset = ~offset;

	return CAST(uint32_t, offset);
}

private int
msetoffset(struct magic_set *ms, struct magic *m, struct buffer *bb,
    const struct buffer *b, size_t o, unsigned int cont_level)
{
	int32_t offset;
	return 0;
}

private int
save_cont(struct magic_set *ms, struct cont *c)
{
	size_t len;
	*c = ms->c;
	return 0;
}

private void
restore_cont(struct magic_set *ms, struct cont *c)
{
	efree(ms->c.li);
	ms->c = *c;
}

private int
mget(struct magic_set *ms, struct magic *m, const struct buffer *b,
    const unsigned char *s, size_t nbytes, size_t o, unsigned int cont_level,
    int mode, int text, int flip, uint16_t *indir_count, uint16_t *name_count,
    int *printed_something, int *need_separator, int *returnval,
    int *found_match)
{
	uint32_t eoffset, offset = ms->offset;
	struct buffer bb;
		case FILE_BYTE:
			if (OFFSET_OOB(nbytes, offset, 1))
				return 0;
			offset = do_ops(m, SEXT(sgn,8,p->b), off);
			break;
		case FILE_BESHORT:
			if (OFFSET_OOB(nbytes, offset, 2))
				return 0;
			offset = do_ops(m, SEXT(sgn,16,BE16(p)), off);
			break;
		case FILE_LESHORT:
			if (OFFSET_OOB(nbytes, offset, 2))
				return 0;
			offset = do_ops(m, SEXT(sgn,16,LE16(p)), off);
			break;
		case FILE_SHORT:
			if (OFFSET_OOB(nbytes, offset, 2))
				return 0;
			offset = do_ops(m, SEXT(sgn,16,p->h), off);
			break;
		case FILE_BELONG:
		case FILE_BEID3:
			if (OFFSET_OOB(nbytes, offset, 4))
			lhs = BE32(p);
			if (in_type == FILE_BEID3)
				lhs = cvt_id3(ms, CAST(uint32_t, lhs));
			offset = do_ops(m, SEXT(sgn,32,lhs), off);
			break;
		case FILE_LELONG:
		case FILE_LEID3:
			if (OFFSET_OOB(nbytes, offset, 4))
			lhs = LE32(p);
			if (in_type == FILE_LEID3)
				lhs = cvt_id3(ms, CAST(uint32_t, lhs));
			offset = do_ops(m, SEXT(sgn,32,lhs), off);
			break;
		case FILE_MELONG:
			if (OFFSET_OOB(nbytes, offset, 4))
				return 0;
			offset = do_ops(m, SEXT(sgn,32,ME32(p)), off);
			break;
		case FILE_LONG:
			if (OFFSET_OOB(nbytes, offset, 4))
				return 0;
			offset = do_ops(m, SEXT(sgn,32,p->l), off);
			break;
		case FILE_LEQUAD:
			if (OFFSET_OOB(nbytes, offset, 8))
				return 0;
			offset = do_ops(m, SEXT(sgn,64,LE64(p)), off);
			break;
		case FILE_BEQUAD:
			if (OFFSET_OOB(nbytes, offset, 8))
				return 0;
			offset = do_ops(m, SEXT(sgn,64,BE64(p)), off);
			break;
		case FILE_OCTAL:
			if (OFFSET_OOB(nbytes, offset, m->vallen))
				return 0;
			offset = do_ops(m,
			    SEXT(sgn,64,strtoull(p->s, NULL, 8)), off);
			break;
		default:
			if ((ms->flags & MAGIC_DEBUG) != 0)
				fprintf(stderr, "bad in_type=%d\n", in_type);
		bb = *b;
		bb.fbuf = s + offset;
		bb.flen = nbytes - offset;
		rv = -1;
		for (mlp = ms->mlist[0]->next; mlp != ms->mlist[0];
		    mlp = mlp->next)
		{
			if ((rv = match(ms, mlp->magic,
			    mlp->nmagic, &bb, 0, BINTEST, text, 0, indir_count,
			    name_count, printed_something, need_separator,
			    NULL, NULL)) != 0)
				break;
		}

		if ((ms->flags & MAGIC_DEBUG) != 0)
			fprintf(stderr, "indirect @offs=%u[%d]\n", offset, rv);

		eoffset = ms->eoffset;
		rv = match(ms, ml.magic, ml.nmagic, b,
		    offset + o, mode, text, flip, indir_count, name_count,
		    printed_something, need_separator, returnval,
		    &nfound_match);
		ms->ms_value.q = nfound_match;
		(*name_count)--;
		*found_match |= nfound_match;
		    *need_separator = oneed_separator;
		ms->offset = offset;
		ms->eoffset = eoffset;
		return rv;

	case FILE_NAME:
		if (ms->flags & MAGIC_NODESC)
			return 1;
	return 1;
}

private uint64_t
file_strncmp(const char *s1, const char *s2, size_t len, size_t maxlen,
    uint32_t flags)
{
	/*
	return v;
}

private uint64_t
file_strncmp16(const char *a, const char *b, size_t len, size_t maxlen,
    uint32_t flags)
{
	/*
	return file_strncmp(a, b, len, maxlen, flags);
}

private int
magiccheck(struct magic_set *ms, struct magic *m)
{
	uint64_t l = m->value.q;
	uint64_t v;
			break;

		case '!':
			matched = fv != fl;
			break;

		case '=':
			matched = fv == fl;
			break;

		case '>':
			matched = fv > fl;
			break;

		case '<':
			matched = fv < fl;
			break;

		default:
			file_magerror(ms, "cannot happen with float: "
			break;

		case '!':
			matched = dv != dl;
			break;

		case '=':
			matched = dv == dl;
			break;

		case '>':
			matched = dv > dl;
			break;

		case '<':
			matched = dv < dl;
			break;

		default:
			file_magerror(ms, "cannot happen with double: "
	case 'x':
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void) fprintf(stderr, "%" INT64_T_FORMAT
			    "u == *any* = 1\n", CAST(unsigned long long, v));
		matched = 1;
		break;

	case '!':
		matched = v != l;
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void) fprintf(stderr, "%" INT64_T_FORMAT "u != %"
			    INT64_T_FORMAT "u = %d\n",
			    CAST(unsigned long long, v),
			    CAST(unsigned long long, l), matched);
		break;

		matched = v == l;
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void) fprintf(stderr, "%" INT64_T_FORMAT "u == %"
			    INT64_T_FORMAT "u = %d\n",
			    CAST(unsigned long long, v),
			    CAST(unsigned long long, l), matched);
		break;

			matched = v > l;
			if ((ms->flags & MAGIC_DEBUG) != 0)
				(void) fprintf(stderr, "%" INT64_T_FORMAT
				    "u > %" INT64_T_FORMAT "u = %d\n",
				    CAST(unsigned long long, v),
				    CAST(unsigned long long, l), matched);
		}
		else {
			matched = CAST(int64_t, v) > CAST(int64_t, l);
			if ((ms->flags & MAGIC_DEBUG) != 0)
				(void) fprintf(stderr, "%" INT64_T_FORMAT
				    "d > %" INT64_T_FORMAT "d = %d\n",
				    CAST(long long, v),
				    CAST(long long, l), matched);
		}
		break;
			matched = v < l;
			if ((ms->flags & MAGIC_DEBUG) != 0)
				(void) fprintf(stderr, "%" INT64_T_FORMAT
				    "u < %" INT64_T_FORMAT "u = %d\n",
				    CAST(unsigned long long, v),
				    CAST(unsigned long long, l), matched);
		}
		else {
			matched = CAST(int64_t, v) < CAST(int64_t, l);
			if ((ms->flags & MAGIC_DEBUG) != 0)
				(void) fprintf(stderr, "%" INT64_T_FORMAT
				    "d < %" INT64_T_FORMAT "d = %d\n",
				     CAST(long long, v),
				     CAST(long long, l), matched);
		}
		break;
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void) fprintf(stderr, "((%" INT64_T_FORMAT "x & %"
			    INT64_T_FORMAT "x) == %" INT64_T_FORMAT
			    "x) = %d\n", CAST(unsigned long long, v),
			    CAST(unsigned long long, l),
			    CAST(unsigned long long, l),
			    matched);
		break;
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void) fprintf(stderr, "((%" INT64_T_FORMAT "x & %"
			    INT64_T_FORMAT "x) != %" INT64_T_FORMAT
			    "x) = %d\n", CAST(unsigned long long, v),
			    CAST(unsigned long long, l),
			    CAST(unsigned long long, l), matched);
		break;

		    m->reln);
		return -1;
	}

	return matched;
}

private int
handle_annotation(struct magic_set *ms, struct magic *m, int firstline)
{
	if ((ms->flags & MAGIC_APPLE) && m->apple[0]) {
		if (print_sep(ms, firstline) == -1)
	return 0;
}

private int
print_sep(struct magic_set *ms, int firstline)
{
	if (firstline)
		return 0;