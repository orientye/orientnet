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
    void trace(const char *s);
    void debug(const char *s);
    void info(const char *s);
    void warn(const char *s);
    void error(const char *s);
    void fatal(const char *s);
}

#endif //_LOG_H_
