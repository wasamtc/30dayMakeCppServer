# day06

day06就具体用到了Reactor模式和之前提到的Channel的回调函数，现在整体就主要分为Reactor和处理资源池，其中Eventloop扮演的就是Reactor，Server扮演的就是处理资源池，因为还没有设计acceptor，所以接收也作为一种handler放在Server中，Channel中要新增一个回调函数私有成员来对handler进行绑定。到此基本的Reactor模式就算完成了，即Eventloop接收事件返回Channel，Channel根据自己绑定的handler（即回调函数）进行处理，并且send给客户端信息，Server负责提供各种handler。

所以在一开始Server初始化要把服务器的Channel绑定到newConnection这个handler上。就是要读serv_sock做一系列的初始化。

还有一件事，因为epoll是整个模式的核心，所以要保护在loop中，所有要用ep的只有通过调用loop来用了。

[C++11 中的std::function和std::bind]: https://www.jianshu.com/p/f191e88dcc80
[回调函数（callback）是什么]: https://www.zhihu.com/question/19801131
[std::function介绍]: https://www.cnblogs.com/yinwei-space/p/12708871.html
