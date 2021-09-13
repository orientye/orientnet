
# 设计目标
- 高性能
- 简洁易用
- 易扩展
- 跨平台
- 基于C++11

# 并发模型
- 支持：1到N个io thread, 0-M个worker thread
- 支持协程: N:1或者N:M(work stealing模式)
- 支持同步和异步方式

# 网络协议
- 同一个端口支持多种协议
- 支持tcp, http(s)
- 支持protobuf
- 可自行定义协议
