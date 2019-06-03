#include "yfc.h"

void main()
{
        struct sockaddr_in s_address;
	int sock,len;
	char buf[80];

        sock=socket(AF_INET,SOCK_DGRAM,0);
	if(sock==-1)
	{
		printf("\n create socket faiult! \n");
		exit(-1);
	}

        len=sizeof(s_address);
        s_address.sin_family=AF_INET;
        s_address.sin_port=htons(9000);
        s_address.sin_addr.s_addr=inet_addr("127.0.0.1");

	sendto(sock,"client success.",sizeof(buf),0,(struct sockaddr*)&s_address,sizeof(s_address));

	len=sizeof(s_address);
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&s_address,&len);

	printf("\n read:%s \n",buf);

//	关闭套接字
	close(sock);
}
