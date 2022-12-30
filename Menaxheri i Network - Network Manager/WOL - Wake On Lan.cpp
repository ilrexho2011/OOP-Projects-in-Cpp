// Program per ndezjen e nje kompjuteri ne rrjet ose 
// internet duke perdorur protokollin Wake-on-LAN. 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <socket.h> 
#include <netinet.h> 
#include <inet.h> 
#include <string.h> 
#include <sys/types.h> 
using namespace std;  
int main() 
{ 
    int i; 
    unsigned char toSend[102],mac[6]; 
    struct sockaddr_in udpClient, udpServer; 
    int broadcast = 1 ; 
  
    // Krijimi i UDP Socket 
    int udpSocket = socket(AF_INET, SOCK_DGRAM, 0); 
  
    // Manipulimi i UDP Socket 
    if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, 
                  &broadcast, sizeof broadcast) == -1) 
    { 
        perror("setsockopt (SO_BROADCAST)"); 
        exit(EXIT_FAILURE); 
    } 
    udpClient.sin_family = AF_INET; 
    udpClient.sin_addr.s_addr = INADDR_ANY; 
    udpClient.sin_port = 0; 
  
    //Perkufizimi i socket 
    bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient)); 
  
    for (i=0; i<6; i++) 
        toSend[i] = 0xFF; 
  
    // Le te marrim MAC Address sikur eshte ab:cd:ef:gh:ij:kl  78:ac:c0:ac:23:b8
    mac[0] = 0x78;  // okteti i pare i MAC Address 
    mac[1] = 0xac;  // okteti i dyte i MAC Address 
    mac[2] = 0xc0;  // okteti i trete i MAC Address 
    mac[3] = 0xac;  // okteti i katert i MAC Address 
    mac[4] = 0x23;  // okteti i peste i MAC Address 
    mac[5] = 0xb8;  // okteti i gjashte i MAC Address 
  
    for (i=1; i<=16; i++) 
        memcpy(&toSend[i*6], &mac, 6*sizeof(unsigned char)); 
  
    udpServer.sin_family = AF_INET; 
  
    // Transmetimi i IP address 
    udpServer.sin_addr.s_addr = inet_addr("192.168.1.103"); 
    udpServer.sin_port = htons(9); 
  
    sendto(udpSocket, &toSend, sizeof(unsigned char) * 102, 0, 
             (struct sockaddr*)&udpServer, sizeof(udpServer)); 
    return 0; 
}
