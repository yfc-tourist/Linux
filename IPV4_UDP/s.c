#include "yfc.h"

void main()
{
	int sock,len;
        struct sockaddr_in s_un,c_un;
	char buf[80];

//	socket()用于创建一个套接字，同时指定协议和类型.
//	协议:AF_INET(IPv4协议网络通信)、AF_INET6(IPv6协议)、AF_KEY(密钥套接字)
//	类型:SOCK_STREAM套接字((面向连接)TCP通信、SOCK_DGRAM((无连接)UDP通信)
        if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		printf("\n create socket failur! \n");
		exit(-1);
	}

//	(sockaddr、sockaddr_un)结构体是用来表示本地地址信息。
//	通常用sockaddr_in来保存本地ip地址,
//	在使用时转成sockaddr类型的指针。
        s_un.sin_family=AF_INET;
        //设置端口号
        //字节序:有两种->1.高位字节存储在低位地址。2.高位字节存储在高位地址。
        //在网络通信中，通信双方有可能使用不同的字节序。
        //统一规定：数据以高位字节优先顺序在网络上传输。
        //字节序自动转换函数:【htons(端口号)、htonl(ip地址)】<-主机
        //字节序自动转换函数:【ntons(端口号)、ntonl(ip地址)】<-外来
        s_un.sin_port=htons(9000);
        //设置IP地址
        //ip地址有两种格式:十进制点分形式和【32位二进制形式(网络传输中IP地址的存储方式)】
        //inet_addr()将十进制ip地址字符串转为32位二进制Ip地址（网络字节序）
        s_un.sin_addr.s_addr=inet_addr("127.0.0.1");
	len=sizeof(s_un);

//	bind()函数将保存在相应地址结构中的地址信息与套接字进行绑定
	if(bind(sock,(struct sockaddr*)&s_un,len)==-1)//命名socket
	{
		printf("\n bind failut!  \n");
		exit(-1);
	}

	len=sizeof(s_un);
	//
	recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&s_un,&len);
	printf(": %s \n",buf);	
	
	sendto(sock,"service success.",sizeof(buf),0,(struct sockaddr*)&s_un,sizeof(s_un));

//	关闭套接字
	close(sock);
}
