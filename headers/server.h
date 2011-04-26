#ifndef __SERVER_SOCKET
#define __SERVER_SOCKET

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

class server{
	private:
		int sockfd, newsockfd, port, sockReturn, pid;
		char buffer[256];
		socklen_t clilen;
		struct sockaddr_in serv_addr, cli_addr;
		
		bool _acceptCon();
		char* _readSock();
		bool _writeSock(char*);
		bool _fork();
		void _conHandler(int);
		
	public:
		server(int);
		~server();
		bool openSocket();
		bool bindAndListen();
		
};

#endif
