gXipmsg : main.o udp.o pack.o sendForm.o recvDialog.o
	cc -g -o gXipmsg main.o udp.o pack.o sendForm.o recvDialog.o -lXm -lXt -lSM -lICE -lX11
             
main.o : main.c gXipmsg.h
	cc -g -c main.c
	
udp.o : udp.c udp.h 
	cc -g -c udp.c	
	
pack.o : pack.c pack.h 
	cc -g -c pack.c	

sendForm.o : sendForm.c sendForm.h 
	cc -g -c sendForm.c

recvDialog.o : recvDialog.c recvDialog.h 
	cc -g -c recvDialog.c

clean : 
	rm -f *.s *.o *.exe *.stackdump
