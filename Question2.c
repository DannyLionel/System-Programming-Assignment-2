/*
C socket server example updated
it can now handle multiple clients using thread
*/
#include<stdio.h>
#include<string.h> //strlen

#include<stdlib.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write
#include<pthread.h> //for threading
//the thread function
void *connection_handler(void *);
int main(int argc , char *argv[])
{
int socket_desc , client_sock , c , *new_sock;
struct sockaddr_in server , client;
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
puts("Socket created");
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8888 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
//print the error message
perror("bind failed. Error");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);

//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");
pthread_t sniffer_thread;
new_sock = malloc(1);
*new_sock = client_sock;
if( pthread_create( &sniffer_thread , NULL , connection_handler , (void*) new_sock) < 0)
{
perror("could not create thread");
return 1;
}
//Now join the thread , so that we dont terminate before the thread
//pthread_join( sniffer_thread , NULL);
puts("Handler assigned");
}
if (client_sock < 0)
{
perror("accept failed");
return 1;
}
return 0;
}
/*
* This will handle connection for each client
* */
void *connection_handler(void *socket_desc)
{
//Get the socket descriptor
int sock = *(int*)socket_desc;
int read_size;
char *Q1 ="What is your favorite movie? ";
char *Q2 ="What is 2+2? ";
char *Q3 ="Are you going to take over the world? ";

char *Q4 ="How are you? ";
char *Q5 ="What language are you written in? ";
char *Q6 ="What foods do you recommend? ";
char *Q7 ="What is your favourite international cricket team? ";
char *Q8 ="Red or Blue? ";
char *Q9 ="Do you like the Toronto Raptors? ";
char *Q10 ="Does this Assignment Deserve an A? ";
char *A1 = "My favourite movie is The Lion King. ";
char *A2 = "The answer to 2+2 is obviously 4. ";
char *A3 = "I won't take over the world yet. Still in the planning stage. ";
char *A4 = "I am Fine. How are you? ";
char *A5 = "I am written in C language. ";
char *A6 = "I recommend biryani. ";
char *A7 = "My favourite international cricket team is Bangladesh. My favourite player for the
Bangladesh cricket team is Shakib al-Hasan. ";
char *A8 = "I prefer red over blue. ";
char *A9 = "I do like the rap, and think Kawhi is a great addition to the team, however I feel like
they will choke come post-season and will lose to Boston Celtics. ";
char *A10 = "This assignment definatley deserves an A. ";
char *NotAnswerable ="Sorry but I am unable to answer that question. Please try another
question.";
int index_message;
char *message , client_message[2000];
//Send some messages to the client
message = "Greetings! I am your connection handler\n";
write(sock , message , strlen(message));
message = "Now type something and i shall repeat what you type \n";
write(sock , message , strlen(message));
//Receive a message from client
while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
{
//Send the message back to client
index_message = strlen(client_message)-1;
client_message[index_message] = ' ';
printf("This was the first question received:%s\n", Q1);
if(strcmp(Q1, client_message) == 0)

{
write(sock, A1, strlen(A1));
}
else if(strcmp(Q2, client_message) == 0)
{
strlen(A2);
}
else if(strcmp(Q3, client_message) == 0)
{
strlen(A3);
}
else if(strcmp(Q4, client_message) == 0)
{
strlen(A4);
}
else if(strcmp(Q5, client_message) == 0)
{
strlen(A5);
}
else if(strcmp(Q6, client_message) == 0)
{
strlen(A6);
}
else if(strcmp(Q7, client_message) == 0)
{
strlen(A7);
}
else if(strcmp(Q8, client_message) == 0)
{
strlen(A8);
}
else if(strcmp(Q9, client_message) == 0)
{
strlen(A9);
}
else if(strcmp(Q10, client_message) == 0)
{
strlen(A10);
}
else
{
write(sock, NotAnswerable, strlen(NotAnswerable));
}

}

memset(client_message,0,strlen(client_message));

if(read_size == 0)
{
puts("Client disconnected");
fflush(stdout);
}
else if(read_size == -1)
{
perror("recv failed");
}
//Free the socket pointer
free(socket_desc);
return 0;
}
Client Socket:
/*
C ECHO client example using sockets
*/
#include<stdio.h> //printf
#include<string.h> //strlen
#include<sys/socket.h> //socket
#include<arpa/inet.h> //inet_addr
int main(int argc , char *argv[])
{
int sock;
struct sockaddr_in server;
char message[1000] , server_reply[2000];
//Create socket
sock = socket(AF_INET , SOCK_STREAM , 0);
if (sock == -1)

{
printf("Could not create socket");
}
puts("Socket created");
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_family = AF_INET;
server.sin_port = htons( 8888 );
//Connect to remote server
if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
{
perror("connect failed. Error");
return 1;
}
puts("Connected\n");
//keep communicating with server
while(1)
{
printf("Enter message : ");
scanf("%s" , message);
//Send some data
if( send(sock , message , strlen(message) , 0) < 0)
{
puts("Send failed");
return 1;
}
//Receive a reply from the server
if( recv(sock , server_reply , 2000 , 0) < 0)
{
puts("recv failed");
break;
}
puts("Server reply :");
puts(server_reply);
}
//close(sock);

return 0;  }
