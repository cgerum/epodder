AUTOMAKE_OPTIONS     = 1.4 foreign

MAINTAINERCLEANFILES = Makefile.in

INCLUDES = @EPODDER_CFLAGS@

bin_PROGRAMS = epodder

epodder_SOURCES = fileselector.c  filetransfer.c  mainwindow.c  \
	          playlist.c  podcasts.c config_files.c song.c \
		  player.c 

epodder_LDADD = @EPODDER_LIBS@
