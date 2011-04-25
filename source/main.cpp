#include "../headers/includes.h"
#include "server.cpp"

using namespace std;

int main(int argc, char** argv){
	if(argv[1] == NULL){
		cout<<"Ussage:\n\tserver [port]"<<endl;
		return 0;
	}
	int port = atoi(argv[1]);
	server s(port);
	s.openSocket();
	s.bindAndListen();
	return 1;
}

