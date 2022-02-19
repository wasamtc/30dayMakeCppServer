# day09

day09设计了一个缓冲类，然后用这个缓冲类来接收发送消息，这样确实更加抽象了，其他也没什么好说的。

vscode编译要在tasks.json里面设置，file是指当前文件，如server.cpp，workspaceFolder是指整个项目的文件夹，总之要成功调试的话需要在task里面的-g加上你的其他cpp文件。
