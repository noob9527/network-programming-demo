import socket as s

serverName = 'localhost'
serverPort = 12000


def main():
    # The TCP client creates a socket and sends a connection establishment request 
    # segment with the lines:
    clientSocket = s.socket(s.AF_INET, s.SOCK_STREAM)
    clientSocket.connect((serverName, serverPort))
    # A connection-establishment request is nothing more than a TCP segment with 
    # destination port number 12000 and a special connection-establishment bit set in 
    # the TCP header (discussed in Section 3.5). The segment also includes a source 
    # port number that was chosen by the client.


    message = input('Input sentence: ')
    clientSocket.send(message.encode())
    received_message = clientSocket.recv(2048)
    print(received_message.decode())
    clientSocket.close()


if __name__ == '__main__':
    main()
