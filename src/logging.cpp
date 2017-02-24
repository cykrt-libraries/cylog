#include "logging.hpp"


namespace cylib{

    Logger::Logger(){
        this->logLevel = DEBUG;
        this->format = "[%(asctime)s][%(levelname)s][%(filename)s][line:%(lineno)d]%(message)s";
        this->fileDir = "log.txt";
    }

    Logger::Logger(const int& logLevel, const std::string& fileDir, const char* readMode){
        this->logLevel = logLevel;
        this->format = "[%(asctime)s][%(levelname)s][%(filename)s][line:%(lineno)d]%(message)s";
        this->fileDir = fileDir;
        this->filePtr = fopen(fileDir.c_str(), readMode);
        fclose(this->filePtr);
    }

    void Logger::setFormat(const std::string& format){
        this->format = format;
    }

    void Logger::setLevel(const int& logLevel){
        this->logLevel = logLevel;
    }

    void Logger::info(const std::string& message, const int lineno, const char* fileName){
        if(this->logLevel >= INFO)
            std::cout << __getFormattedString(message, INFO, lineno, fileName) << std::endl;
    }

    void Logger::debug(const std::string& message, const int lineno, const char* fileName){
        if(this->logLevel >= DEBUG){
            std::cout << __getFormattedString(message, DEBUG, lineno, fileName) << std::endl;
        }
    }

    void Logger::warning(const std::string& message, const int lineno, const char* fileName){
        if(this->logLevel >= WARNING){
            std::cout << __getFormattedString(message, WARNING, lineno, fileName) << std::endl;
        }

    }

    void Logger::error(const std::string& message, const int lineno, const char* fileName){
        if(this->logLevel >= ERROR)
            std::cout << __getFormattedString(message, ERROR, lineno, fileName) << std::endl;
    }

    std::string Logger::__getCurrentTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char result[80];
        time (&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(result, 80,"%d-%m-%Y %I:%M:%S", timeinfo);
        return std::string(result);
    }

    std::string Logger::__getFormattedString(const std::string& message, const int levelName, const int lineno, const char* fileName){
        char levelNameList[][100] = {"DEBUG", "INFO", "WARNING", "ERROR"};
        char formatList[][100] = {"%(asctime)s", "%(filename)s", "%(lineno)d", "%(levelname)s", "%(message)s"};
        std::stringstream lineNumber;
        lineNumber << lineno;
        std::vector<std::string> resultList;
        resultList.push_back(__getCurrentTime());
        resultList.push_back(fileName);
        resultList.push_back(lineNumber.str());
        resultList.push_back(levelNameList[levelName]);
        resultList.push_back(message);
        std::string result = this->format;
        for(int i = 0;i < sizeof(formatList) / sizeof(formatList[0]);++i){
            size_t pos = result.find(formatList[i]);
            if(pos == std::string::npos) {
            } else {
                result.replace(pos, std::string(formatList[i]).size(), resultList[i]);
            }
        }
        __writeMessageToFile(result);
        return result;

    }

    void Logger::__writeMessageToFile(const std::string& message){
        this->filePtr = fopen(this->fileDir.c_str(), "a+");
        fprintf(this->filePtr, "%s\n", message.c_str());
        fclose(this->filePtr);
    }
}
