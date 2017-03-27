#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Connection.h"

using namespace std;

Connection::Connection()
{
	proto=new char[100];
	local_addr=new char[100];
	//local_port=new char[100];
	dst_addr=new char[100];
	dst_port=new char[100];
	sockfd=new char[100];
	pid=new char[100];
	pro_name=new char[100];
	//pid="";
	//pro_name="";
}
Connection::Connection(char* p, char* la, char* lp,  char* da, char* dp, char* s)
{
	int size=3000;
	proto=new char[size];
	local_addr=new char[size];
	//local_port=new char[size];
	dst_addr=new char[128];
	dst_port=new char[size];
	sockfd=new char[size];
	pid=new char[size];
	pro_name=new char[size];
	cout<<"p length"<<strlen(p)<<endl;
	cout<<"la length"<<strlen(la)<<endl;
	/*proto=p;
	local_addr=la;
	local_port=lp;
	dst_addr=da;
	dst_port=dp;
	sockfd=s;*/
	//pid="";
	//pro_name="";
	strcpy(proto,p);
	strcpy(local_addr,la);
	//strcpy(local_port,lp);
	strcpy(dst_addr,da);
	strcpy(dst_port,dp);
	strcpy(sockfd,s);
//	char* tmpend;
	cout<<"lp length:"<<strlen(lp)<<endl;
	strcpy(la,"017AA8C0");
	local_port=strtol(lp,NULL,16);
	if(!strcmp(proto,"tcp") || !strcmp(proto,"udp") )//ipv4
	{
		cout<<"in converting"<<endl;
		struct in_addr local_inaddr;
		local_inaddr.s_addr=(int)strtoll(la,NULL,16);
		inet_ntop(AF_INET,&local_inaddr,local_addr,60);
		cout<<"in converting"<<endl;

		struct in_addr dst_inaddr;
		dst_inaddr.s_addr=(int)strtoll(da,NULL,16);
		inet_ntop(AF_INET,&dst_inaddr,dst_addr,60);
	}
	else
	{
		struct in6_addr local_inaddr;
		if (sscanf(la,
		    "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
		    &local_inaddr.s6_addr[3], &local_inaddr.s6_addr[2], &local_inaddr.s6_addr[1], &local_inaddr.s6_addr[0],
		    &local_inaddr.s6_addr[7], &local_inaddr.s6_addr[6], &local_inaddr.s6_addr[5], &local_inaddr.s6_addr[4],
		    &local_inaddr.s6_addr[11], &local_inaddr.s6_addr[10], &local_inaddr.s6_addr[9], &local_inaddr.s6_addr[8],
		    &local_inaddr.s6_addr[15], &local_inaddr.s6_addr[14], &local_inaddr.s6_addr[13], &local_inaddr.s6_addr[12]) == 16)
		{
		    inet_ntop(AF_INET6, &local_inaddr, local_addr, sizeof local_addr);
		    printf("ip=%s \n",local_addr);
		}
		
		struct in6_addr dst_inaddr;
		//strcpy(da,"BACD0120000000000000000052965732");
	    char ip_str[128];
		//cout<<"da address:"<<da<<endl;
/*		char* pEnd;
		dst_inaddr.s6_addr[3]=strtoll(da,&pEnd,16);
		printf("printf:%d\n",dst_inaddr.s6_addr[3]);
		cout<<"s6addr3= "<<dst_inaddr.s6_addr[3]<<endl;
*/
		if (sscanf(da,
		    "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
		    &dst_inaddr.s6_addr[3], &dst_inaddr.s6_addr[2], &dst_inaddr.s6_addr[1], &dst_inaddr.s6_addr[0],
		    &dst_inaddr.s6_addr[7], &dst_inaddr.s6_addr[6], &dst_inaddr.s6_addr[5], &dst_inaddr.s6_addr[4],
		    &dst_inaddr.s6_addr[11], &dst_inaddr.s6_addr[10], &dst_inaddr.s6_addr[9], &dst_inaddr.s6_addr[8],
		    &dst_inaddr.s6_addr[15], &dst_inaddr.s6_addr[14], &dst_inaddr.s6_addr[13], &dst_inaddr.s6_addr[12]) == 16)
		{
		    //inet_ntop(AF_INET6, &dst_inaddr, dst_addr, sizeof dst_addr);
		    inet_ntop(AF_INET6, &dst_inaddr, ip_str, sizeof ip_str);
			printf("s6addr:%d %d %d\n",dst_inaddr.s6_addr[3],dst_inaddr.s6_addr[2],dst_inaddr.s6_addr[1]);
		    printf("ip=%s \n",ip_str);
			strcpy(dst_addr,ip_str);
		}

	}
}
char* Connection::getSockfd()
{
	return sockfd;
}
void Connection::setPid(char* p)
{
	strcpy(pid,p);
}
void Connection::setPname(char* pn)
{
	strcat(pro_name,pn);
}
void Connection::showInfo()
{
	cout<<proto<<"\t\nLOCAL ADDR: "
    <<local_addr<<":"<<local_port<<"\t\nDST ADDR: "
    <<dst_addr<<":"<<dst_port<<"\t\nPID/NAME: "
    //<<Conn[i].sockfd
    <<pid<<"/ "<<pro_name
    <<"\n-----------------------------------"
    <<endl;
}
