gXipmsg : main.o udp.o pack.o
	cc -o gXipmsg.exe main.o udp.o pack.o
             
main.o : main.c gXipmsg.h
	cc -c main.c
	
udp.o : udp.c udp.h 
	cc -c udp.c	
	
pack.o : pack.c pack.h 
	cc -c pack.c	

	
clean:
	rm -f *.s *.o *.exe