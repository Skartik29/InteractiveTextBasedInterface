#pragma once
#include <cstring>
#include <iostream>

namespace FILEHANDLINGUTILITY
{
    class IFileHandler
    {
    public:
        virtual ~IFileHandler() {}
        virtual bool CloseOperations() = 0;
        virtual bool IsFileOpen() = 0;
    };
    class IFileInputHandler : public IFileHandler
    {
    public:
        virtual ~IFileInputHandler() {}
        virtual bool InputOperations(std::string& data) = 0;
    };
    class IFileOutputHandler : public IFileHandler
    {
    public:
        virtual ~IFileOutputHandler() {}
        virtual bool OutputOperations(const std::string& data) = 0;
    };
}