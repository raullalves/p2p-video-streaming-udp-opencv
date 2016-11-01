#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

//max number of nodes in network. Arbitrary number
#define QTD_MAXIMA 999

//node class
class No{
	
	public:
	
		No(void);
		~No(void);
		void addNovoNo(char * ip, int port);
		void removerNo(char * ip);
		void exibirNos();
		int getQtdNos();
		char* getIP(int i);
		int getPorta(int i);
	
	private:
		int qtd_nos;
		char** ips;
		int* porta;
		
};
