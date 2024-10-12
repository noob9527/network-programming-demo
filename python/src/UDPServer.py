import socket as s

serverPort = 12000


# 
# Computer Networking, A Top-Down Approach
# With port numbers assigned to UDP sockets, we can now precisely describe 
# UDP multiplexing/demultiplexing. Suppose a process in Host A, with UDP port 
# 19157, wants to send a chunk of application data to a process with UDP port 46428 in 
# Host B. The transport layer in Host A creates a transport-layer segment that includes 
# the application data, the source port number (19157), the destination port number 
# (46428), and two other values (which will be discussed later, but are unimportant for 
# the current discussion). The transport layer then passes the resulting segment to the 
# network layer. The network layer encapsulates the segment in an IP datagram and 
# makes a best-effort attempt to deliver the segment to the receiving host. If the segment arrives at the receiving Host B, the transport layer at the receiving host examines the destination port number in the segment (46428) and delivers the segment 
# to its socket identified by port 46428. Note that Host B could be running multiple 
# processes, each with its own UDP socket and associated port number. As UDP segments arrive from the network, Host B directs (demultiplexes) each segment to the 
# appropriate socket by examining the segment’s destination port number.
# It is important to note that a UDP socket is fully identified by a two-tuple consisting of a destination IP address and a destination port number. As a consequence, if 
# two UDP segments have different source IP addresses and/or source port numbers, but 
# have the same destination IP address and destination port number, then the two segments will be directed to the same destination process via the same destination socket.
def main():
    serverSocket = s.socket(s.AF_INET, s.SOCK_DGRAM)
    serverSocket.bind(('', serverPort))
    print('server is ready')
    while True:
        # You may be wondering now, what is the purpose of the source port number? 
        # As shown in Figure 3.4, in the A-to-B segment the source port number serves as 
        # part of a “return address”—when B wants to send a segment back to A, the destination port in the B-to-A segment will take its value from the source port value of the 
        # A-to-B segment. (The complete return address is A’s IP address and the source port 
        # number.) As an example, recall the UDP server program studied in Section 2.7. In 
        # UDPServer.py, the server uses the recvfrom() method to extract the clientside (source) port number from the segment it receives from the client; it then sends 
        # a new segment to the client, with the extracted source port number serving as the 
        # destination port number in this new segment.
        message, clientAddress = serverSocket.recvfrom(2048)
        print(f'receive message = {message.decode()}')
        outputMessage = message.decode().upper()
        serverSocket.sendto(outputMessage.encode(), clientAddress)


if __name__ == '__main__':
    main()
