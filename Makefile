DEBUG = -g
INCDIR =
LIBDIR =
FLAGS = -lXm -lXt -lSM -lICE -lX11
BINDIR = /usr/bin/
XPMDIR = /etc/gXipmsg/

gXipmsg : main.o udp.o tcp.o pack.o appIcon.o sendDialog.o recvDialog.o
	cc $(INCDIR) $(DEBUG) -o gXipmsg main.o udp.o tcp.o pack.o appIcon.o sendDialog.o recvDialog.o $(LIBDIR) $(FLAGS)

main.o : main.c main.h gXipmsg.h
	cc $(INCDIR) $(DEBUG) -c main.c

udp.o : udp.c udp.h 
	cc $(INCDIR) $(DEBUG) -c udp.c	
	
tcp.o : tcp.c tcp.h 
	cc $(INCDIR) $(DEBUG) -c tcp.c

pack.o : pack.c pack.h 
	cc $(INCDIR) $(DEBUG) -c pack.c	

appIcon.o : appIcon.c appIcon.h 
	cc $(INCDIR) $(DEBUG) -c appIcon.c

sendDialog.o : sendDialog.c sendDialog.h 
	cc $(INCDIR) $(DEBUG) -c sendDialog.c

recvDialog.o : recvDialog.c recvDialog.h 
	cc $(INCDIR) $(DEBUG) -c recvDialog.c

clean : 
	rm -f gXipmsg *.s *.o *.exe *.stackdump
	
install :
	cp gXipmsg $(BINDIR)
	mkdir $(XPMDIR)
	cp ipmsg.xpm $(XPMDIR)
	
uninstall :
	rm $(BINDIR)gXipmsg
	rm $(XPMDIR)ipmsg.xpm
	rm -r $(XPMDIR)

