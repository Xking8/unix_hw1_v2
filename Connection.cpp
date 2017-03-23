#include <iostream>
#include <string.h>
#include "Connection.h"

using namespace std;

Connection::Connection()
{
	proto=new char[100];
	local_addr=new char[100];
	local_port=new char[100];
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
	local_port=new char[size];
	dst_addr=new char[size];
	dst_port=new char[size];
	sockfd=new char[size];
	pid=new char[size];
	pro_name=new char[size];
	/*proto=p;
	local_addr=la;
	local_port=lp;
	dst_addr=da;
	dst_port=dp;
	sockfd=s;
	pid="";
	pro_name="";*/
	/*strcpy(proto,p);
	strcpy(local_addr,la);
	strcpy(local_port,lp);
	strcpy(dst_addr,da);
	strcpy(dst_port,dp);
	strcpy(sockfd,s);*/
}
