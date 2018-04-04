#include<stdio.h>
#include<ws2tcpip.h> //multicast
#include <winsock2.h>  
#pragma comment(lib,"ws2_32.lib")  

#define g_multi_ip "225.0.0.1"
#define g_port 8888
int main(int argc, char*argv[])
{
	WSADATA wsa;

	int ierr = WSAStartup(MAKEWORD(1, 1), &wsa);
	if (ierr != 0)
	{
		printf("WSAStartup faile\n");
	}

	SOCKET m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == m_socket)
	{
		printf("socket faile\n");
	}
	
	int ioptv = 0;
	if (SOCKET_ERROR == setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&ioptv, sizeof(ioptv)))
	{
		printf("setsockopt faile\n");
	}

	sockaddr_in m_addr;
	
	ZeroMemory(&m_addr, sizeof(m_addr));

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.S_un.S_addr = inet_addr(g_multi_ip);
	m_addr.sin_port = htons(g_port);

	char buf[MAX_PATH] = {"1234"};
	int isend = 0;

	while (true)
	{
		isend = sendto(m_socket, buf, MAX_PATH, 0, (const sockaddr*)&m_addr, sizeof(m_addr));
		if (isend != MAX_PATH)
		{
			printf("sendto faile\n");
		}
	}
	return true;
}