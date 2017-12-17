//Developed by Raul Lima Alves
//Computer Engineer

#include "Peer.h"
#include <pthread.h>
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;
using namespace cv;

//peer object
Peer * peer;

//method to show that you are in the network
void *tellYouAreInTheNetwork(void* pParams) {
	
	while (peer->tellNetwork_Boolean) {
		peer->tellOtherPeers();
	}
	
}

//method to find new nodes in network
void *findWhoIsInTheNetwork(void* pParams) {
	
	while (peer->findNetwork_Boolean) {
		peer->findOtherPeers();
	}
	
}

//show main menu
void showMenu() {

	char *connected_ip = inet_ntoa(peer->ip_current.sin_addr);
	int port = ntohs(peer->ip_current.sin_port);
	cout << endl << "You are connected at " << connected_ip << " : " << port << endl;
	cout << "\t\tMENU" << endl;
	cout << "1 - List peers" << endl;
	cout << "2 - Begin Stream with someone" << endl;
	cout << "3 - Exit" << endl;
	cout << "Choose your option: ";

}

//get user menu option
int getOption() {

	int option;
	cin >> option;
	return option;
}

//choses friend in node list to stream
void chooseConnection() {
	
	system("clear");
	cout << "Which one would you like to stream? " << endl;
	peer->node->exibirNos();

	cout << "Select the Peer`s number: " << endl;
	int number;
	cin >> number;
	char* ip = peer -> node -> getIP(number);
	int port = peer -> node -> getPorta(number);
	peer->connectPeer(ip, port);

}

//main function
int main(int argc, char *argv[]) {

	int option;
	int i,j;
	peer = new Peer();

	pthread_t threads[2];
	pthread_create( &threads[0], NULL, tellYouAreInTheNetwork,(void *)i);
	pthread_create( &threads[1], NULL, findWhoIsInTheNetwork, (void *)j);
	system("clear");
	do {
		
		
		showMenu();
		option = getOption();
		
		switch (option) {
			
		case 1:
			peer->node->exibirNos();
			getchar();
			break;
			
		case 2:
			chooseConnection();
			break;
			
		case 3:
			cout << "Saindo da rede..." << endl;
			peer->leave();
			delete peer;
			exit(0);
			
		default:
			cout << endl << "Opcao incorreta..." << endl;
			sleep(2000);
			break;
			
		}

	} while (option != 3);
	
	delete peer;
	return 0;
}