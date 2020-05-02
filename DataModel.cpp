#include "pch.h"
#include "DataModel.h"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <csignal>
#include <cstring>
#include <future>
#include <thread>

namespace DATAMODELARCHITECTURE
{
    //Temporary object to hold the session object to handle interrupt processes
    static DataModel* session_object = nullptr;

    //Data Model
    DataModel::DataModel()
    {
        file_handler = nullptr;
        operations_handler = new OPERATIONSUTILITY::OperationsHandler(data, redo, file_handler);
    }

    //Getter for Operations Handler
    OPERATIONSUTILITY::OperationsHandler* DataModel::GetOperationsHandler() const
    {
        return operations_handler;
    }

    //Destructor
    DataModel::~DataModel()
    {
        if (file_handler != nullptr)
        {
            delete file_handler;
            file_handler = nullptr;
        }
        if (operations_handler != nullptr)
        {
            delete operations_handler;
            operations_handler = nullptr;
        }
    }

    //Data Model : Simple
    DataModelSimple::DataModelSimple() : DataModel()
    {
     
    }

    DataModelSimple::~DataModelSimple()
    {
       operations_handler->InterruptProcesses();
    }

    DataModel* DataModelFactory::CreateFactory(const DataModelType& type)
    {
        switch (type)
        {
        case DataModelType::SIMPLE:
            return new DataModelSimple();
        default:
            return nullptr;
        }
    }
}