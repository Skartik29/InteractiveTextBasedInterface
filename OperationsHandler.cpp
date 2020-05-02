#include "pch.h"
#include "OperationsHandler.h"
#include "MenuHandler.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <csignal>
#include <cstring>

using namespace MENUHANDLINGUTILITY;
namespace OPERATIONSUTILITY
{
    //Temporary object to hold the session object to handle interrupt processes
    static OperationsHandler* session_object = nullptr;

    //Operations handler
    OperationsHandler::OperationsHandler(std::vector<std::string>& data, std::stack<std::string>& redo, FILEHANDLINGUTILITY::FileHandler*& file_handler)
    {
        this->data = &data;
        this->redo = &redo;
        this->file_handler = file_handler;
        LoadOperations();
        register_callbacks();
        t1 = std::thread(&OperationsHandler::CheckForAnsynchronousCalls, this);
    }

    //EmptyRedoStack
    void OperationsHandler::EmptyRedoStack()
    {
        if (redo != nullptr)
        {
            int sz = redo->size();
            while (sz > 0)
            {
                redo->pop();
                sz--;
            }
        }
    }

    //Destructor
    OperationsHandler::~OperationsHandler()
    {
        if (file_handler != nullptr)
        {
            delete file_handler;
            file_handler = nullptr;
        }
        InterruptProcesses();
        //bool res = asyncResults.get();
        t1.detach();
    }

    //Keyboard events
    bool OperationsHandler::key_pressed(int key)
    {
        return (GetAsyncKeyState(key) & 0x8000 != 0);
    }

    //Console shutdown event
    void OperationsHandler::signal_callback_handler(int signum)
    {
        if (session_object)
        {
            std::future<bool> interrupt_processes = std::async(&OperationsHandler::InterruptProcesses, session_object);
            bool result = interrupt_processes.get();
            if (session_object->file_handler != nullptr)
            {
                delete session_object->file_handler;
                session_object->file_handler = nullptr;
            }
        }
    }

    //Population of user input into data model
    void OperationsHandler::DataPopulation()
    {
        std::string string_input_line;
        while (std::getline(std::cin, string_input_line))
        {
            std::cout << MenuHandler(MenuOptions::NEXTLINE);
            if (key_pressed(VK_LEFT))
            {
                bool result = UndoOperations();
            }
            else if (key_pressed(VK_RIGHT))
            {
                bool result = RedoOperations();
            }
            else if (key_pressed(VK_UP))
            {               
                InvokeSearchOperations();
            }
            else if (key_pressed(VK_DOWN))
            {
                InvokeReplaceAllOperations();
            }
            else if (key_pressed(VK_CONTROL))
            {
                break;
            }           
            else
            {
                data->push_back(string_input_line);
                EmptyRedoStack();
            }
        }
    }

    //Parse a complete string by lines and populate the data model
    void OperationsHandler::ParseCompleteStringByLineBreaks(const std::string& complete_string)
    {
        std::stringstream ss(complete_string);
        std::string each_line;
        while (std::getline(ss, each_line, '\n'))
        {
            data->push_back(each_line);
        }
    }

    //Parse the data model and fill up the entire string
    void OperationsHandler::ParseDataModelToACompleteString(std::string& complete_string)
    {
        for (auto it : *data)
        {
            complete_string += it;
            complete_string += "\n";
        }
    }

    //Invoke search  operations via key press
    bool OperationsHandler::InvokeSearchOperations()
    {
        std::cout << MenuHandler(MenuOptions::SEARCH);
        std::string search_key;
        std::getline(std::cin, search_key);
        return SearchOperations(search_key);
    }

    //Invoke replace all operations via key press
    bool OperationsHandler::InvokeReplaceAllOperations()
    {
        std::cout << MenuHandler(MenuOptions::SEARCH);
        std::string search_key;
        std::getline(std::cin, search_key);
        std::cout << MenuHandler(MenuOptions::REPLACE);
        std::string replace_key;
        std::getline(std::cin, replace_key);
        return ReplaceAllOperations(search_key, replace_key);
    }

    bool OperationsHandler::InvokeSaveOperations()
    {
        return SaveOperations();
    }

    bool OperationsHandler::CheckForAnsynchronousCalls()
    {
        while (true)
        {
            InvokeSaveOperations();
            Sleep(2000);
        }
    }

    void OperationsHandler::register_callbacks()
    {
        std::signal(SIGBREAK, &OperationsHandler::signal_callback_handler);
    }

    bool OperationsHandler::InputOperations()
    {
        //Ask for user inputs
        std::cout << MenuHandler(MenuOptions::INPUTFROM);
        int choice = 2;
        std::cin >> choice;
        if (choice > 2) choice = 2;
        switch (choice)
        {
        case 1:
        {
            bool operation_result = false;
            std::string string_input_line;
            std::cout << MenuHandler(MenuOptions::READFILE);
            std::cin >> string_input_line;
            if (file_handler != nullptr)
            {
                delete file_handler;
                file_handler = nullptr;
            }
            file_handler = FILEHANDLINGUTILITY::FileFactory::CreateFactory(string_input_line, FILEHANDLINGUTILITY::FileMode::READ);
            FILEHANDLINGUTILITY::InputFileHandler* input_file_handler = nullptr;
            if (file_handler)
                input_file_handler = dynamic_cast<FILEHANDLINGUTILITY::InputFileHandler*>(file_handler);
            if (input_file_handler)
            {
                std::string complete_data;
                bool result = input_file_handler->InputOperations(complete_data);
                if (result == true)
                {
                    EmptyRedoStack();
                    ParseCompleteStringByLineBreaks(complete_data);
                    //delete input_file_handler;
                    DataPopulation();
                }
                operation_result = result;
            }
            return operation_result;
        }
        case 2:
        {
            DataPopulation();
            break;
        }
        }
        return true;
    }

