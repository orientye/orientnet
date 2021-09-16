
# 设计目标
- 高性能
- 简洁易用
- 易扩展
- 跨平台
- 基于C++11

# 并发模型
- 支持：1到N个io thread, 0-M个worker thread
    - 0个worker thread退化为one loop per thread
- 支持协程: N:1或者N:M
- 支持同步, 异步, '半同步半异步'

# 网络协议
- 同一个端口支持多种协议
- 支持tcp, http(s)
- 支持protobuf
- 可自行定义协议
