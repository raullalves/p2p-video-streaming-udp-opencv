#include "Peer.h"

//construtor of peer class
Peer::Peer(void) {

	findNetwork_Boolean = true;
	tellNetwork_Boolean = true;
	string mensagemP2p = "GettingInside";

	strcpy(msgBroadcast, mensagemP2p.c_str());
	strcpy(msgAdmissao, mensagemP2p.c_str());

	string mensagemSaindo = "Leaving";
	strcpy(msgSaida, mensagemP2p.c_str());

	no = new No();
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	socketUdp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	char broadcast = 'a';
	
	if (setsockopt(socketUdp, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
	{
		cout << "Erro 1" << endl;
		closesocket(socketUdp);
		
	}

	Recv_addr.sin_family = AF_INET;
	Recv_addr.sin_port = htons(PORT);
	Recv_addr.sin_addr.s_addr = INADDR_ANY;
	Sender_addr.sin_family = AF_INET;
	Sender_addr.sin_port = htons(PORT);
	Sender_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

	if (bind(socketUdp, (sockaddr*)&Recv_addr, sizeof(Recv_addr)) < 0)
	{
		cout << "Erro 2" << endl;
		closesocket(socketUdp);
	}

	WSAData wsaData2;
	WSAStartup(MAKEWORD(1, 1), &wsaData2);
	char nomePc[80];
	
	if (gethostname(nomePc, sizeof(nomePc)) == SOCKET_ERROR) {
		cout << "Erro 4" << endl;
		WSACleanup();
		return;
	}
	cout<<nomePc;
	
	struct hostent *host = gethostbyname(nomePc);
	
	if (host == 0) {
		cout << "Erro 5" << endl;
		WSACleanup();
		return;
	}

	if (host->h_addr_list[0] == 0) {
		cout << "Erro 6" << endl;
		return;
	}

	struct in_addr addr;
	
	memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));

	ip_current.sin_family = AF_INET;
	ip_current.sin_port = htons(PORT);
	ip_current.sin_addr.s_addr = inet_addr(inet_ntoa(addr));

	cout << "Peer criado com sucesso" << endl;

}

//destrutor
Peer::~Peer(void) {

	closesocket(socketUdp);
	WSACleanup();

}

//Find new friends in network
void Peer::findOtherPeers()
{
	
	char recvBuff[50];
	int recvBuffLen = 50;
	while (findNetwork_Boolean)
	{
		struct sockaddr_in Recv_addr2;
		
		recvfrom(socketUdp, recvBuff, recvBuffLen, 0, (struct sockaddr*)&Recv_addr2, &len);
		
		char from_ip[1024];
		getnameinfo((struct sockaddr*)&Recv_addr2, sizeof(Recv_addr2), from_ip, 1024, NULL, NULL, 0);
		struct hostent *host = gethostbyname(from_ip);
		struct in_addr addr;
		
		if (host->h_addr_list[0] == 0) {
			cout << "Erro 6" << endl;
			return;
		}

		memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));
		struct sockaddr_in ipt;
		
		ipt.sin_family = AF_INET;
		ipt.sin_port = htons(PORT);
		ipt.sin_addr.s_addr = inet_addr(inet_ntoa(addr));
		
		char *connected_ip= inet_ntoa(ipt.sin_addr);
		string con_ip(connected_ip);
		
		char *meuIP = inet_ntoa(ip_current.sin_addr);
		string my_ip(meuIP);
		
		if ((strcmp(recvBuff, msgAdmissao) == 0) && !(my_ip.compare(con_ip) == 0)) {
			
			int port = PORT;
			char* temp_ip = new char[con_ip.length() + 1];
			strcpy(temp_ip, con_ip.c_str());
			no->addNewNode(temp_ip, port);

		}
		
		if ((strcmp(recvBuff, msgSaida) == 0) && !(my_ip.compare(con_ip) == 0)) {

			char* temp_ip = new char[con_ip.length() + 1];
			strcpy(temp_ip, con_ip.c_str());
			no->removeNode(temp_ip);

		}

	}

}

//tell broadcast you are in the netowrk
void Peer::tellOtherPeers()
{
	
	while (tellNetwork_Boolean)
	{
		if (sendto(socketUdp, msgBroadcast, strlen(msgBroadcast) + 1, 0, (sockaddr *)&Sender_addr, sizeof(Sender_addr)) < 0)
		{
			
			cout << "Erro 3" << endl;
			closesocket(socketUdp);
			
		}
		
		Sleep(5000);
	}

}

