# day07

在前一天的基础上我们又设计出了acceptor，主要是为了让server类更加抽象，因为server类是不应该有初始化服务器的socket这种操作的，还有reactor模式本身应该有一个acceptor，所以我们就单独设计一个acceptor，每个服务器的端口都有一个acceptor（我们这里只有一个服务器的端口），这个acceptor主要负责建立新的连接，不过这个功能也是通过回调server里的函数实现，acceptor本身也有一个channel来添加到epoll中，所以每次建立连接要经过两次回调。

至此，初始化时server会创建一个服务端的acceptor，acceptor创建时自动初始化吧，绑定，监听，挂载，同时初始acceptor对应channel的回调函数，server随后初始acceptor的回调函数，初始化完成。

之后有新的连接时，channel回调acceptor，acceptor回调server的函数创建一个新的连接，如果有可读事件，则channel回调server的函数即可。

从上面我们也可以看出来有可读事件channel直接去回调函数是很具体的操作，所以明天我们要做的就是把TCP连接抽象为类，通过这个连接类去调用函数。
