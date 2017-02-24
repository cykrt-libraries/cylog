# CyLog
**NOTE: This project was made primarily as a learning exercise, and will neither be maintained nor should be used in a production environment.**

A python-like logging moudle in C++


## Features

* Time/date stamped output
* Filename/Lineno output
* Format can be customized
* Log level can be customized

## Usage
Here is a simple example.  

    #include "logging.hpp"
    int main(){
        cylib::Logger logger(DEBUG, "log.txt", "w+");
        logger.debug("debug", __LINE__, __FILE__);
        return 0;
    }


The output is:

    [24-02-2017 07:00:27][DEBUG][logging.cpp][line:65]debug

Formatting example:

    logger.setFormat("[%(asctime)s]%(message)s");

 - `%(asctime)s` Datetime
 - `%(lineno)s` The line number of the log code
 - `%(filename)s`The name of the file where the log code is located
 - `%(levelname)s` The name of the Logging Level.
 - `%(message)s` The message you want output, it is necessary.

Logging Levels:
* DEBUG
* INFO
* WARNING
* ERROR
