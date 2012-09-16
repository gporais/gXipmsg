//created: geo (August 2012)
https://github.com/gorais/gXipmsg.git


gXipmsg is a Motif version of the wonderful tool IPMsg found on this site: http://ipmsg.org/index.html.en
This project taught me a lot about Motif and TCP/UDP. The goal was to design an application that can be build and run
on all *nix platforms with as much as possible no need of modifiyng anything, as inspired by the O'Reilly book and sample codes.

The main goal for this project is to utilize the fast and easy file transfer on any *nix system between other platforms without
setting up NFS,FTP,SAMBA or other client-server apps for this purpose. 


Release history:
	
BETA 1.0:
	* Very fast download of multiple files
	* Optimized memory handling
	* Optimized widget handling
	* Optimized UDP/TCP handling

ALPHA 1.0:
	* More stable and bug fixes
	* Enhanced GUI
	* Enhance architecture to support all UNIX flavors

APLHA:
	* Messaging thru UDP protocol
	* Can broadcast message to specific people

	
gXipmsg was tested on the following:
1. Intel x86: 
	* Windows XP through Cygwin
	* Solaris 10 through VMWare
	* FreeBSD 9 with OpenMotif through VBox
	* Ubuntu 12.04 with OpenMotif through VBox 

2. MIPS:
	* IRIX 6.5 on SGI O2 and Octane

If you have any chance to try this on other platform, i'll be delighted to hear your feedback :)
You can contact me via email: orais.georgephillip@gmail.com

To try, please download the Windows version on your Windows box.
Then build gXipmsg using make or GNU make with Makefile.
Please note, BSD and SUN has its own Makefile, please use this with -f option.
General step is:
	make
	make install
	
Binary file will be copied to /usr/bin/
Folder structure will be consturcerd under /etc/
	/etc
		/gXipmsg
			ipmsg.xpm
			/Downloads
			
To run: gXipmsg <handlename>	(eg. gXipmsg geo)
If no handlename specified, your login name is automatically used.
	

Hope you enjoy trying this as much i enjoyed coding this, thanks!!!
