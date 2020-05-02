#pragma once
#include "IDataModel.h"
#include <string>
#include <stack>
#include <vector>
#include <cstdlib>
#include <csignal>
#include "FileHandler.h"
#include "IFileHandler.h"
#include "IOperationsHandler.h"
#include "OperationsHandler.h"

namespace DATAMODELARCHITECTURE
{
    enum class DataModelType
    {
        SIMPLE = 0,
        IMPROVED,
        END
    };

    class DataModel
    {
    protected:
        std::vector<std::string> data;
        std::stack<std::string> redo;
        FILEHANDLINGUTILITY::FileHandler* file_handler;
        OPERATIONSUTILITY::OperationsHandler* operations_handler;
    public:
        virtual ~DataModel();
        DataModel();
        OPERATIONSUTILITY::OperationsHandler* GetOperationsHandler() const;
    };

    class DataModelSimple : public DataModel
    {
    protected:
        
    public:
        DataModelSimple();
        ~DataModelSimple();
    };

    class DataModelFactory
    {
    public:
        static DataModel* CreateFactory(const DataModelType& type);
    };
}