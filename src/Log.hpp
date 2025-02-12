#include <iostream>
#include <fstream>

#ifndef __NOTEMAN_LOG_HPP__
#define __NOTEMAN_LOG_HPP__

class Log{
    public:
        const int LogLevelInfo  = 0;
        const int LogLevelWarn  = 1;
        const int LogLevelError = 2;
        void ChangeLogLvl(int level){pm_CurrentLogLevel = level;}
        
        void Info(std::string message){
            if(pm_CurrentLogLevel <= 0){
                std::cerr << "[INFO]: " << message << '\n';
            }
        }
        void Warn(std::string message){
            if(pm_CurrentLogLevel <= 1){
                std::cerr << "[WARNING]: " << message << '\n';
            }
        }
        void Error(std::string message){
            if(pm_CurrentLogLevel <= 2){
                std::cerr << "[ERROR]: " << message << '\n';
            }
        }

    private:
        int pm_CurrentLogLevel {LogLevelWarn};

};
#endif // NOTEMAN_LOG_HPP
