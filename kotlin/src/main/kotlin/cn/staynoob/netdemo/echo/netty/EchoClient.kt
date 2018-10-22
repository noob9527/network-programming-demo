package cn.staynoob.netdemo.echo.netty

import io.netty.bootstrap.Bootstrap
import io.netty.channel.ChannelInitializer
import io.netty.channel.nio.NioEventLoopGroup
import io.netty.channel.socket.SocketChannel
import io.netty.channel.socket.nio.NioSocketChannel
import java.net.InetSocketAddress

class EchoClient {
    fun start(host: String, port: Int) {

        val group = NioEventLoopGroup()

        try {
            val bootstrap = Bootstrap()
            bootstrap.group(group)
                    .channel(NioSocketChannel::class.java)
                    .remoteAddress(InetSocketAddress(host, port))
                    .handler(object: ChannelInitializer<SocketChannel>() {
                        override fun initChannel(ch: SocketChannel) {
                            ch.pipeline().addLast(EchoClientHandler())
                        }
                    })

            val channelFuture = bootstrap.connect().sync()
            channelFuture.channel().closeFuture().sync()
        } finally {
            group.shutdownGracefully().sync()
        }
    }
}

fun main(vararg argv: String) {
    val host = "127.0.0.1"
    val port = 22000
    EchoClient().start(host, port)
}