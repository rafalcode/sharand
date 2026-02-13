CC=gcc
CFLAGS=-g -Wall
SPECLIBS=-lcairo -lm
CJPGLIBS=-lm -lcairo -lcairo_jpg -ljpeg # cairp +jpg libs
SPECINC=-I/home/nutria/mylocal/include
SPECINC2=-I/usr/include/cairo
EXECUTABLES=ra0 ra2 linestar scall ls2 lsr2 lsr2f

# ra2 and linestar taken from other repos.
ra0: ra0.c
	${CC} ${CFLAGS} -o $@ $^
ra2: ra2.c
	${CC} ${CFLAGS} -o $@ $^

linestar: linestar.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
ls2: ls2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# by chance, my naive work on ls2 produced what looks like a scallop shell, by chance.
# I worked it out. line_to(x0, x0) - see the two x0's? that was why.
scall: scall.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}

# now that lsr is working correctly (though unevens don't sit on horizontal well).
# we can introduce a little randomness.
lsr2: lsr2.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# OK lsr2.c is a reasonable attempt at irregularly shaped boulders.
# but it should function-ified, therefore:
lsr2f: lsr2f.c
	${CC} ${CFLAGS} -o $@ $^ ${SPECLIBS}
# when you function-ify you nearly always 

# by chance, my naive work on ls2 produced what looks like a scallop shell, by chance.
.PHONY: clean

clean:
	rm -f ${EXECUTABLES}
