#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <cstdio>

#define DEBUG 0
#define INFO 1
#define WARNING 2
#define ERROR 3

namespace cylib{
    class Logger {
        private:
            int logLevel;
            std::string format;
            std::string fileDir;
            FILE* filePtr;
            std::string __getCurrentTime();
            std::string __getFormattedString(const std::string& message, const int levelName, const int lineno, const char* fileName);
            void __writeMessageToFile(const std::string& message);
        public:
            Logger();
            Logger(const int& logLevel, const std::string& fileDir, const char* readMode);
            void setLevel(const int& logLevel);
            void setFormat(const std::string& format);
            void debug(const std::string& message, const int lineno, const char* fileName);
            void info(const std::string& message, const int lineno, const char* fileName);
            void warning(const std::string& message, const int lineno, const char* fileName);
            void error(const std::string& message, const int lineno, const char* fileName);
    };
}


#endif