    bool OperationsHandler::OutputOperations()
    {
        //Ask for user inputs
        std::cout << MenuHandler(MenuOptions::WRITETO);
        int choice = 2;
        std::cin >> choice;
        if (choice > 2) choice = 2;
        switch (choice)
        {
        case 1:
        {
            bool operation_result = false;
            std::string string_input_line;
            std::cout << MenuHandler(MenuOptions::WRITEFILE);
            std::cin >> string_input_line;
            if (file_handler != nullptr)
            {
                delete file_handler;
                file_handler = nullptr;
            }
            file_handler = FILEHANDLINGUTILITY::FileFactory::CreateFactory(string_input_line, FILEHANDLINGUTILITY::FileMode::WRITE);
            FILEHANDLINGUTILITY::OutputFileHandler* output_file_handler = nullptr;
            if (file_handler)
                output_file_handler = dynamic_cast<FILEHANDLINGUTILITY::OutputFileHandler*>(file_handler);
            if (output_file_handler)
            {
                std::string complete_data;
                ParseDataModelToACompleteString(complete_data);
                bool result = output_file_handler->OutputOperations(complete_data);
                if (result == true)
                {
                    //delete output_file_handler;
                }
                operation_result = result;
            }
            return operation_result;
        }
        case 2:
        {
            for (auto it : *data)
            {
                std::cout << it << std::endl;
            }
            break;
        }
        }
        return true;
    }

    bool OperationsHandler::SaveOperations()
    {
        bool operation_result = false;
        std::string load_file = "load_file_text_based_interface.txt";
        if (file_handler != nullptr)
        {
            delete file_handler;
            file_handler = nullptr;
        }
        file_handler = FILEHANDLINGUTILITY::FileFactory::CreateFactory(load_file, FILEHANDLINGUTILITY::FileMode::WRITE);
        FILEHANDLINGUTILITY::OutputFileHandler* output_file_handler = nullptr;
        if (file_handler)
            output_file_handler = dynamic_cast<FILEHANDLINGUTILITY::OutputFileHandler*>(file_handler);
        if (output_file_handler)
        {
            std::string complete_data;
            ParseDataModelToACompleteString(complete_data);
            bool result = output_file_handler->OutputOperations(complete_data);
            if (result == true)
            {
                //delete output_file_handler;
            }
            operation_result = result;
        }
        return operation_result;
    }

    bool OperationsHandler::LoadOperations()
    {
        session_object = this;

        bool operation_result = false;
        std::string load_file = "load_file_text_based_interface.txt";
        if (file_handler != nullptr)
        {
            delete file_handler;
            file_handler = nullptr;
        }
        std::string string_input_line;
        std::cout << MenuHandler(MenuOptions::LOADOPTIONS);
        std::cin >> string_input_line;
        if (string_input_line == "1")
        {
            file_handler = FILEHANDLINGUTILITY::FileFactory::CreateFactory(load_file, FILEHANDLINGUTILITY::FileMode::READ);
            FILEHANDLINGUTILITY::InputFileHandler* input_file_handler = nullptr;
            if (file_handler)
                input_file_handler = dynamic_cast<FILEHANDLINGUTILITY::InputFileHandler*>(file_handler);
            if (input_file_handler)
            {
                std::string complete_data;
                bool result = input_file_handler->InputOperations(complete_data);
                if (result == true)
                {
                    EmptyRedoStack();
                    ParseCompleteStringByLineBreaks(complete_data);
                    input_file_handler->RemoveFile();
                    //delete input_file_handler;
                }
                operation_result = result;
            }
        }
        return operation_result;
    }
    bool OperationsHandler::UndoOperations()
    {
        if (data)
        {
            int sz = data->size();
            if (sz > 0)
            {
                redo->push((*data)[sz - 1]);
                data->pop_back();
            }
            return true;
        }
        else
            return false;
    }

    bool OperationsHandler::RedoOperations()
    {
        if (!redo->empty())
        {
            data->push_back(redo->top());
            redo->pop();
            return true;
        }
        return false;
    }

    bool OperationsHandler::SearchOperations(const std::string& key)
    {
        int ct = 1;
        for (auto it : *data)
        {
            int length_parent = it.length();
            for (int i = 0; i < length_parent; ++i)
            {
                int ind_parent = i;
                int ind_key = 0;
                int length_key = key.length();
                while ((ind_key < length_key && ind_parent < length_parent) && it[ind_parent] == key[ind_key])
                {
                    ind_parent++;
                    ind_key++;
                }
                if (ind_key >= length_key)
                    std::cout << "Found at: line: " << ct << " character: " << i << std::endl;
            }
            ct++;
        }
        return true;
    }

    bool OperationsHandler::ReplaceAllOperations(const std::string& key, const std::string& replace)
    {
        for (auto &it : *data)
        {
            int length_parent = it.length();
            for (int i = 0; i < length_parent; ++i)
            {
                int ind_parent = i;
                int ind_key = 0;
                int length_key = key.length();
                while ((ind_key < length_key && ind_parent < length_parent) && it[ind_parent] == key[ind_key])
                {
                    ind_parent++;
                    ind_key++;
                }
                if (length_key > 0 && ind_key >= length_key)
                {
                    it.replace(i, length_key, replace);
                    length_parent = it.length();
                    i += replace.length();
                }
            }
        }
        return true;
    }

    bool OperationsHandler::InterruptProcesses()
    {
        return SaveOperations();
    }
}