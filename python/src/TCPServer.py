import socket as s

serverPort = 12000


def main():
    serverSocket = s.socket(s.AF_INET, s.SOCK_STREAM)
    serverSocket.bind(('', serverPort))
    serverSocket.listen(1)
    print('server is ready')
    while True:
        connectionSocket, add = serverSocket.accept()
        message = connectionSocket.recv(2048)
        print(f'receive message = {message.decode()}')
        outputMessage = message.decode().upper()
        connectionSocket.send(outputMessage.encode())
        connectionSocket.close()


if __name__ == '__main__':
    main()
