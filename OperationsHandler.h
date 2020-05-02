#pragma once
#include "IOperationsHandler.h"
#include <cstring>
#include <string>
#include <vector>
#include <stack>
#include <cstdlib>
#include <csignal>
#include "FileHandler.h"
#include "IFileHandler.h"
#include <future>
#include <thread>

namespace OPERATIONSUTILITY
{
    class OperationsHandler : IOperationsHandler
    {
    protected:
        std::vector<std::string> *data;
        std::stack<std::string> *redo;
        FILEHANDLINGUTILITY::FileHandler* file_handler;
        std::thread t1;

        void EmptyRedoStack();
        void DataPopulation();
        void ParseCompleteStringByLineBreaks(const std::string& complete_string);
        void ParseDataModelToACompleteString(std::string& complete_string);
        bool InvokeSearchOperations();
        bool InvokeReplaceAllOperations();
        bool InvokeSaveOperations();
        bool key_pressed(int key);
    public:
        OperationsHandler(std::vector<std::string>& data, std::stack<std::string>& redo, FILEHANDLINGUTILITY::FileHandler*& file_handler);
        ~OperationsHandler();
        bool InputOperations();
        bool OutputOperations();
        bool SaveOperations();
        bool LoadOperations();
        bool UndoOperations();
        bool RedoOperations();
        bool SearchOperations(const std::string& key);
        bool ReplaceAllOperations(const std::string& key, const std::string& replace);
        bool InterruptProcesses();
        static void signal_callback_handler(int signum);
        void register_callbacks();
        bool CheckForAnsynchronousCalls();
    };
}