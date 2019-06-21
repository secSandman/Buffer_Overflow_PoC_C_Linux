 /*
 * A vulnerable network application C to show the basics over-flowing a buffer and writing a simple Socket Program .. (-8
 * Thanks to taishi8117 for the source code and tutorial on the public internet 
 * Thanks to Rensellar College and UPENN for leaving your C / C# programming material for free on the public internet
 */
 
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <unistd.h>
#include    <signal.h>


/*defines a macro named BUFFER_SIZE as an abbreviation for the token 1024. If somewhere after this #define directive there comes a C statement of the form*/
#define BUFFER_SIZE 1024
#define HEADER_SIZE 4

/* Macro will insert buffer size of 1024 into char buffer setting our buffer size to 1024 bytes*/

void vuln_read(int cli_fd) {

  /*The server reads characters from the socket connection into this buffer.*/

  char buffer[BUFFER_SIZE];


  /* Assuming that incoming header is in little endianread then read 4 bytes to get how many bytes to read */

  int to_read;
  read(cli_fd, &to_read, HEADER_SIZE);
  printf("Will read %d bytes\n", to_read);

  
  /* ----------------- WARNING ------------------------*/
  /*int read_bytes = read(cli_fd, buffer, to_read); has a buffer overflow vulnerability, 
  because to_read can be much larger than the macro defined 1024. 
  That's because there is no byte length validation on to_read before we place into buffer of 1024, meh */
  
  int read_bytes = read(cli_fd, buffer, to_read);
  printf("Read: %d bytes\n", read_bytes);
  printf("Incoming message: %s\n", buffer);
}

int main (int argc, char **argv){


  // struct sockaddr_storage serverStorage;
  // int welcomeSocket, newSocket;


  if (argc < 2) {
    printf("Usage: %s [port]\n", argv[0]);
    exit(1);
  }

  /*
  sockfd is a file descriptors, i.e. array subscripts into the file descriptor table . These two variables store the values returned by the socket system call and the accept system call.
  port stores the port number on which the server accepts connections.
  cli_len stores the size of the address of the client. This is needed for the accept system call.
  */

  int port, sock_fd, cli_fd;
  socklen_t cli_len;

  /*A sockaddr_in is a structure containing an internet address. This structure is defined in <netinet/in.h>. */
  struct sockaddr_in serv_addr, cli_addr;

/*The socket() system call creates a new socket. It takes three arguments. The first is the address domain of the socket. Recall that there are two possible address domains, the unix domain for two processes which share a common file system, and the Internet domain for any two hosts on the Internet. The symbol constant AF_UNIX is used for the former, and AF_INET for the latter (there are actually many other options which can be used here for specialized purposes).
The second argument is the type of socket. Recall that there are two choices here, a stream socket in which characters are read in a continuous stream as if from a file or pipe, and a datagram socket, in which messages are read in chunks. The two symbolic constants are SOCK_STREAM and SOCK_DGRAM. The third argument is the protocol. If this argument is zero (and it always should be except for unusual circumstances), the operating system will choose the most appropriate protocol. It will choose TCP for stream sockets and UDP for datagram sockets.

The socket system call returns an entry into the file descriptor table (i.e. a small integer). This value is used for all subsequent references to this socket. If the socket call fails, it returns -1. In this case the program displays and error message and exits. However, this system call is unlikely to fail.

This is a simplified description of the socket call; there are numerous other choices for domains and types, but these are the most common. */


  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    printf("Error opening a socket\n");
    exit(1);
  }

  /*An in_addr structure, defined in the same header file, contains only one field, a unsigned long called s_addr. The variable serv_addr will contain the address of the server,
  and cli_addr will contain the address of the client which connects to the server.

  The port number on which the server will listen for connections is passed in as an argument,
  and this statement uses the atoi() function to convert this from a string of digits to an integer. */

  port = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(port);

  /*The bind() system call binds a socket to an address, in this case the address of the current host and port number on which the server will run. It takes three arguments, the socket file descriptor, the address to which is bound, and the size of the address to which it is bound. The second argument is a pointer to a structure of type sockaddr, but what is passed in is a structure of type sockaddr_in, and so this must be cast to the correct type. This can fail for a number of reasons, the most obvious being that this socket is already in use on this machine.*/

  if (bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    printf("Error on bind()\n");
    exit(1);
  }

  /* The listen system call allows the process to listen on the socket for connections. The first argument is the socket file descriptor, and the second is the size of the backlog queue, i.e., the number of connections that can be waiting while the process is handling a particular connection. This should be set to 5, the maximum size permitted by most systems.
  If the first argument is a valid socket, this call cannot fail, and so the code doesn't check for errors. */
  
  // printf("Waiting for a connection...\n");
  listen(sock_fd, 1);

  while(1)

  { //infinite loop


  /*The accept() system call causes the process to block until a client connects to the server. Thus, it wakes up the process when a connection from a client has been successfully established. It returns a new file descriptor, and all communication on this connection should be done using the new file descriptor. The second argument is a reference pointer to the address of the client
  on the other end of the connection, and the third argument is the size of this structure. */

  cli_len = sizeof(cli_addr);
  cli_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &cli_len);
  if (cli_fd < 0) {
    printf("Error on accept()\n");
    exit(1);
  }
  // printf("Connection accepted...\n");
  

  vuln_read(cli_fd);

  char message[] = "Hello there, try to Pwn me ... if you're a 1773 H4x0r, lolz!\n";
  write(cli_fd, message, strlen(message));
  close(cli_fd);
  sleep(1);
  }
  return 0;
}

