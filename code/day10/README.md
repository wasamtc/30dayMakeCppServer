# day10

每次写标题的时候总算不用凑格式加个0了

今天完成的东西很少但很重要，之前我们只有一个线程，接收分发事件是这个线程，处理事件还是这个线程，但是按道理处理事件需要用线程池中的线程，所以今天我们就设计了一个简单的线程池，最主要的就是一个线程的vector，然后初始化的时候用到了lambda，这一部分的内容可以看C++primer，线程是一创建就开始运行了，这里面我们还用了锁和条件变量，这一部分的内容可以看下现代C++和收藏的网页

[C++锁及条件变量的使用]: https://blog.csdn.net/c_base_jin/article/details/89741247

其实完成了初始化差不多就完成了今天的工作，其他地方要改的就是EventLoop里面加一个线程池的初始化和线程池事物的添加，然后Channel里面的handle就是直接把自己的处理函数通过event加到线程池里面即可，

现在的流程是，先初始化EventLoop，初始这个的时候会初始化Epoll和ThreadPoll，这时候线程池的线程应该都堵住了，然后初始化Server，初始的时候会初始Acceptor，这时候会创建服务器的socket以及channel，然后Epoll开始poll，接到新连接，channel把newconnection的函数放到线程池的事物中，创建一个connection类和相应的channel类，然后继续运行，接到其他请求也同理。