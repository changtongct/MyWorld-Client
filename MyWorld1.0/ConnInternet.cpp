#include "ConnInternet.h"

#include <iostream>
using namespace std;

ConnInternet::ConnInternet(void) {
	WORD sockVersion = MAKEWORD(2,2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data) != 0) {
		printf("invalid WSA !");
		return;
	}
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET) {
		printf("invalid socket !");
		return ;
	}
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(9999);
	serAddr.sin_addr.S_un.S_addr = inet_addr("123.207.84.70");
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		printf("connect error !\n");
		closesocket(sclient);
		return ;
	}
	char id_recData[64] = {0};
	recv(sclient, id_recData, 32, 0);
	if (id_recData[0] != 123) {
		printf("非法连接,正在关闭...111111111111");
		this->closeSocket();
	}
	swap(id_recData[4], id_recData[7]);
	swap(id_recData[5], id_recData[6]);
	m_id = *(int*)&id_recData[4];
	sendMsg(InternetPackage(CHECK_BYTE, 1, LOG_IN, 4, m_id, 0.0, -200.0, 10.0, 0.0, 201.0, 10.0));
	printf("id初始化成功: %d\n",m_id);
	logIn = true;
};

bool ConnInternet::logIn = false;

ConnInternet* ConnInternet::Instance() {
	static ConnInternet instance;

	while (logIn == false) {Sleep(1);}

	return &instance;
}

void ConnInternet::sendMsg(InternetPackage package) {
	char sendData[40] = {0};
	InternetPackage *b = &package;
	char* p = (char*)b;
			for (int i=0;i<32;++i) {
				sendData[i] = *p;
				++p;
			};
	send(sclient, sendData, 32, 0);
}

void ConnInternet::receiveMsg(void) {
	char recData[32];
	

	while(1) {
		memset(recData,0,32);
		int ret = recv(sclient, recData, 1024, 0);
		/*if(ret > 0) {
			recData[ret] = 0x00;
		}*/
		//printf("收到长度：%d\n",ret);
			
		//小端转大端，高字节放高地址
		for (int i=4;i<=28;i+=4) {
			swap(recData[i],recData[i+3]);
			swap(recData[i+1],recData[i+2]);
		}

		InternetPackage *msg = new InternetPackage();
		char *p = &recData[0];

			
		if (*p != 123) {
			printf("非法连接,正在关闭...");
			this->closeSocket();
			break;
		}
		msg->check = *p;
		++p;
		msg->ptype = *p;
		++p;
		msg->state = *p;
		++p;
		msg->reserve = *p;
		++p;
		msg->id = *(int*)p;
		p+=4;
		msg->X = *(float*)p;
		p+=4;
		msg->Y = *(float*)p;
		p+=4;
		msg->Z = *(float*)p;
		p+=4;
		msg->toX = *(float*)p;
		p+=4;
		msg->toY = *(float*)p;
		p+=4;
		msg->toZ = *(float*)p;

		printf("%x,%x,%x,%x,%d,%f,%f,%f,%f,%f,%f\n",msg->check, msg->ptype, msg->state, msg->reserve, msg->id, msg->X, msg->Y, msg->Z, msg->toX, msg->toY, msg->toZ);

		if (msg->ptype == 1) {
			switch (msg->state) {
				case LOG_IN : AllEntity.addEntity(msg->id, MY_PLAYER, Coordinate(msg->toX, msg->toY, msg->toZ), Coordinate(msg->X, msg->Y, msg->Z));
						printf("login\n");
					break;
				case LOG_ONLINE : AllEntity.changeCoorDirect(msg->id, Coordinate(msg->toX, msg->toY, msg->toZ), Coordinate(msg->X, msg->Y, msg->Z));
					break;
				case LOG_OFF : AllEntity.delEntity(msg->id);
					break;
			}
		}
		else if (msg->ptype == 2) {
			switch (msg->state) {
				case BULLET_NEW : AllEntity.addEntity(msg->id, MY_BULLET, Coordinate(msg->toX, msg->toY, msg->toZ), Coordinate(msg->X, msg->Y, msg->Z));
					break;
				/*case BULLET_MOVE : AllEntity.changeCoorDirect(msg->id, Coordinate(msg->toX, msg->toY, msg->toZ), Coordinate(msg->X, msg->Y, msg->Z));
					break;
				case BULLET_DEL : AllEntity.addEntity(msg->id, MY_PLAYER, Coordinate(msg->toX, msg->toY, msg->toZ), Coordinate(msg->X, msg->Y, msg->Z));
					break;*/
			}
		}
	}
}

void ConnInternet::closeSocket(void) {
	closesocket(sclient);
	WSACleanup();
	;
}

int ConnInternet::getID(void) {
	return m_id;
}