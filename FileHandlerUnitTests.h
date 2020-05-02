#pragma once
#include "IFileHandler.h"
#include "FileHandler.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace FILEHANDLINGUTILITY
{
    constexpr bool __success = true;
    constexpr bool __failure = false;

    class FileHandlerUnitTests
    {
    private:
        //Input operations testing
        bool noFile(InputFileHandler* input_file_handler, std::string& no_file);
        bool emptyFile(InputFileHandler* input_file_handler, std::string& empty_file);
        bool standardFile(InputFileHandler* input_file_handler, std::string& standard_file);
        bool largeFile(InputFileHandler* input_file_handler, std::string& large_file);
        //Output operations testing
        bool emptyString(OutputFileHandler* output_file_handler, const std::string& empty_string);
        bool standardString(OutputFileHandler* output_file_handler, const std::string& standard_string);
        bool largeString(OutputFileHandler* output_file_handler, const std::string& large_string);
    public:
        bool TestingInputOperations();
        bool TestingOutputOperations();
    };
}