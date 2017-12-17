#define FRAME_HEIGHT 720
#define FRAME_WIDTH 1280
#define FRAME_INTERVAL (1000/30)
#define UDP_PACK_SIZE 4096 
#define ENCODE_QUALITY 80
#define TAMANHO_BUFFER 65540

#include "Node.h"

class Peer
{
	int socketUdp, socketVideo;
	char msgBroadcast[16];
	char msgAdmissao[16];
	char msgSaida[16];
	socklen_t len = sizeof(struct sockaddr_in);
	int PORT = 7002;
	pthread_t thread[1];
	
public:
	
	Node * node;
	Peer(void){

		findNetwork_Boolean = true;
		tellNetwork_Boolean = true;
		std::string mensagemP2p = "GettingInside";

		strcpy(msgBroadcast, mensagemP2p.c_str());
		strcpy(msgAdmissao, mensagemP2p.c_str());

		std::string mensagemSaindo = "Leaving";
		strcpy(msgSaida, mensagemSaindo.c_str());

		node = new Node();

		socketUdp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (socketUdp < 0) 
        	error("ERROR opening socket");
		int broadcastEnable=1;
	
		if (setsockopt(socketUdp, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) < 0)
		{
			error("Error setting socket to broadcast");
		}

		Recv_addr.sin_family = AF_INET;
		Recv_addr.sin_port = htons(PORT);
		Recv_addr.sin_addr.s_addr = INADDR_ANY;
		Sender_addr.sin_family = AF_INET;
		Sender_addr.sin_port = htons(PORT);
		Sender_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

		if (bind(socketUdp, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
		{
			error("Error binding socket");
		}

		char nomePc[80];
	
		if (gethostname(nomePc, sizeof(nomePc)) == -1) {
			error("Error getting hostname");
		}
		std::cout<<nomePc;
	
		struct hostent *host = gethostbyname(nomePc);
	
		if (host == 0) {
			error("Host error");
		}

		if (host->h_addr_list[0] == 0) {
			error("Error");
		}

		struct in_addr addr;
	
		memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));

		ip_current.sin_family = AF_INET;
		ip_current.sin_port = htons(PORT);
		ip_current.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

		std::cout << "Peer created" << std::endl;
	}

	static void *getVideoWrapper(void *context)
    {
        return ((Peer *)context)->getVideo();
    }

	bool findNetwork_Boolean;
	bool tellNetwork_Boolean;
	void findOtherPeers();
	void tellOtherPeers();
	void leave();
	void *getVideo();
	void connectPeer(char* ip, int port);
	struct sockaddr_in Recv_addr;
	struct sockaddr_in Sender_addr;
	struct sockaddr_in ip_current;
	char* ip_destino;
	int porta_destino;
	
private:

	void error(const char *msg);

};