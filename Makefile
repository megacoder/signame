# vim: ts=8 sw=8

PREFIX	=/opt
BINDIR	=${PREFIX}/bin

CC	=gcc -std=gnu99
OPT	=-Os
CFLAGS	=${OPT} -Wall -g -I.
LDFLAGS	=-g
LDLIBS	=

all::	signame

names.o:: names.c names.h

signame.o:: signame.c names.h

signame:: signame.o names.o
	${CC} ${LDFLAGS} -o $@ signame.o names.o ${LDLIBS}

names.c:: Makefile howto-grab_signal_names names.h
	./howto-grab_signal_names /usr/include/bits/signum.h >$@

clean::
	${RM} *.o core.* lint tags a.out
	${RM} names.c

distclean clobber:: clean
	${RM} signame

check::	signame
	./signame 13
	./signame

install:: signame
	install -D -c -s signame ${BINDIR}/signame

uninstall::
	${RM} ${BINDIR}/signame
