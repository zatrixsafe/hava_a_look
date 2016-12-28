
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
