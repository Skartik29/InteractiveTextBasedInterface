#include "pch.h"
#include "FileHandlerUnitTests.h"

namespace FILEHANDLINGUTILITY
{
    bool FileHandlerUnitTests::noFile(InputFileHandler* input_file_handler, std::string& test_string)
    {
        bool result = input_file_handler->InputOperations(test_string);
        std::cout << "Results of input Operations with no input file: " << test_string << std::endl;
        return result == true ? __success : __failure;
    }
    bool FileHandlerUnitTests::emptyFile(InputFileHandler* input_file_handler, std::string& test_string)
    {
        bool result = input_file_handler->InputOperations(test_string);
        std::cout << "Results of input Operations with an empty input file: " << test_string << std::endl;
        return result == true ? __success : __failure;
    }
    bool FileHandlerUnitTests::standardFile(InputFileHandler* input_file_handler, std::string& test_string)
    {
        bool result = input_file_handler->InputOperations(test_string);
        std::cout << "Results of input Operations with a standard input file: " << test_string << std::endl;
        return result == true ? __success : __failure;
    }
    bool FileHandlerUnitTests::largeFile(InputFileHandler* input_file_handler, std::string& test_string)
    {
        bool result = input_file_handler->InputOperations(test_string);
        std::cout << "Results of input Operations with a large input file: " << test_string << std::endl;
        return result == true ? __success : __failure;
    }
    bool FileHandlerUnitTests::TestingInputOperations()
    {
        std::string no_file = "no_file.txt";
        std::string empty_file = "empty_file.txt";
        std::string standard_file = "standard_file.txt";
        std::string large_file = "large_file.txt";

        std::string no_file_testing_string;
        std::string empty_file_testing_string;
        std::string standard_file_testing_string;
        std::string large_file_testing_string;

        FileHandler* no_file_handler = FileFactory::CreateFactory(no_file, FileMode::READ);
        FileHandler* empty_file_handler = FileFactory::CreateFactory(empty_file, FileMode::READ);
        FileHandler* standard_file_handler = FileFactory::CreateFactory(standard_file, FileMode::READ);
        FileHandler* large_file_handler = FileFactory::CreateFactory(large_file, FileMode::READ);

        InputFileHandler* input_no_file_handler = dynamic_cast<InputFileHandler*>(no_file_handler);
        if (input_no_file_handler)
        {
            bool result = noFile(input_no_file_handler, no_file_testing_string);
            if (result == __success) result = input_no_file_handler->CloseOperations();
        }
        InputFileHandler* input_empty_file_handler = dynamic_cast<InputFileHandler*>(empty_file_handler);
        if (input_empty_file_handler)
        {
            bool result = emptyFile(input_empty_file_handler, empty_file_testing_string);
            if (result == __success) result = input_empty_file_handler->CloseOperations();
        }
        InputFileHandler* input_standard_file_handler = dynamic_cast<InputFileHandler*>(standard_file_handler);
        if (input_standard_file_handler)
        {
            bool result = standardFile(input_standard_file_handler, standard_file_testing_string);
            if (result == __success) result = input_standard_file_handler->CloseOperations();
        }
        InputFileHandler* input_large_file_handler = dynamic_cast<InputFileHandler*>(large_file_handler);
        if (input_large_file_handler)
        {
            bool result = largeFile(input_large_file_handler, large_file_testing_string);
            if (result == __success) result = input_large_file_handler->CloseOperations();
        }

        delete no_file_handler;
        delete empty_file_handler;
        delete standard_file_handler;
        delete large_file_handler;

        return __success;
    }
    bool FileHandlerUnitTests::emptyString(OutputFileHandler* output_file_handler, const std::string& test_string)
    {
        bool result = output_file_handler->OutputOperations(test_string);
        if (result == __success)
        {
            output_file_handler->CloseOperations();
            return __success;
        }
        return __failure;
    }
    bool FileHandlerUnitTests::standardString(OutputFileHandler* output_file_handler, const std::string& test_string)
    {
        bool result = output_file_handler->OutputOperations(test_string);
        if (result == __success)
        {
            output_file_handler->CloseOperations();
            return __success;
        }
        return __failure;
    }
    bool FileHandlerUnitTests::largeString(OutputFileHandler* output_file_handler, const std::string& test_string)
    {
        bool result = output_file_handler->OutputOperations(test_string);
        if (result == __success)
        {
            output_file_handler->CloseOperations();
            return __success;
        }
        return __failure;
    }
    bool FileHandlerUnitTests::TestingOutputOperations()
    {
        bool result = __success;
        std::string empty_string = "";
        std::string standard_string = "this is testing string\nWe are here for a reason\nGood luck!!!\nBye";
        std::string large_string = "MigrationCodeSuggestions:\n1.] We run the migration code for all the versions.Do we add up on the changes version by version(in the loop) or could we have all changes made from given version to current version ?\n•	We could tweak CurrentReleaseFixup();\n2.] Do we need to handle the exception of pMigrator being null; like relay a message to the client ?\n3.] QRMMigration ?\n•	ERROR_FINALLY_PROTECT doesn’t have an end call\n4.] Modified flag in the part files ?\n5.] PHYS_material_private_access ?\nQuestions in general :";

        std::string empty_file = "empty_file_output.txt";
        std::string standard_file = "standard_file_output.txt";
        std::string large_file = "large_file_output.txt";

        FileHandler* empty_string_handler = FileFactory::CreateFactory(empty_file, FileMode::WRITE);
        FileHandler* standard_string_handler = FileFactory::CreateFactory(standard_file, FileMode::WRITE);
        FileHandler* large_string_handler = FileFactory::CreateFactory(large_file, FileMode::WRITE);

        OutputFileHandler* output_empty_string_handler = dynamic_cast<OutputFileHandler*>(empty_string_handler);
        if (output_empty_string_handler) result = emptyString(output_empty_string_handler, empty_string);
        OutputFileHandler* output_standard_string_handler = dynamic_cast<OutputFileHandler*>(standard_string_handler);
        if (output_standard_string_handler) result = standardString(output_standard_string_handler, standard_string);
        OutputFileHandler* output_large_string_handler = dynamic_cast<OutputFileHandler*>(large_string_handler);
        if (output_large_string_handler) result = largeString(output_large_string_handler, large_string);

        delete empty_string_handler;
        delete standard_string_handler;
        delete large_string_handler;
        
        return __success;
    }
}