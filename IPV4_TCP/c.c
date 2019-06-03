#include "yfc.h"

void main()
{
        struct sockaddr_in s_address;
	int sock,len;
	char buf[80];

        sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		printf("\n create socket faiult! \n");
		exit(-1);
	}

        len=sizeof(s_address);
        s_address.sin_family=AF_INET;
        s_address.sin_port=htons(9000);
        s_address.sin_addr.s_addr=inet_addr("2.0.0.6");

//	客户端通过该函数向服务器端的监听套接字发送连接请求。
        if(connect(sock,(struct sockaddr*)&s_address,len)==-1)//请求服务端连接
	{
		printf("\n connect server computer faiult!  \n");
		exit(-1);
	}

	printf("\n buf: ");
	scanf("%s",buf);
	write(sock,buf,80);

//	读取套接字中传入的内容.
	if(read(sock,buf,80)==-1)
	{
		printf("\n read faiult! \n");
		exit(-1);
	}
	printf("\n read:%s \n",buf);

//	关闭套接字
	close(sock);
}
