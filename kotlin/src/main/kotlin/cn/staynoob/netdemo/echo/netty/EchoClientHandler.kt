package cn.staynoob.netdemo.echo.netty

import io.netty.buffer.ByteBuf
import io.netty.channel.ChannelHandler
import io.netty.channel.ChannelHandlerContext
import io.netty.channel.SimpleChannelInboundHandler
import io.netty.util.CharsetUtil

@ChannelHandler.Sharable
class EchoClientHandler : SimpleChannelInboundHandler<ByteBuf>() {


    override fun channelRead0(ctx: ChannelHandlerContext, msg: ByteBuf) {
        print("client received: ${msg.toString(CharsetUtil.UTF_8)}")
    }

    override fun channelActive(ctx: ChannelHandlerContext) {
        val thread = Thread {
            System.`in`.bufferedReader().use { reader ->
                while (true) {
                    val msg = reader.readLine()
                    val buffer = ctx.alloc().buffer()
                    buffer.writeBytes("$msg\n".toByteArray(Charsets.UTF_8))
                    ctx.writeAndFlush(buffer)
                }
            }
        }
        thread.start()
    }

    @Suppress("OverridingDeprecatedMember")
    override fun exceptionCaught(ctx: ChannelHandlerContext, cause: Throwable) {
        cause.printStackTrace()
        ctx.close()
    }

}