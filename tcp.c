// created by: geo (September 2012)
#include "tcp.h"


int tcp_InitClient(struct RecvClientData* data)
{
	int reuse = 1;
	int buff_size;
	int buff_minsize;
	
	// Create socket
	if((data->dSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("error: socket(SOCK_STREAM)");
		return -1;
	}
		
	// Create socket address from
	TCP_AddrRemoteServ.sin_family = TCP_DEFAULT_FAMILY;
	TCP_AddrRemoteServ.sin_port = htons(TCP_DEFAULT_PORT);
			
	// Set IP of socket address of server
	if((TCP_AddrRemoteServ.sin_addr.s_addr = inet_addr(data->dServerInfo.IP_Address)) == -1)
	{
		printf("error: inet_addr(%s)\n", data->dServerInfo.IP_Address);		
		return -1;
	}
	
	// Connect socket 
	if((connect(data->dSocket, (struct sockaddr*)&TCP_AddrRemoteServ, sizeof(TCP_AddrRemoteServ))) == -1)
	{
		tcp_CloseClient(data);
		printf("error: connect(tcp)");
		return -1;
	}
	
	// Set reuse address option 
	if ((data->dSocket != -1) && setsockopt(data->dSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
	{
		printf("error: setsockopt(tcp, reuseaddr)");
		return -1;
	}
	
	// Set TCP send buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(data->dSocket, SOL_SOCKET, SO_SNDBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(data->dSocket, SOL_SOCKET, SO_SNDBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(tcp, SOL_SOCKET, SENDSIZE)");
		return -1;
	}
		 
	// Set TCP recv buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(data->dSocket, SOL_SOCKET, SO_RCVBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(data->dSocket, SOL_SOCKET, SO_RCVBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(tcp, SOL_SOCKET, RECVSIZE)");
		return -1;
	}
					
	return 0;
}


void tcp_CloseClient(struct RecvClientData* ptrData)
{
	// Close socket
	tcp_Close(ptrData->dSocket);
}


int tcp_WriteClient(struct RecvClientData* ptrData, char* ptrBuff, int mSize)
{
	return tcp_Write(ptrData->dSocket, ptrBuff, mSize);
}


int tcp_ReadClient(struct RecvClientData* ptrData, char* ptrBuff, int mSize)
{
	return tcp_Read(ptrData->dSocket, ptrBuff, mSize);
}



int tcp_InitListener(void)
{
	int reuse = 1;
	int buff_size;
	int buff_minsize;
	
	// Create socket
	if((TCP_SockListener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("error: socket(SOCK_STREAM)");
		return -1;
	}
		
	// Create socket listener address
	TCP_AddrLocalServ.sin_family = TCP_DEFAULT_FAMILY;
	TCP_AddrLocalServ.sin_port = htons(TCP_DEFAULT_PORT);
	TCP_AddrLocalServ.sin_addr.s_addr = TCP_DEFAULT_IPADDR;
			
	// BInd socket 
	if((bind(TCP_SockListener, (struct sockaddr*)&TCP_AddrLocalServ, sizeof(TCP_AddrLocalServ))) == -1)
	{
		tcp_Close(TCP_SockListener);
		printf("error: connect(tcp)");
		return -1;
	}
	
	// Set reuse address option 
	if ((TCP_SockListener != -1) && setsockopt(TCP_SockListener, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) != 0)
	{
		printf("error: setsockopt(tcp, reuseaddr)");
		return -1;
	}
	
	// Set TCP send buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(TCP_SockListener, SOL_SOCKET, SO_SNDBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(TCP_SockListener, SOL_SOCKET, SO_SNDBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(tcp, SOL_SOCKET, SENDSIZE)");
		return -1;
	}
		 
	// Set TCP recv buffer size
	buff_size = _TCP_BUF_SIZE;
	buff_minsize = _TCP_BUF_MIN_SIZE;
	if((setsockopt(TCP_SockListener, SOL_SOCKET, SO_RCVBUF, (void*)&buff_size, sizeof(int))) != 0 && (setsockopt(TCP_SockListener, SOL_SOCKET, SO_RCVBUF, (void*)&buff_minsize, sizeof(int))) != 0)
	{
		printf("error: setsockopt(tcp, SOL_SOCKET, RECVSIZE)");
		return -1;
	}
		
	// Start listen
	listen(TCP_SockListener, TCP_LISTEN_LEN);
	
	return 0;
}


void tcp_CloseListener(void)
{
	tcp_Close(TCP_SockListener);
}


void tcp_Close(int mSocket)
{
	// Close socket
	if(mSocket != -1)
	{
		close(mSocket);
		mSocket = -1;
	}
}


int tcp_Write(int mSocket, char* ptrBuff, int mSize)
{
	return write(mSocket, ptrBuff, mSize);
}


int tcp_Read(int mSocket, char* ptrBuff, int mSize)
{
	return read(mSocket, ptrBuff, mSize);
}




void tcp_InquirePackets(void)
{
	char* TCP_Buffer;
	int cliSocket = -1;
	struct sockaddr_in cli_addr;
	socklen_t clilen;
	
	struct SendClientData* pNum;
	int addrNum;
	int mUserIdx = 0;
	int mItemIdx = 0;
	
	struct stat st;
	FILE* fpRead;
	int mFileSize = 0;
	int mProgSize = 0;
	int mTcpRet = 0;

	while(recvfromTimeOutUDP(TCP_SockListener, 0, 0) > 0)
	{		
		if((cliSocket = accept(TCP_SockListener, (struct sockaddr *) &cli_addr, &clilen)) != -1)
		{	
			// Allocate mem for buffer
			TCP_Buffer = malloc(TCP_FILE_BUFSIZ);
			
			// Clear buffer
			memset(TCP_Buffer,'\0',TCP_FILE_BUFSIZ);
				
			// Ok the data is ready, call recvfrom() to get it then
			tcp_Read(cliSocket, TCP_Buffer, TCP_FILE_BUFSIZ);			
					    
		    pack_UnpackBroadcast(TCP_Buffer, &TCP_DataFrom);	
		    
		    // Search LList by PacketID
		    if(appIcon_SearchList(&addrNum, TCP_DataFrom.Handlename))
		    {
		    	pNum = (struct SendClientData*)addrNum;
		    	printf("found packet: %s\n",pNum->PacketID);
		    	
		    	// Search node by Hostname
		    	if(appIcon_SearchNode(pNum, &mUserIdx, TCP_DataFrom.Hostname))
		    	{
		    		printf("found user: %i\n",mUserIdx);
		    		
		    		// Search file for FileID
		    		if(appIcon_SearchItems(pNum, &mItemIdx, TCP_DataFrom.Extended))
		    		{
		    			printf("found item: %i\n",mItemIdx);
		    			
		    			stat(pNum->apItemList[mItemIdx],&st);
		    			mFileSize = (int)st.st_size;
		    			mProgSize = 0;
		    			mTcpRet = 0;
		    			fpRead = fopen(pNum->apItemList[mItemIdx], "rb");
		    			
		    			// Clear buffer
						memset(TCP_Buffer,'\0',TCP_FILE_BUFSIZ);
		    			
		    			// Decode command
					    switch(GET_MODE(TCP_DataFrom.IP_Flags))
						{							
							case IPMSG_GETFILEDATA:
								
								while(mFileSize > mProgSize)
								{
									mTcpRet = fread(TCP_Buffer, sizeof(TCP_Buffer[0]), TCP_FILE_BUFSIZ, fpRead);									
									mTcpRet = tcp_Write(cliSocket, TCP_Buffer, mTcpRet);																	
									mProgSize += mTcpRet;
									printf("send %s %i bytes\n", pNum->apItemList[mItemIdx], mProgSize);
								}
								
								// Close file
								fclose(fpRead);
								break;
								
							case IPMSG_GETDIRFILES:
								
								break;					
							
								
							default:
								printf("unknown TCP command: %s\n", TCP_Buffer);
						}		    			
		    					    			
		    			if(pNum->dItemsLeft[mUserIdx] > 0)
		    				pNum->dItemsLeft[mUserIdx] -= 1;		    			
		    			sendDialog_Destroy(NULL, (XtPointer) pNum, NULL);
		    		}		    		
		    	}
		    }		
			
			// Release buffer memory
			free(TCP_Buffer);
			
			// Close socket
			tcp_Close(cliSocket);
		}		
	}		
}

