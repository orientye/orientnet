
# 设计目标
- 高性能
- 简洁易用
- 易扩展
- 跨平台
- 基于C++11

# 并发模型
- 线程
    - 1个或更多个io thread, 0个或更多个worker thread
    - 0个worker thread退化为one loop per thread
- 协程
    - 支持N:1
    - 支持N:M

# 网络协议
- 同一个端口支持多种协议
- 支持tcp, http(s)
- 支持protobuf
- 可自行定义协议
- 支持同步, 异步, '半同步'(join), 取消等操作
