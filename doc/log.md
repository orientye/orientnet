# 设计目标
- level: 支持
- logger: 支持
- layout与appender

    以sink的方式提供

    目的地:  
        [1] console  
        [2] (local)file  
        [3] socket/http  
        [4] db  
        基于性能与简洁性, orientnet仅支持[1]和[2], 是否支持[3]与[4]由应用层决定  

    滚动方式:  
        [1]按时间大小滚动  
        [2]按大小滚动  

- thread-safe: 支持
- crash-safe: 暂不支持