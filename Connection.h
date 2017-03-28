#ifndef Con
#define Con

class Connection
{
public:
	Connection();
	Connection(char*,char*,char*,char*,char*,char*);
	void showInfo(bool,bool,bool);
	char* getSockfd();
	void setPid(char*);
	void setPname(char*);
private:
	char* proto;
	char* local_addr;
	//char* local_port;
	long int local_port;

	char* dst_addr;
	char* dst_port;
	char* sockfd;
	char* pid;
	char* pro_name;

};
#endif
