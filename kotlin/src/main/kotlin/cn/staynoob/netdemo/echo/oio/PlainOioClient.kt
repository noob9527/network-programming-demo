package cn.staynoob.netdemo.echo.oio

import java.io.OutputStreamWriter
import java.io.PrintWriter
import java.net.InetSocketAddress
import java.net.Socket

class PlainOioClient {
    fun start(host: String, port: Int) {

        Socket().use { socket ->
            val address = InetSocketAddress(host, port)
            socket.connect(address)

            val inStream = socket.getInputStream()
            val outStream = socket.getOutputStream()

            System.`in`.bufferedReader().use { reader ->
                PrintWriter(OutputStreamWriter(outStream), true).use { writer ->
                    inStream.bufferedReader().use {
                        while (true) {
                            val msg = reader.readLine() ?: break
                            writer.println(msg)
                            println(it.readLine())
                        }
                    }
                }
            }
        }

    }
}

fun main(args: Array<String>) {
    val host = "127.0.0.1"
    val port = 22000
    PlainOioClient().start(host, port)
}