# day11

今天的这个内容很复杂啊，主要是用了很多不知道的知识，尤其是很多现代C++的知识。

这里面有：

[类模板及可变参数模板](https://www.cnblogs.com/qicosmos/p/4325949.html)

[从4行代码看右值引用](https://www.cnblogs.com/qicosmos/p/4283455.html)

[C++11 并发指南四( 详解二 std::packaged_task 介绍)](https://www.cnblogs.com/haippy/p/3279565.html)

[std::result_of编译时获取函数返回类型](https://blog.csdn.net/wangzhicheng1983/article/details/117350183)

[C++typename的由来和用法](https://blog.csdn.net/lyn631579741/article/details/110730145)

[C++ using用法总结](https://www.cnblogs.com/wangkeqin/p/9339862.html)

[C++11中的std::bind](https://blog.csdn.net/u013654125/article/details/100140328)

[具体代码讲解：用C++封装线程池](https://blog.csdn.net/GavinGreenson/article/details/72770818)

然后还有一个地方折腾了很久，就是请求建立新连接的不多，所以acceptor可以直接用主线程（阻塞式socket）处理，所以channel的事物那里就要区分啊，所以就多了一个useET函数，useET就是把模式换成ET嘛，所以就要更新啊，我之前没注意，我是useET后在enableReading，结果enableReading就把之前的ET给覆盖了，所以就一直出问题。

我觉得今天这个测试文件还是有点东西，至少解决了我一个长久关于linux命令的问题，具体的解释见：

[Linux下getopt()函数的简单使用](https://www.cnblogs.com/qingergege/p/5914218.html)

[c++中的atoi()和stoi()函数的用法和区别](https://blog.csdn.net/qq_33221533/article/details/82119031)

[linux——getopt()和getopt_long()函数及optarg,optind, opterr, optopt全局变量](https://blog.csdn.net/u014470361/article/details/84110216)



