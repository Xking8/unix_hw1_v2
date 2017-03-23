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

	//start parsing /proc/net/xxx
	//int conncount=0;//connection entry count
	char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
/*	
	Conn[0].sockfd = "1111";
	Conn[1].sockfd = "2222";
	showConnInfo(Conn,2);
	exit(1);
*/
#ifdef debug
	for(int i=0;i<1;i++)
	{
		fgets(line,MAXLINE,fp[i]);
		while(fgets(line,MAXLINE,fp[i]))
		{
			cout << "readline:" << line << endl;
			//char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
			proto=new char[4];
			local_addr= new char[30];
		    local_port=new char[20];
    		dst_addr=new char[30];
    		dst_port=new char[20];
			sockfd=new char[10];
	/*		
			char* noneed;
			char *proto=new char[4];
			char *local_addr= new char[30];
		    char *local_port=new char[20];
    		char *dst_addr=new char[30];
    		char *dst_port=new char[20];
			char *sockfd=new char[10];
			char* noneed;*/


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
/*			cout<<"address chk "
				<<&proto<<" "
				<<&local_addr<<" "
				<<&local_port<<" "
				<<&dst_addr<<" "
				<<&dst_port<<" "
				<<&sockfd
				<<endl;
			*/
			Conn[conncount]=Connection(proto,local_addr,local_port,dst_addr,dst_port,sockfd);
			cout<<"after construct"<<endl;
			conncount++;
		
		/*	for(int i=0;i<conncount;i++)
			{
				cout<<Conn[i].proto<<"\t"
				<<Conn[i].local_addr<<":"<<Conn[i].local_port<<"\t"
				<<Conn[i].dst_addr<<":"<<Conn[i].dst_port<<"\t"
				<<Conn[i].sockfd
				<<endl;


			}*/
		}
		fclose(fp[i]);
	}

	showConnInfo(Conn,conncount);
	exit(1);
#endif
	for(int i=0;i<4;i++)
	{
		fgets(line,MAXLINE,fp[i]);
		while(fgets(line,MAXLINE,fp[i]))
		{
			cout << "readline:" << line << endl;
			//char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
			/*proto=new char[4];
			local_addr= new char[30];
		    local_port=new char[20];
    		dst_addr=new char[30];
    		dst_port=new char[20];
			sockfd=new char[10];
			*/
			char* noneed;
		/*	char *proto=new char[4];
			char *local_addr= new char[30];
		    char *local_port=new char[20];
    		char *dst_addr=new char[30];
    		char *dst_port=new char[20];
			char *sockfd=new char[10];
			char* noneed;*/


			Conn[conncount].proto=protocal[i];
			noneed=strtok(line," ");
			strcpy(Conn[conncount].local_addr,strtok(NULL," :"));
			strcpy(Conn[conncount].local_port,strtok(NULL," :"));
			
			strcpy(Conn[conncount].dst_addr,strtok(NULL," :"));
			strcpy(Conn[conncount].dst_port,strtok(NULL," :"));
			for(int t=0;t<6;t++)
				noneed=strtok(NULL," ");
			//Conn[conncount].sockfd=strtok(NULL," ");
			strcpy(Conn[conncount].sockfd,strtok(NULL," "));
			cout<<"mychk "
				<<Conn[conncount].proto<<" "
				//<<local_addr<<" "
				//<<local_port<<" "
				//<<dst_addr<<" "
				//<<dst_port<<" "
				<<Conn[conncount].sockfd
				<<endl;
/*			cout<<"address chk "
				<<&proto<<" "
				<<&local_addr<<" "
				<<&local_port<<" "
				<<&dst_addr<<" "
				<<&dst_port<<" "
				<<&sockfd
				<<endl;
			*/
		//	Conn[conncount]=Connection(proto,local_addr,local_port,dst_addr,dst_port,sockfd);
			cout<<"after construct"<<endl;
			conncount++;
		


		}

		fclose(fp[i]);
	}
	//showConnInfo(Conn,conncount);
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
			//strcat(fd_path,procdirent->d_name);
			//strcat(fd_path,"/fd");
			//cout<<"path "<<fd_path<<endl;
//			DIR* mydir;
//			mydir=opendir("/proc/1447/fd");

			char fd_path[256];
			strcpy(fd_path,"/proc/");
			strcat(fd_path,procdirent->d_name);
			strcat(fd_path,"/fd");
			cout<<"path "<<fd_path<<endl;

			DIR* fd_dir;
			fd_dir=opendir(fd_path);
			//fd_dir=opendir("/proc/1/fd");
			struct dirent* fd_dirent;
			//fd_dir=opendir("/proc/1/fd");
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
				//cout<<"the fd "<<fd_dirent->d_name<<"\tfilepath: "<<file_path<<endl;
			//	stat(file_path,&sb);
			    if (stat(file_path, &sb) == -1) {
			        perror("stat");
        			exit(EXIT_FAILURE);
			    }
			   /* if (stat("/proc/3099/fd/3", &sb) == -1) {
			        perror("stat");
        			exit(EXIT_FAILURE);
			    }*/
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
			//showConnInfo(Conn,conncount);
		}
		//showConnInfo(Conn,conncount);
	}
	cout<<"sock count"<<sockcnt<<endl;
	cout<<"mc"<<Matchcnt<<endl;
	showConnInfo(Conn,conncount);
