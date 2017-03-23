#ifndef Con
#define Con

class Connection
{
public:
	Connection();
	Connection(char*,char*,char*,char*,char*,char*);
	char* proto;
	char* local_addr;
	char* local_port;
	char* dst_addr;
	char* dst_port;
	char* sockfd;
	char* pid;
	char* pro_name;

};
#endif
