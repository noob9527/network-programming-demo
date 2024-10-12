import socket as s

serverName = 'localhost'
serverPort = 12000


def main():
    # When a UDP socket is created in this manner, the transport layer automatically 
    # assigns a port number to the socket. In particular, the transport layer assigns a port 
    # number in the range 1024 to 65535 that is currently not being used by any other UDP 
    # port in the host.
    clientSocket = s.socket(s.AF_INET, s.SOCK_DGRAM)
    # Alternatively, we can add a line into our Python program after we 
    # create the socket to associate a specific port number (say, 19157) to this UDP socket 
    # via the socket bind() method:
    # clientSocket.bind((’’, 19157))
    message = input('Input sentence: ')
    clientSocket.sendto(message.encode(), (serverName, serverPort))
    received_message, severAddress = clientSocket.recvfrom(2048)
    print(received_message.decode())
    clientSocket.close()


if __name__ == '__main__':
    main()
