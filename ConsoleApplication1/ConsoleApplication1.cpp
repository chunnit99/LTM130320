#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32")
using namespace std;
//hàm kiểm tra kí tự a
bool isCharacter(char a) {
	if (a == '.' || (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '-')
		return true;
	else return false;
}
//hàm kiểm tra chuỗi hợp lệ
bool isIP(char* s) {
	for (int i = 0; i < sizeof(s); i++)
	{
		if (!isCharacter(s[i])) return false;
	}
	return true;
}
int main()
{
	//khởi tạo winsock
	WSAData wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (res == 0) {
		addrinfo* info;
		SOCKADDR_IN addr;
		//lấy chuỗi kí tự từ bàn phím
		char s[256];
		cin.getline(s, 256);
		//kiểm tra chuỗi ký tự
		if (!isIP(s)) {
			printf("Ten mien chua ky tu khong hop le");
			return true;
		}
		//phân giải địa chỉ
		int ret = getaddrinfo(s, "http", NULL, &info);
		int err = WSAGetLastError();
		//Ghi địa chỉ IP đã phân giải ra màn hình
		if (ret == 0) {
			//duyệt từng địa chỉ IP
			while (info != NULL) {
				memcpy(&addr, info->ai_addr, info->ai_addrlen);
				printf("Dia chi ip: %s", inet_ntoa(addr.sin_addr));
				info = info->ai_next;
			}
		}
		else {
			printf("Khong phan giai duoc dia chi! ");
		}
	}

}