# 单词消除游戏（GuessWordGame）
> c++课程设计大作业

采用Qt5编译。

## 程序简介
- GuessWordGame
客户端程序，在第一次启动后通过config.xml配置网络参数。  
其他还有一些功能如出做题、出题、排行榜、在线对战。  
如果想要切换到本地版本，在datastructure.h中有宏定义可以切换。  
- TcpServer
服务器程序，可设置端口号。  
配有日志系统。  
- WordExtracter
提取单词程序（基本上用不到）
