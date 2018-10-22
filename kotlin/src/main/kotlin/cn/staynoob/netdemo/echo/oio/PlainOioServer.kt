package cn.staynoob.netdemo.echo.oio

import cn.staynoob.netdemo.echo.EchoServer
import java.io.OutputStreamWriter
import java.io.PrintWriter
import java.net.ServerSocket
import java.net.Socket

class PlainOioServer : EchoServer {

    class EchoHandler(
            private val connectionSocket: Socket
    ) : Runnable {
        override fun run() {
            val inStream = connectionSocket.getInputStream()
            val outStream = connectionSocket.getOutputStream()

            connectionSocket.use {
                inStream.bufferedReader().use { reader ->
                    PrintWriter(OutputStreamWriter(outStream, Charsets.UTF_8.name()), true).use { writer ->
                        while (true) {
                            val msg = reader.readLine() ?: break
                            println("String received: $msg")
                            writer.println(msg)
                        }
                    }
                }
                println("about to disconnect")
            }
        }
    }


    override fun start(port: Int) {
        ServerSocket(port).use { serverSocket ->
            while (true) {
                val connectionSocket = serverSocket.accept()
                println("Connection is established")
                val echoRunnable = EchoHandler(connectionSocket)
                val thread = Thread(echoRunnable)
                thread.start()
            }
        }

    }
}

fun main(args: Array<String>) {
    PlainOioServer().start(22000)
}