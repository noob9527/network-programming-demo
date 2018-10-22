import socket as s

serverName = 'localhost'
serverPort = 12000


def main():
    clientSocket = s.socket(s.AF_INET, s.SOCK_DGRAM)
    message = input('Input sentence: ')
    clientSocket.sendto(message.encode(), (serverName, serverPort))
    received_message, severAddress = clientSocket.recvfrom(2048)
    print(received_message.decode())
    clientSocket.close()


if __name__ == '__main__':
    main()
