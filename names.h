/*
 * vim: ts=8 sw=8
 */

#ifndef	NAMES_H
# define NAMES_H

typedef struct	{
	char const * const	name;
	char const * const	desc;
} Name_t;

extern	Name_t	names[];
extern	int	nNames;

#endif	/* NAMES_H */
