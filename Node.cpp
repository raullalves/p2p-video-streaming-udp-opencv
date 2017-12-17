#include "Node.h"
using namespace std;

//add new node
void Node::addNewNode(char * ip, int port){
	
	bool alreadyExists = false;
	
	for (int i = 0; (i < qtd_nos) && !(alreadyExists); i++)
		if (strcmp(ips[i],ip) == 0)
			alreadyExists = true;
		
	if (!alreadyExists){
		ips[qtd_nos] = ip;
		ports[qtd_nos] = port;
		qtd_nos++;
	}
	
}

//remove node
void Node::removeNode(char * ip){
	
	for (int i = 0; i < qtd_nos; i++){
		
		if (strcmp(ips[i],ip) == 0){
			
			qtd_nos--;
			if(i != qtd_nos){
				ips[i] = ips[qtd_nos];
				ports[i] = ports[qtd_nos];
			}
			
		}	
		
	}	
}

//returns ip
char * Node::getIP(int i){
	
	return ips[i];
	
}

//returns port number
int Node::getPorta(int i){
	
	return ports[i];
	
}

//show friend list
void Node::exibirNos(){
	
	for (int i = 0; i<qtd_nos; i++)
		cout<<"Node number "<<i<<endl<<"ip = "<<ips[i]<<endl<<"port= "<<ports[i]<<endl;
	
}

//returns total quantity of nodes in network
int Node::getQtdNos(){
	
	return qtd_nos;
	
}