#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include "Connection.h"

using namespace std;
int MAXLINE = 1000;
char *protocal[4]={"tcp","tcp6","udp","udp6"};
void finding_match(Connection*,char*,char*);
void showConnInfo(Connection*,int);
int conncount=0;//connection entry count
int Matchcnt=0;
int main(int argc, char* argv[])
{
	//Connection Conn[1000];
	Connection *Conn;
	Conn = new Connection[MAXLINE];
	for (int i=0;i<MAXLINE;i++)
	{
		Conn[i] = Connection();
	}
	FILE *fp[4];//tcp_fp, tcp6_fp, udp_fp, udp6_fp;
	fp[0] = fopen("/proc/net/tcp","r");
	fp[1] = fopen("/proc/net/tcp6","r");
	fp[2] = fopen("/proc/net/udp","r");
	fp[3] = fopen("/proc/net/udp6","r");
	char line[MAXLINE];

	for(int i=0;i<4;i++)
	{
		fgets(line,MAXLINE,fp[i]);
		while(fgets(line,MAXLINE,fp[i]))
		{
			cout << "readline:" << line << endl;
			char* noneed;
			char *proto=new char[4];
			char *local_addr= new char[30];
		    char *local_port=new char[20];
    		char *dst_addr=new char[30];
    		char *dst_port=new char[20];
			char *sockfd=new char[10];


			proto=protocal[i];
			noneed=strtok(line," ");
			local_addr=strtok(NULL," :");
			local_port=strtok(NULL," :");
			
			dst_addr=strtok(NULL," :");
			dst_port=strtok(NULL," :");
			for(int t=0;t<6;t++)
				noneed=strtok(NULL," ");
			sockfd=strtok(NULL," ");
			cout<<"mychk "
				<<proto<<" "
				<<local_addr<<" "
				<<local_port<<" "
				<<dst_addr<<" "
				<<dst_port<<" "
				<<sockfd
				<<endl;
			Conn[conncount]=Connection(proto,local_addr,local_port,dst_addr,dst_port,sockfd);
			cout<<"after construct"<<endl;
			conncount++;
		
		}
		fclose(fp[i]);
	}

	showConnInfo(Conn,conncount);

	//finding pid
	DIR* procdir;
	procdir=opendir("/proc");
	struct dirent* procdirent;
	//char fd_path[256];
	//strcpy(fd_path,"/proc");
	int sockcnt=0;
	while(procdirent=readdir(procdir))
	{
		if(isdigit(procdirent->d_name[0]))
		{
			cout<<"proc's dirent: "<<procdirent->d_ino<<" "<<procdirent->d_off<<" "<<procdirent->d_name<<endl;

			char fd_path[256];
			strcpy(fd_path,"/proc/");
			strcat(fd_path,procdirent->d_name);
			strcat(fd_path,"/fd");
			cout<<"path "<<fd_path<<endl;

			DIR* fd_dir;
			fd_dir=opendir(fd_path);
			struct dirent* fd_dirent;
			if(!(fd_dir=opendir(fd_path)))
				cout<<"error!"<<endl;
			fd_dirent=readdir(fd_dir);
			fd_dirent=readdir(fd_dir);
			while(fd_dirent=readdir(fd_dir))
			{
				char file_path[256];
				struct stat sb;
				strcpy(file_path,fd_path);
				strcat(file_path,"/");
				strcat(file_path,fd_dirent->d_name);
			    if (stat(file_path, &sb) == -1) {
			        perror("stat");
        			exit(EXIT_FAILURE);
			    }
				if ((sb.st_mode & S_IFMT)==S_IFSOCK) {
					char *linkname;
					ssize_t r;

					 if (lstat(file_path, &sb) == -1) {
						perror("lstat");
						exit(EXIT_FAILURE);
					}

				   linkname = (char*)malloc(sb.st_size + 1);
					if (linkname == NULL) {
						fprintf(stderr, "insufficient memory\n");
						exit(EXIT_FAILURE);
					}

				   r = readlink(file_path, linkname, sb.st_size + 1);

				   if (r < 0) {
						perror("lstat");
						exit(EXIT_FAILURE);
					}

				   if (r > sb.st_size) {
						fprintf(stderr, "symlink increased in size "
										"between lstat() and readlink()\n");
						exit(EXIT_FAILURE);
					}

				   linkname[sb.st_size] = '\0';

				   printf("'%s' points to '%s'\n", file_path, linkname);
					char* sockfd = strtok(linkname,"socket:[]");
					cout<<"extract "<<sockfd<<endl;

					finding_match(Conn,sockfd,procdirent->d_name);
					cout<<"IS socket"<<endl;
					showConnInfo(Conn,conncount);
					sockcnt++;
					
				}

			}
		}
	}
	cout<<"sock count"<<sockcnt<<endl;
	cout<<"mc"<<Matchcnt<<endl;
	showConnInfo(Conn,conncount);
}
void finding_match(Connection *Conn, char* sfd, char* pid)
{
	for(int i=0;i<conncount;i++)
	{
		if(!strcmp(Conn[i].getSockfd(),sfd))
		{
			cout<<"t0"<<endl;
			Conn[i].setPid(pid);
			cout<<"t1"<<endl;
			FILE *fp;
			char fname[256];
			strcpy(fname,"/proc/");
			strcat(fname,pid);
			strcat(fname,"/cmdline");
			//strcat(fname,"/comm");

			FILE *cmdline = fopen(fname, "rb");
			char *arg = 0;
			size_t size = 0;
			while(getdelim(&arg, &size, 0, cmdline) != -1)
			{
				puts(arg);
			  	Conn[i].setPname(arg);
			  	Conn[i].setPname(" ");
				if(arg[0]=='/')
					break;
			
			}
			free(arg);
			fclose(cmdline);


			cout<<"MATCH, pid="<<pid//<<"pname="<<Conn[i].pro_name
			<<endl;
			Matchcnt++;
			break;
		}
	}
}
void showConnInfo(Connection *Conn, int cnt)
{
	for(int i=0;i<cnt;i++)
	{
		Conn[i].showInfo();
	}
}











