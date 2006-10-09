# vim: ts=8 sw=8

PREFIX	=${HOME}/opt
BINDIR	=${PREFIX}/bin

CC	=ccache gcc -march=i686
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
	./howto-grab_signal_names /usr/include/bits/signum.h >$@.tmp && \
		move-if-change $@.tmp $@

clean::
	${RM} *.o core.* lint tags a.out
	${RM} names.c

distclean clobber:: clean
	${RM} signame

check::	signame
	./signame 13
	./signame

install:: signame
	install -d ${BINDIR}
	install -c -s signame ${BINDIR}/

uninstall::
	${RM} ${BINDIR}/signame
