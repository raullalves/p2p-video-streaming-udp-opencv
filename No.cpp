#include "No.h"

//constructor
No::No(void){
	
	qtd_nos = 0;
	ips = new char*[QTD_MAXIMA];
	porta = new int[QTD_MAXIMA];
	
}

//destructor
No::~No(void){
	
	for (int i = 0; i < qtd_nos; i++)
		delete[] ips[i];
	delete[] ips;
	delete[] porta;
	
}

//add new node
void No::addNovoNo(char * ip, int port){
	
	bool noJaExiste = false;
	
	for (int i = 0; (i < qtd_nos) && !(noJaExiste); i++)
		if (strcmp(ips[i],ip) == 0)
			noJaExiste = true;
		
	if (!noJaExiste){
		ips[qtd_nos] = ip;
		porta[qtd_nos] = port;
		qtd_nos++;
	}
	
}

//remove node
void No::removerNo(char * ip){
	
	for (int i = 0; i < qtd_nos; i++){
		
		if (strcmp(ips[i],ip) == 0){
			
			qtd_nos--;
			if(i != qtd_nos){
				ips[i] = ips[qtd_nos];
				porta[i] = porta[qtd_nos];
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
	
	return porta[i];
	
}

//show friend list
void No::exibirNos(){
	
	for (int i = 0; i<qtd_nos; i++)
		cout<<"no numero "<<i<<endl<<"ip = "<<ips[i]<<endl<<"porta= "<<porta[i]<<endl;
	
}

//returns total quantity of nodes in network
int No::getQtdNos(){
	
	return qtd_nos;
	
}
	