/*	DIR* mydir;
	mydir=opendir("/proc/2354/fd");
	struct dirent *mydirent;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<" reclen="<<mydirent->d_reclen<<endl;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	mydirent=readdir(mydir);
	if(mydirent)
		//cout<<"not empty"<<endl;
		cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
		mydirent=readdir(mydir);
		if(mydirent)
		//cout<<"not empty"<<endl;
		cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	//cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
*/
}
void finding_match(Connection *Conn, char* sfd, char* pid)
{
	for(int i=0;i<conncount;i++)
	{
		if(!strcmp(Conn[i].sockfd,sfd))
		{
			strcpy(Conn[i].pid,pid);
			FILE *fp;
			char fname[256];
			strcpy(fname,"/proc/");
			strcat(fname,pid);
			strcat(fname,"/cmdline");
			//strcat(fname,"/comm");
			//strcpy(fname,"./hello");

			FILE *cmdline = fopen(fname, "rb");
			char *arg = 0;
			size_t size = 0;
			while(getdelim(&arg, &size, 0, cmdline) != -1)
			{
				puts(arg);
			  	strcat(Conn[i].pro_name,arg);
			  	strcat(Conn[i].pro_name," ");
			
			}
			free(arg);
			fclose(cmdline);


/*			const int BUFSIZE = 4096; // should really get PAGESIZE or something instead...
			unsigned char buffer[BUFSIZE]=""; // dynamic allocation rather than stack/global would be better

			int fd = open(fname, O_RDONLY);
			int nbytesread = read(fd, buffer, BUFSIZE);
			cout<<"BUFFER: "<<buffer<<endl;
			unsigned char *end = buffer + nbytesread;
			for (unsigned char *p = buffer; p < end; )
			{ cout << p << endl;
			  strcat(Conn[i].pro_name,(char*)p);
			  strcat(Conn[i].pro_name," ");
			  while (*p++); // skip until start of next 0-terminated section
			}
			close(fd);
*/
/*			const int BUFSIZE = 300; // should really get PAGESIZE or something instead...
			//char buffer[BUFSIZE]=""; // dynamic allocation rather than stack/global would be better
			char* buffer = new char[BUFSIZE];
			int fd = open(fname, O_RDONLY);
			int nbytesread = read(fd, buffer, BUFSIZE);
			cout<<"nbytesread: "<<nbytesread <<endl;
			char *end = buffer + nbytesread;
			for (char *p = buffer; p < end;)
			{
			  //while (*p++); // skip until start of next 0-terminated section
			  cout <<"p: "<< p <<" length: "<<strlen(p)<< endl;
			  //bcopy(p,Conn[i].pro_name,strlen(p));
			  strcat(Conn[i].pro_name,p);
			  strcat(Conn[i].pro_name," ");
			  showConnInfo(Conn,conncount);
			  while (*p++ && p<end)
			  {
				cout<<"IN WHILE: p="<<p<<endl; // skip until start of next 0-terminated section
			  }
			}
			close(fd);				
*/

/*			const int BUFSIZE = 300; // should really get PAGESIZE or something instead...
			//char buffer[BUFSIZE]=""; // dynamic allocation rather than stack/global would be better
			char* buffer = new char[BUFSIZE];
			int fd = open(fname, O_RDONLY);
			char* t;
			t=  new char[1];
			int n;
			//int nbytesread = read(fd, buffer, 1);
			//cout<<"nbytesread: "<<nbytesread <<endl;
			//char *end = buffer + nbytesread;
			for (;read(fd,t,1)>=0;)
			{
			  //char* t;
			  //t=  new char[1];
			  //int n=read(fd,t,1);
			  //while (*p++); // skip until start of next 0-terminated section
			  cout <<"ttt: "<< t <<" length: "<<strlen(t)<< endl;
			  //bcopy(p,Conn[i].pro_name,strlen(p));
			  strcat(Conn[i].pro_name,t);
			  strcat(Conn[i].pro_name," ");
			  //showConnInfo(Conn,conncount);
			  while (*buffer++ && buffer<end)
			  {
				cout<<"IN WHILE: buf="<<buffer<<endl; // skip until start of next 0-terminated section
			  }
			}
			close(fd);				
*/

/*			while(fread(line,3000,1,fp))	
			{
				cout<<"LINE"<<line<<endl;
				strcat(Conn[i].pro_name,line);
				strcat(Conn[i].pro_name," ");
			}
*/
/*
			fp=fopen(fname,"r");
			char line[100]="";
			while(fgets(line,20,fp))
			{
				cout<<"LINE2"<<endl;
				strcat(Conn[i].pro_name,line);
			}
*/		
			cout<<"MATCH, pid="<<pid<<"pname="<<Conn[i].pro_name<<endl;
			Matchcnt++;
			break;
		}
	}
}
void showConnInfo(Connection *Conn, int cnt)
{
	cout<<"List of connections:\nProto Local Address\tForeign Address\tPID/Program name and arguments"<<endl;
	for(int i=0;i<cnt;i++)
	{
		cout<<Conn[i].proto<<"\t\nLOCAL ADDR:"
		<<Conn[i].local_addr<<":"<<Conn[i].local_port<<"\t\nDST ADDR: "
		<<Conn[i].dst_addr<<":"<<Conn[i].dst_port<<"\t\nPID/NAME: "
		//<<Conn[i].sockfd
		<<Conn[i].pid<<"/"<<Conn[i].pro_name
		<<"\n-----------------------------------"
		<<endl;


	}
}











