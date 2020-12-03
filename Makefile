CC=gcc
CFLAGS=-framework ApplicationServices -framework Carbon
SOURCES=mouselogger.c
EXECUTABLE=mouselogger
INSTALLDIR=~/bin
LOGSPATH=~/.cache/mousekeylogs

compile: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install:
	mkdir -p $(INSTALLDIR)
	cp $(EXECUTABLE) $(INSTALLDIR)
	mkdir -p $(LOGSPATH)

uninstall:
	rm $(INSTALLDIR)/$(EXECUTABLE)

clean:
	[ -f $(EXECUTABLE) ] && rm $(EXECUTABLE) || echo ""
