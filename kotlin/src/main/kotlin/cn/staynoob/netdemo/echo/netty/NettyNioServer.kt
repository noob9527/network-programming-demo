@file:Suppress("DEPRECATION")

package cn.staynoob.netdemo.echo.netty

import cn.staynoob.netdemo.echo.EchoServer
import io.netty.bootstrap.ServerBootstrap
import io.netty.channel.ChannelInitializer
import io.netty.channel.nio.NioEventLoopGroup
import io.netty.channel.socket.SocketChannel
import io.netty.channel.socket.nio.NioServerSocketChannel

class NettyNioServer : EchoServer {
    override fun start(port: Int) {
        val group = NioEventLoopGroup()

        try {
            val bootstrap = ServerBootstrap()
            bootstrap.group(group)
                    .channel(NioServerSocketChannel::class.java)
                    .localAddress(port)
                    .childHandler(object : ChannelInitializer<SocketChannel>() {
                        override fun initChannel(ch: SocketChannel) {
                            ch.pipeline().addLast(EchoServerHandler())
                        }
                    })

            val channelFuture = bootstrap.bind().sync()
            channelFuture.channel().closeFuture().sync()
        } finally {
            group.shutdownGracefully().sync()
        }
    }
}

fun main(vararg argv: String) {
    val port = 22000
    val server = NettyNioServer()
    server.start(port)
}
