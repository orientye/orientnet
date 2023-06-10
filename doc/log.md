# 设计目标
- level: 支持
- logger: 支持
- layout与appender
    - 以sink的方式提供
    - 目的地:
        - [1] console
        - [2] (local)file
        - [3] network
        - [4] db
        - 基于性能与简洁性, orientnet仅支持[1]和[2]
    - 滚动方式:
        - 按时间大小滚动
        - 按大小滚动

- thread-safe: 支持
- crash-safe: 暂不支持
    - 关键日志额外立即存储?
- 同步与异步
    - 支持同步
    - 支持异步

- 主要思想
    - 一个进程里, 多个生产者(即多个线程), 一个消费者(log线程)
    - 多缓冲
    - 有序
