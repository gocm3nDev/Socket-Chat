# Socket Programming Project

## Overview

This project demonstrates a simple client-server application using socket programming in C. The server listens for connections and exchanges messages with the client over TCP.

### Key features include:

- Customizable server IP address and port.
- Real-time message exchange.
- Graceful handling of connection errors.
  
### Requirements
- GCC Compiler (or any C compiler).
- Linux/Unix-based environment recommended for networking features.
- Basic understanding of socket programming.
  
### Installation

Clone the repository:

```c
git clone https://github.com/gocm3nDev/Socket-Chat.git
```

Navigate to the project directory:

```c
cd socket-programming
```

Compile the client and server programs:

Server
```c
gcc -o server server.c
```

Client
```c
gcc -o client client.c
```

### Usage

Start the server:

```c
./server
```

The server listens on the specified port (default: 4006).

Run the client:
```c
./client
```
When prompted, enter the server's IP address.

Exchange messages between the client and server. Type exit to close the connection.

### Code Structure

server.c: Contains the server-side implementation, including socket creation, binding, and message handling.

client.c: Contains the client-side implementation, including connection to the server and message handling.

### Customization
Update SERVER_PORT in the source files to change the default port.

Modify message buffer sizes by changing the SERVER_TLENGTH definition.

### Contributing
Feel free to fork this repository and contribute enhancements or fixes. Pull requests are welcome!
