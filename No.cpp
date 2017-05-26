#include "No.h"

//constructor
No::No(void){
	
	qtd_nos = 0;
	ips = new char*[QTD_MAXIMA];
	port = new int[QTD_MAXIMA];
	
}

//destructor
No::~No(void){
	
	for (int i = 0; i < qtd_nos; i++)
		delete[] ips[i];
	delete[] ips;
	delete[] port;
	
}

//add new node
void No::addNewNode(char * ip, int port){
	
	bool alreadyExists = false;
	
	for (int i = 0; (i < qtd_nos) && !(alreadyExists); i++)
		if (strcmp(ips[i],ip) == 0)
			alreadyExists = true;
		
	if (!alreadyExists){
		ips[qtd_nos] = ip;
		port[qtd_nos] = port;
		qtd_nos++;
	}
	
}

//remove node
void No::removeNode(char * ip){
	
	for (int i = 0; i < qtd_nos; i++){
		
		if (strcmp(ips[i],ip) == 0){
			
			qtd_nos--;
			if(i != qtd_nos){
				ips[i] = ips[qtd_nos];
				port[i] = port[qtd_nos];
			}
			
		}	
		
	}	
}

//returns ip
char * No::getIP(int i){
	
	return ips[i];
	
}

//returns port number
int No::getPorta(int i){
	
	return port[i];
	
}

//show friend list
void No::exibirNos(){
	
	for (int i = 0; i<qtd_nos; i++)
		cout<<"Node number "<<i<<endl<<"ip = "<<ips[i]<<endl<<"port= "<<port[i]<<endl;
	
}

//returns total quantity of nodes in network
int No::getQtdNos(){
	
	return qtd_nos;
	
}
	