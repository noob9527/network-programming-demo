import socket as s

serverPort = 12000


def main():
    serverSocket = s.socket(s.AF_INET, s.SOCK_DGRAM)
    serverSocket.bind(('', serverPort))
    print('server is ready')
    while True:
        message, clientAddress = serverSocket.recvfrom(2048)
        print(f'receive message = {message.decode()}')
        outputMessage = message.decode().upper()
        serverSocket.sendto(outputMessage.encode(), clientAddress)


if __name__ == '__main__':
    main()
