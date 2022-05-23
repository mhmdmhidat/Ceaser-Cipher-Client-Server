# Ceaser-Cipher-Client-Server
This is a pair of client and iterative server programs using UDP socket programming in C.
The client sends a null-terminated character message to the server, prints the returned 
response after being processed by the server, and waits for more user-input ( see below). The server 
encrypts the received message using ceaser cipher, sends the result to the client, and waits for more 
requests from the client side (see below)
Client-Side:
Once the client starts, it asks the user to enter a message. The message is one line which can contain small-letter characters or 0-9 digits. 
Spaces are allowed between words. After input checking, the client sends the request. When a reply is received, it is decrypted and converted to small-letter and printed on the standard output. 
Note that the connection between the client and server stays open, so that the client can repeat the operation again until the user ask for termination by entering the word “-1”. At this point, also the server terminates.
In order to make sure to don’t face a buffer limitation problem, the client code should get and report the sending and receiving buffer sizes for the UDP sockets (SO_SNDBUF and SO_RCVBUF). 
After printing the results on the screen, the program changes the send and receive buffer sizes to some value entered by the user and report the new values again into the screen. This step done at the beginning before start sending requests to the server.
The client uses command line arguments to read the IP and port number of the server, and leave for the kernel to assign its local socket address.
Server-side:
Once a message is received from the client, the server prints the received message, encrypts it using ceaser cipher, converts the encrypted message to capital letter, prints the new "capital-letter" message, then sends the new "capital-letter" message to the client. 
Note that a space in the input remains the same. Then, it waits for more request until it receives -1 , at which time it exits. 
Ceaser cipher: 
It is a type of substitution cipher in which each letter in the plaintext is replaced by a letter
after being shifted THREE positions down the alphabet. For example, “a” once encrypted would be 
replaced by “D”, “b” would become E, “1” would become “4”, “9” would become “<” and so on. 
The decryption process is reversed. Note that the clear text is in small letters and the encrypted text 
is in capital letters.
