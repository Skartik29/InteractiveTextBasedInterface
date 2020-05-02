#pragma once
#include "IFileHandler.h"
#include <string>
#include <fstream>

namespace FILEHANDLINGUTILITY
{
    enum class FileMode
    {
        READ = 0,
        WRITE,
        APPEND, 
        END
    };

    class FileHandler : public IFileHandler
    {
    protected:
        std::string filename;
    public:
        FileHandler(const std::string& filename);
        virtual bool RemoveFile();
        virtual bool CloseOperations() override = 0;
        virtual bool IsFileOpen() override = 0;
        ~FileHandler();
    };

    class InputFileHandler : public FileHandler, public IFileInputHandler
    {
    protected:
        std::ifstream file_object;
    public:
        InputFileHandler(const std::string& filename);
        bool InputOperations(std::string& data);
        bool CloseOperations();
        bool IsFileOpen();
        ~InputFileHandler();
    };

    class OutputFileHandler : public FileHandler, public IFileOutputHandler
    {
    protected:
        FileMode mode;
        std::ofstream file_object;
    public:
        OutputFileHandler(const std::string& filename);
        OutputFileHandler(const std::string& filename, const FileMode& mode);
        bool OutputOperations(const std::string& data);
        bool CloseOperations();
        bool IsFileOpen();
        ~OutputFileHandler();
    };

    class FileFactory
    {
    public:
        static FileHandler* CreateFactory(const std::string& filename, const FileMode& mode);
    };
}