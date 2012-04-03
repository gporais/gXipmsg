gXipmsg : main.o udp.o pack.o sendForm.o recvDialog.o
	cc -o gXipmsg main.o udp.o pack.o sendForm.o recvDialog.o -lXm -lXt -lSM -lICE -lX11
             
main.o : main.c gXipmsg.h
	cc -c main.c
	
udp.o : udp.c udp.h 
	cc -c udp.c	
	
pack.o : pack.c pack.h 
	cc -c pack.c	

sendForm.o : sendForm.c sendForm.h 
	cc -c sendForm.c

recvDialog.o : recvDialog.c recvDialog.h 
	cc -c recvDialog.c

clean : 
	rm -f *.s *.o *.exe *.stackdump
