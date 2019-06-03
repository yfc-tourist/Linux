#include "yfc.h"

void main()
{
	struct sockaddr_un address;
	int sock,len;
	char buf[80];

	sock=socket(AF_UNIX,SOCK_STREAM,0);
	if(sock==-1)
	{
		printf("\n create socket faiult! \n");
		exit(-1);
	}

	len=sizeof(address);
	address.sun_family=AF_UNIX;
	strcpy(address.sun_path,fifo);

//	客户端通过该函数向服务器端的监听套接字发送连接请求。
	if(connect(sock,(struct sockaddr*)&address,len)==-1)//请求服务端连接
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