//leave the network
void Peer::leave() {
	string mensagemSaindo = "Leaving";
	strcpy(msgBroadcast, mensagemSaindo.c_str());
	Sleep(1500);
}

//get video
void Peer::getVideo() {
	
	sockaddr_in Video_addr;
	
	Video_addr.sin_family = AF_INET;
	Video_addr.sin_port = htons(porta_destino);
	Video_addr.sin_addr.s_addr = inet_addr(ip_destino);
	
	namedWindow("Video recebido", CV_WINDOW_AUTOSIZE);
	
	char buffer[TAMANHO_BUFFER]; 
	int tamanhoMensagem; 

	while (1) {
		
		//get the size of the video image
		do {
			
			tamanhoMensagem = recvfrom(socketUdp, buffer, TAMANHO_BUFFER, 0, (sockaddr *)&Video_addr, &len);
			
		} while (tamanhoMensagem > sizeof(int));
		
		int tamanho_pacote = ((int *)buffer)[0];
		
		char * buffer_video = new char[UDP_PACK_SIZE*tamanho_pacote];
		
		//get the video
		for (int i = 0; i < tamanho_pacote; i++) {
			
			tamanhoMensagem = recvfrom(socketUdp, buffer, TAMANHO_BUFFER, 0, (sockaddr *)&Video_addr, &len);
			
			//wrong data, it happens in udp
			if (tamanhoMensagem != UDP_PACK_SIZE) continue;
			
			memcpy(&buffer_video[UDP_PACK_SIZE*i], buffer, UDP_PACK_SIZE);
		}
		
		Mat matVideo = Mat(1, UDP_PACK_SIZE*tamanho_pacote, CV_8UC1, buffer_video);
		
		Mat frame_video = imdecode(matVideo, CV_LOAD_IMAGE_COLOR);
		
		//wrong data, it happens in udp
		if (frame_video.empty()) continue;
		
		imshow("Video recebido", frame_video);

		waitKey(1);
		
		free(buffer_video);

	}
	
}

//wrapper to start a thread with a class method
void __cdecl Peer::temp(void * params) {

		static_cast<Peer*>(params)->getVideo();
}

//connect to peer and send video daata
void Peer::connectPeer(char* ip, int port) {
	
	findNetwork_Boolean = false;
	tellNetwork_Boolean = false;
	
	ip_destino = ip;
	porta_destino = port;
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	socketVideo = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	Recv_addr.sin_family = AF_INET;
	Recv_addr.sin_port = htons(port);
	Recv_addr.sin_addr.s_addr = INADDR_ANY;

	sockaddr_in Send_addr_video;
	Send_addr_video.sin_family = AF_INET;
	Send_addr_video.sin_port = htons(port);
	Send_addr_video.sin_addr.s_addr = inet_addr(ip);

	//start thread to get the video from other peer
	_beginthread(&Peer::temp, 0, static_cast<void*>(this));

	vector < uchar > encoded;
	
	VideoCapture cap(0);
	while(!cap.isOpened()) cout << "Falha ao exibir a web cam";
	
	while (1) {
		
		Mat frame, send;
		
		cap >> frame;
		
		if (frame.empty()) continue;
		
		string servAddress = ip;

		int jpeg = ENCODE_QUALITY;
		
		resize(frame, send, Size(FRAME_WIDTH, FRAME_HEIGHT), 0, 0, INTER_LINEAR);
		
		vector <int> parametros_compress;
		parametros_compress.push_back(CV_IMWRITE_JPEG_QUALITY);
		parametros_compress.push_back(jpeg);

		imencode(".jpg", send, encoded, parametros_compress);
		
		int total_enviar = 1 + (encoded.size() - 1) / UDP_PACK_SIZE;
		int buffer_tamanho[1];
		buffer_tamanho[0] = total_enviar;
		
		sendto(socketUdp, (char*)buffer_tamanho, sizeof(int), 0, (sockaddr *)&Send_addr_video, sizeof(Send_addr_video));
		
		for (int i = 0; i < total_enviar; i++)
			sendto(socketUdp, (char*)&encoded[UDP_PACK_SIZE*i], UDP_PACK_SIZE, 0, (sockaddr *)&Send_addr_video, sizeof(Send_addr_video));
		
		waitKey(FRAME_INTERVAL);

	}

}