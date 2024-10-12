import socket as s

serverPort = 12000


# One subtle difference between a 
# TCP socket and a UDP socket is that a TCP socket is identified by a four-tuple: 
# (source IP address, source port number, destination IP address, destination port 
# number).
# Thus, when a TCP segment arrives from the network to a host, the host 
# uses all four values to direct (demultiplex) the segment to the appropriate socket.
# In particular, and in contrast with UDP, two arriving TCP segments with different source IP addresses or source port numbers will (with the exception of a TCP 
# segment carrying the original connection-establishment request) be directed to two 
# different sockets.
#
# -- Computer Networking, A Top-Down Approach
#
def main():
    # The TCP server application has a “welcoming socket,” that waits for connection 
    # establishment requests from TCP clients on port number 12000.
    serverSocket = s.socket(s.AF_INET, s.SOCK_STREAM)
    serverSocket.bind(('', serverPort))
    serverSocket.listen(1)
    print('server is ready')
    while True:
        # When the host operating system of the computer running the server process 
        # receives the incoming connection-request segment with destination port 12000, 
        # it locates the server process that is waiting to accept a connection on port number 
        # 12000. The server process then creates a new socket:
        connectionSocket, address = serverSocket.accept()
        # Also, the transport layer at the server notes the following four values in the connection-request segment: (1) the source port number in the segment, (2) the IP 
        # address of the source host, (3) the destination port number in the segment, and 
        # (4) its own IP address. The newly created connection socket is identified by these 
        # four values; all subsequently arriving segments whose source port, source IP 
        # address, destination port, and destination IP address match these four values will 
        # be demultiplexed to this socket. With the TCP connection now in place, the client 
        # and server can now send data to each other.

        # The server host may support many simultaneous TCP connection sockets, with 
        # each socket attached to a process, and with each socket identified by its own four-tuple. When a TCP segment arrives at the host, all four fields (source IP address, 
        # source port, destination IP address, destination port) are used to direct (demultiplex) 
        # the segment to the appropriate socket.

        message = connectionSocket.recv(2048)
        print(f'receive message = {message.decode()}')
        outputMessage = message.decode().upper()
        connectionSocket.send(outputMessage.encode())
        connectionSocket.close()


if __name__ == '__main__':
    main()
