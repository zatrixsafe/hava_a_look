# iow_clksender
## 说明
1.bin目录下是控制iow_clksender开始和停止的运行脚本
可运行bash iow_clksender.sh start 启动程序
运行bash iow_clksender.sh stop 停止程序
2.config目录下是clicksender模块的配置文件
3.lib存放的是项目文件
4.iow_clksender目录下为项目的主要程序脚本

添加新的广告主时:
1.在MIS的创意层添加对广告主的AppId的sendUrl进行配置
3.在添加sendUrl时，应按照appId=<APPID>的格式添加参数


日志文件位于logs目录下的clicksender.log文件中
日志配置项在logger.conf文件中

## 请求时序图

```sequence

Title:test
participant ClickSenderManager
participant SenderThread
participant FillThread
participant Queue
participant MySql
participant MonitorThread
Note over ClickSenderManager: 主线程
ClickSenderManager->Queue:实例一个全局Queue
Note over Queue: 用于共享待发送激活数据
ClickSenderManager->SenderThread:启动多个worker线程
ClickSenderManager->FillThread:启动单个fill线程
ClickSenderManager->MonitorThread:启动单个监控线程
FillThread->MySql:请求mysql数据(fill_clk_queue)
MySql-->>FillThread:返回待发送激活数
Note over FillThread: 处理SQL中数据(process_clks)
FillThread->Queue:待发送激活数据放入Queue中
SenderThread->Queue:取出待发送激活数据
Queue-->>SenderThread:待发送激活数据
SenderThread->广告主:激活数据发送至广告主(send)
广告主-->>SenderThread:response
Note over SenderThread:核对广告主response
SenderThread->MySql:更改clk id 状态
MonitorThread->MySql:检查当天内未处理的clk数量

```

