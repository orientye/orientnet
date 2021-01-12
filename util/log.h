#ifdef _LOG_H_

class Log {
    enum class LogLevel {
        kTrace = 0,
        kDebug,
        kInfo,
        kWarn,
        kError,
        kFatal,
    }
public:
    void setLogLevel(Log::LogLevel l)
}

#endif //_LOG_H_
