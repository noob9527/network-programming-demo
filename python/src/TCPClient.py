import socket as s

serverName = 'localhost'
serverPort = 12000


def main():
    clientSocket = s.socket(s.AF_INET, s.SOCK_STREAM)
    clientSocket.connect((serverName, serverPort))
    message = input('Input sentence: ')
    clientSocket.send(message.encode())
    received_message = clientSocket.recv(2048)
    print(received_message.decode())
    clientSocket.close()


if __name__ == '__main__':
    main()
