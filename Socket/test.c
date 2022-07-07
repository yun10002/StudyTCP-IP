/*
*Created : 2022-07-07
*Author : 최윤진
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

char webpage[]="HTTP/1.1 200 OK\r\n"
					"Server:Linux Web Server\r\n"
					"Content-Type:text/html; charset=UTF-8\r\n\r\n"
					"<!DOCTYPE html>\r\n"
					"<html><head><title> My Web Page </title>\r\n"
					"<style>body {background-color:#1E90FF}</style></head>\r\n"
					"<body><center><h1>Hello summer!</h1><br>\r\n"
					"<img src=\"wallpaper.png\"></center></body></html>\r\n";

void error_handling(char *message);

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_addr_size;
	char buf[2048];
	char img_buf[7000000];
	int n, fd;
	char *img;

	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//1) 소켓생성
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr)); //소켓 초기화
	serv_adr.sin_family=AF_INET;				 //소켓 설정
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	//2) bind함수로 소켓에 주소정보 전달
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	//3) listen함수로 소켓이 연결요청이 가능한 상태가 되도록 함
	if(listen(serv_sock, 20)==-1)
		error_handling("listen() error");

	while(1){
		clnt_addr_size=sizeof(clnt_adr);
		//4) accept함수로 데이터 송수신 연결요청 수락
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_addr_size);
	 	if(clnt_sock==-1) 
	 		error_handling("accept() error");
		printf("new client connection...\n");
		
		n=read(clnt_sock, buf, sizeof(buf));
		printf("%s", buf);
		if(n<0) printf("read() error");

		img=strstr(buf, "/");
		img=strtok(img, " ");

		if(strcmp(img, "/wallpaper.png")==0){ //이미지파일 추출
			fd=open("wallpaper.png", O_RDONLY);
			read(fd, img_buf, sizeof(img_buf));
			write(clnt_sock, img_buf, sizeof(img_buf));
			break;
		}
		else
			write(clnt_sock, webpage, sizeof(webpage));
	}
	
	close(clnt_sock); close(serv_sock); //생성한 소켓 닫아주기

	
	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
