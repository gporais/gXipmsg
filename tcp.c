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
	
	struct SendClientData* pNum = NULL;
	int addrNum = 0;
	int mUserIdx = 0;
	int mItemIdx = 0;	
	struct stat st;

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
		    	
		    	// Search node by Hostname
		    	if(appIcon_SearchNode(pNum, &mUserIdx, TCP_DataFrom.Hostname))
		    	{   		
		    		// Search file for FileID
		    		if(appIcon_SearchItems(pNum, &mItemIdx, TCP_DataFrom.Extended))
		    		{
		    			stat(pNum->apItemList[mItemIdx],&st);
		    			
		    			pNum->dTCPData[mUserIdx].dFileSize = (int)st.st_size;
						pNum->dTCPData[mUserIdx].dProgSize = 0;
						pNum->dUserIdx = mUserIdx;
		    			pNum->dTCPData[mUserIdx].dfpRead = fopen(pNum->apItemList[mItemIdx], "rb");
		    			
		    			// Clear buffer
						memset(TCP_Buffer,'\0',TCP_FILE_BUFSIZ);
						pNum->dTCPData[mUserIdx].dBuffer = TCP_Buffer;						
						
						pNum->dTCPData[mUserIdx].dSocket = cliSocket;						
		    			
		    			// Decode command
					    switch(GET_MODE(TCP_DataFrom.IP_Flags))
						{							
							case IPMSG_GETFILEDATA:								
								
								pNum->dTCPData[mUserIdx].dWorkID = XtAppAddWorkProc(GXIM_App, tcp_SendProcedure, (XtPointer)pNum);								
								break;
								
							case IPMSG_GETDIRFILES:
								
								break;					
							
								
							default:
								printf("unknown TCP command: %s\n", TCP_Buffer);
						}	
		    		}		    		
		    	}
		    }
		}		
	}		
}



Boolean tcp_SendProcedure(XtPointer client_data)
{
	struct SendClientData* data = (struct SendClientData*) client_data;
	int mTcpRet = 0;
	int mUserIdx = data->dUserIdx;
	Boolean bRet = False;
	
	mTcpRet = fread(data->dTCPData[mUserIdx].dBuffer, sizeof(data->dTCPData[mUserIdx].dBuffer[0]), TCP_FILE_BUFSIZ, data->dTCPData[mUserIdx].dfpRead);									
	mTcpRet = tcp_Write(data->dTCPData[mUserIdx].dSocket, data->dTCPData[mUserIdx].dBuffer, mTcpRet);																	
	data->dTCPData[mUserIdx].dProgSize += mTcpRet;
		
	if(data->dTCPData[mUserIdx].dFileSize <= data->dTCPData[mUserIdx].dProgSize)
	{
		// Done
		XtRemoveWorkProc(data->dTCPData[mUserIdx].dWorkID);
		bRet = True;
	
		// Close file
		fclose(data->dTCPData[mUserIdx].dfpRead);
		
		if(data->dItemsLeft[mUserIdx] > 0)
		{
			data->dItemsLeft[mUserIdx] -= 1;
		}
		
		// Release buffer memory
		free(data->dTCPData[mUserIdx].dBuffer);
		
		// Close socket
		tcp_Close(data->dTCPData[mUserIdx].dSocket);
		
		sendDialog_Destroy(NULL, client_data, NULL);
	}
	
	return bRet;
}

