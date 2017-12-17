#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
//max number of nodes in network. Arbitrary number
#define QTD_MAXIMA 999

//node class
class Node{
	
	public:
	
		Node(void){
			qtd_nos = 0;
			ips = new char*[QTD_MAXIMA];
			ports = new int[QTD_MAXIMA];
		}

		~Node(void){
			for (int i = 0; i < qtd_nos; i++)
				delete[] ips[i];
			delete[] ips;
			delete[] ports;
		}

		void addNewNode(char * ip, int port);
		void removeNode(char * ip);
		void exibirNos();
		int getQtdNos();
		char* getIP(int i);
		int getPorta(int i);
	
	private:
		int qtd_nos;
		char** ips;
		int* ports;
};
