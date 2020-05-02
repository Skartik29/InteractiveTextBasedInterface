#pragma once
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>

namespace DATAMODELARCHITECTURE
{
    class IDataModel
    {
    public:
        virtual ~IDataModel() {}
        virtual bool InputOperations() = 0;
        virtual bool OutputOperations() = 0;
        virtual bool SaveOperations() = 0;
        virtual bool LoadOperations() = 0;
        virtual bool UndoOperations() = 0;
        virtual bool RedoOperations() = 0;
        virtual bool SearchOperations(const std::string& key) = 0;
        virtual bool ReplaceAllOperations(const std::string& key, const std::string& replace) = 0;
        virtual bool InterruptProcesses() = 0;
    };
}