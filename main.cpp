//Developed by Raul Lima Alves
//Computer Engineering Student in Brazil

#include "Peer.h"
#include <process.h>
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
void avisarNos(void* pParams) {
	
	while (peer->avisar_bool) {
		peer->avisar();
	}
	
}

//method to find new nodes in network
void buscarNos(void* pParams) {
	
	while (peer->buscar_bool) {
		peer->buscar();
	}
	
}

//show main menu
void mostrarMenu() {

	char *connected_ip = inet_ntoa(peer->ip_atual.sin_addr);
	int porta = ntohs(peer->ip_atual.sin_port);
	cout << endl << "Voce esta conectado no ip " << connected_ip << " atraves da porta " << porta << endl;
	cout << "\t\tMENU" << endl;
	cout << "1 - Listar peers na rede local" << endl;
	cout << "2 - Iniciar Stream de video com alguem" << endl;
	cout << "3 - Sair" << endl;
	cout << "Digite a opcao desejada: ";

}

//get user menu option
int obterOpcao() {

	int opcao;
	cin >> opcao;
	return opcao;
}

//choses friend in node list to stream
void escolherNo() {
	
	system("cls");
	cout << "Escolha o usuario desejado: " << endl;
	peer->no->exibirNos();
	cout << "Digite o numero do no desejado: " << endl;
	int numero;
	cin >> numero;
	char* ip = peer -> no -> getIP(numero);
	int porta = peer -> no -> getPorta(numero);
	peer->conectarPeer(ip, porta);

}

//main function
int main() {

	int opcao;
	
	peer = new Peer();
	
	_beginthread(avisarNos, 0, NULL);
	_beginthread(buscarNos, 0, NULL);
	
	do {
		
		system("cls");
		mostrarMenu();
		opcao = obterOpcao();
		
		switch (opcao) {
			
		case 1:
			peer->no->exibirNos();
			system("PAUSE");
			break;
			
		case 2:
			escolherNo();
			break;
			
		case 3:
			cout << "Saindo da rede..." << endl;
			peer->sair();
			delete peer;
			return 0;
			break;
			
		default:
			cout << endl << "Opcao incorreta..." << endl;
			Sleep(2000);
			break;
			
		}

	} while (opcao != 3);
	
	delete peer;
	return 0;
}