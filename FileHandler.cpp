#include "pch.h"
#include "FileHandler.h"
#include <iostream>
#include <cassert>
#include <sstream>

namespace FILEHANDLINGUTILITY
{
    FileHandler::FileHandler(const std::string& filename)
    {
        this->filename = filename;
    }

    bool FileHandler::RemoveFile()
    {
        std::remove(filename.c_str());
        return true;
    }

    FileHandler::~FileHandler()
    {
        this->filename = "";
    }

    InputFileHandler::InputFileHandler(const std::string& filename) : FileHandler(filename)
    {
        //Do nothing
    }

    bool InputFileHandler::InputOperations(std::string& data)
    {
        file_object.open(filename);
        if (file_object.is_open())
        {
            std::stringstream strStream;
            strStream << file_object.rdbuf(); //read the file
            data = strStream.str();
            return true;
        }
        else return false;
    }

    bool InputFileHandler::CloseOperations()
    {
        if (IsFileOpen())
            file_object.close();
        return true;
    }

    bool InputFileHandler::IsFileOpen()
    {
        if (file_object.is_open())
            return true;
        else
            return false;
    }

    InputFileHandler::~InputFileHandler()
    {
        CloseOperations();
    }

    OutputFileHandler::OutputFileHandler(const std::string& filename) : FileHandler(filename)
    {
        this->mode = FileMode::WRITE;
        //Do nothing
    }

    OutputFileHandler::OutputFileHandler(const std::string& filename, const FileMode& mode) : FileHandler(filename)
    {
        this->mode = mode;
        //Do nothing
    }

    bool OutputFileHandler::OutputOperations(const std::string& data)
    {      
        switch (mode)
        {
            case FileMode::WRITE:
            {
                RemoveFile();
                file_object.open(filename, std::ofstream::out);
                break;
            }
            case FileMode::APPEND:
            {
                file_object.open(filename, std::ofstream::app);
                break;
            }
            default:
            {
                file_object.open(filename, std::ofstream::out | std::ofstream::app);
                break;
            }
        }
        if (file_object.is_open())
        {
            file_object << data;
            return true;
        }
        else return false;
    }

    bool OutputFileHandler::CloseOperations()
    {
        if (IsFileOpen())
            file_object.close();
        return true;
    }

    bool OutputFileHandler::IsFileOpen()
    {
        if (file_object.is_open())
            return true;
        else
            return false;
    }

    OutputFileHandler::~OutputFileHandler()
    {
        CloseOperations();
    }

    FileHandler* FileFactory::CreateFactory(const std::string& filename, const FileMode& mode)
    {
        //static_assert(mode < FileMode::END, "Invalid filemode\n");
        switch (mode)
        {
        case FileMode::READ:
            return new InputFileHandler(filename);
        case FileMode::WRITE:
            return new OutputFileHandler(filename);
        case FileMode::APPEND:
            return new OutputFileHandler(filename, FileMode::APPEND);
        default:
            return nullptr;
        }
    }
}