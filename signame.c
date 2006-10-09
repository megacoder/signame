/*
 * vim: ts=8 sw=8
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <names.h>

static	char *		me = "signame";
static	unsigned	debugLevel;
static	unsigned	multi;

static	void
process(
	char *		s
)
{
	int		signo;


	signo = -1;
	if( !strncasecmp( s, "SIG", 3 ) )	{
		Name_t *	n;
		Name_t * const	lastName = names + nNames;

		++multi;
		for( n = names; n < lastName; ++n )	{
			if( n->name && !strcasecmp( s, n->name ) )	{
				signo = n - names;
				break;
			}
		}
	} else	{
		signo = (int) strtoul( s, NULL, 0 );
	}
	if( multi )	{
		printf( "%d\t", signo );
	}
	if( (signo > 0) && (signo < nNames) )	{
		Name_t * const	n = names + signo;

		if( n->name )	{
			printf( "%-10s\t%s\n", n->name, n->desc );
		} else	{
			printf( "DUNNO %d\n", signo );
		}
	} else	{
		printf( "DUNNO %d\n", signo );
	}
}

int
main(
	int		argc,
	char * *	argv
)
{
	char *		bp;
	int		c;

	/* Set process name						*/
	me = argv[ 0 ];
	if( (bp = strrchr( me, '/' )) != NULL )	{
		me = bp + 1;
	}
	/* Process command line arguments				*/
	opterr = 0;
	while( (c = getopt( argc, argv, "D" )) != EOF )	{
		switch( c )	{
		default:
			fprintf(
				stderr,
				"%s: switch -%c not implemented yet.\n",
				me,
				c
			);
			exit( 1 );
		case '?':
			fprintf(
				stderr,
				"%s: unknown switch -%c!\n",
				me,
				optopt
			);
			exit( 1 );
		case 'D':
			++debugLevel;
			break;
		}
	}
	/* Remainder of command line are arg numbers to decode		*/
	if( optind < argc )	{
		if( (argc - optind) > 1 )	{
			++multi;
		}
		while( optind < argc )	{
			optarg = argv[ optind++ ];
			process( optarg );
		}
	} else	{
		/* Args, spill our guts					*/
		int	signo;

		++multi;
		for( signo = 1; signo < nNames; ++signo )	{
			char	buf[ BUFSIZ ];

			sprintf( buf, "%d", signo );
			process( buf );
		}
	}
	return( 0 );
}
