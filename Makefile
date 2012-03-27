gXipmsg : main.o udp.o pack.o sendForm.o
	cc -o gXipmsg.exe main.o udp.o pack.o sendForm.o -lXm -lXt -lSM -lICE -lX11
             
main.o : main.c gXipmsg.h
	cc -c main.c
	
udp.o : udp.c udp.h 
	cc -c udp.c	
	
pack.o : pack.c pack.h 
	cc -c pack.c	

sendForm.o : sendForm.c sendForm.h 
	cc -c sendForm.c
	
clean:
	rm -f *.s *.o *.exe *.stackdump