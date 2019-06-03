#include "yfc.h"

void main()
{
	int sock,csock,len;
	struct sockaddr_un s_un,c_un;
	char buf[80];

//	socket()用于创建一个套接字，同时指定协议和类型.
//	协议:建立的socket仅限同一台设备上的进程间通信用AF_UNIX或AF_LOCAL(本地套接字)
//	类型:SOCK_STREAM流式套接字((面向连接)TCP通信、SOCK_DGRAM((无连接)UDP通信)
	if((sock=socket(AF_UNIX,SOCK_STREAM,0))==-1)
	{
		printf("\n create socket failur! \n");
		exit(-1);
	}

//	(sockaddr、sockaddr_un)结构体是用来表示本地地址信息。
//	通常用sockaddr_un来保存某个本地地址,
//	在使用时转成sockaddr类型的指针。
	s_un.sun_family=AF_UNIX;
	strcpy(s_un.sun_path,fifo);
	len=sizeof(s_un);
	unlink(fifo);//清空文件内容

//	bind()函数将保存在相应地址结构中的地址信息与套接字进行绑定
	if(bind(sock,(struct sockaddr*)&s_un,len)==-1)//命名socket
	{
		printf("\n bind failut!  \n");
		exit(-1);
	}

//	将套接字设置为监听模式，准备接收客户端的连接请求.
	listen(sock,2);//服务端许接入数

	len=sizeof(c_un);

//	等待并接收客户端的连接请求，建立好TCP连接后，返回一个新的已连接套接字.
	if((csock=accept(sock,(struct sockaddr*)&c_un,&len))==-1)//接受客户端的连接
	{
		printf("\n server computer accept failut! \n");
		exit(-1);
	}

//	对已连接套接字进行读操作.
	if(read(csock,buf,80)==-1)
	{
		printf("\n read faiult! \n");
		exit(-1);
	}
	printf("\n read: %s \n",buf);

//	对已连接套接字进行写操作.
	printf("\nwrite: ");
	scanf("%s",buf);
	if(write(csock,buf,80)==-1)
	{
		printf("\n write faiult! \n");
		exit(-1);
	}

//	关闭套接字
	close(csock);
	close(sock);
}
