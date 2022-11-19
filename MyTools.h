#pragma once

#include <stdint.h>
#include <string>

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================


	class FileLoggerSingletone
	{
	public:

        static FileLoggerSingletone& getStr()
        {
            static FileLoggerSingletone theInstance;
            return theInstance;
        }

        void  OpenLogFile(const std::string& FN);

        void CloseLogFile();

        void  WriteToLog(const std::string& str);

        void  WriteToLog(const std::string& str, int n);

        void  WriteToLog(const std::string& str, double d);

    protected:
        FileLoggerSingletone() {};
	private:
        
        FileLoggerSingletone(const FileLoggerSingletone& root) = delete;
        FileLoggerSingletone& operator=(const FileLoggerSingletone&) = delete;
	};


    class LoggerSingleton : public FileLoggerSingletone
    {
    public:
        LoggerSingleton(FileLoggerSingletone* log) : File(log)
        {

        };

        ~LoggerSingleton()
        {
            delete File;
        };

    private:
        FileLoggerSingletone* File;
    };

	//=============================================================================================

};