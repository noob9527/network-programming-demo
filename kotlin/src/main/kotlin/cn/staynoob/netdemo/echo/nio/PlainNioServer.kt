package cn.staynoob.netdemo.echo.nio

import cn.staynoob.netdemo.echo.EchoServer
import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.SelectionKey
import java.nio.channels.Selector
import java.nio.channels.ServerSocketChannel
import java.nio.channels.SocketChannel

class PlainNioServer : EchoServer {
    override fun start(port: Int) {
        val selector = Selector.open()

        val serverSocketChannel = ServerSocketChannel.open()
        serverSocketChannel.configureBlocking(false)
        serverSocketChannel.bind(InetSocketAddress(port))

        serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT)

        val buffer = ByteBuffer.allocate(256);
        while (true) {
            selector.select()
            val iterator = selector.selectedKeys().iterator()
            while (iterator.hasNext()) {
                val key = iterator.next()
                // remove the key, otherwise we will get the key again and again
                // by selector.selectedKeys() even if it's not ready to use.
                // https://stackoverflow.com/questions/7132057/why-the-key-should-be-removed-in-selector-selectedkeys-iterator-in-java-ni
                iterator.remove()

                if (key.isAcceptable) {
                    val clientChannel = serverSocketChannel.accept()
                    clientChannel.configureBlocking(false)
                    clientChannel.register(selector, SelectionKey.OP_READ)
                    println("Connection is established")
                    println(clientChannel)
                }

                if (key.isReadable) {
                    val clientChannel = key.channel() as SocketChannel
                    val readCount = clientChannel.read(buffer)
                    if (readCount == -1) {
                        clientChannel.close()
                        key.cancel()
                        continue
                    }
                    buffer.flip()
                    clientChannel.write(buffer)


                    buffer.rewind()
                    val msg = Charsets.UTF_8.decode(buffer).toString()
                    println("String received: $msg")

                    buffer.clear()
                }
            }
        }
    }
}

fun main(args: Array<String>) {
    PlainNioServer().start(22000)
}
