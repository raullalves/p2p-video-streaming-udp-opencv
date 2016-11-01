#include <opencv2/imgproc.hpp>
#define _WIN32_WINNT 0x0A00
#include <Ws2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <process.h>
#include "No.h"
#include <iostream>
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#define FRAME_HEIGHT 720
#define FRAME_WIDTH 1280
#define FRAME_INTERVAL (1000/30)
#define UDP_PACK_SIZE 4096 
#define ENCODE_QUALITY 80
#define TAMANHO_BUFFER 65540

using namespace cv;
using namespace std;

#pragma comment (lib, "Ws2_32.lib")

class Peer
{

	WSADATA wsaData, wsaVideo;
	SOCKET socketUdp, socketVideo;

	char msgBroadcast[16];
	char msgAdmissao[16];
	char msgSaida[16];
	int len = sizeof(struct sockaddr_in);
	int PORT = 7002;
	
public:

	No * no;
	Peer(void);
	~Peer(void);
	bool buscar_bool;
	bool avisar_bool;
	void buscar();
	void avisar();
	void sair();
	void receberVideo();
	void conectarPeer(char* ip, int port);
	struct sockaddr_in Recv_addr;
	struct sockaddr_in Sender_addr;
	struct sockaddr_in ip_atual;
	char* ip_destino;
	int porta_destino;
	
private:

	static void __cdecl temp(void * params);

};