@file:Suppress("DEPRECATION")

package cn.staynoob.netdemo.echo.netty

import cn.staynoob.netdemo.echo.EchoServer
import io.netty.bootstrap.ServerBootstrap
import io.netty.channel.ChannelInitializer
import io.netty.channel.oio.OioEventLoopGroup
import io.netty.channel.socket.SocketChannel
import io.netty.channel.socket.oio.OioServerSocketChannel

class NettyOioServer : EchoServer {
    override fun start(port: Int) {
        val group = OioEventLoopGroup()

        try {
            val bootstrap = ServerBootstrap()
            bootstrap.group(group)
                    .channel(OioServerSocketChannel::class.java)
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
    val server = NettyOioServer()
    server.start(port)
}
