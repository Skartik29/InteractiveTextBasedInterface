// DocumentBasedInterface.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "IFileHandler.h"
#include "FileHandler.h"
#include "FileHandlerUnitTests.h"
#include "IDataModel.h"
#include "DataModel.h"
#include "IOperationsHandler.h"
#include "OperationsHandler.h"
#include <array>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <csignal>
#include <future>
#include <thread>
#include <unordered_map>

using namespace FILEHANDLINGUTILITY;
using namespace DATAMODELARCHITECTURE;

int main()
{  
    DataModel* new_model = DataModelFactory::CreateFactory(DataModelType::SIMPLE);
    DataModelSimple* simple_model = dynamic_cast<DataModelSimple*>(new_model);
    if (simple_model)
    {        
        bool result = simple_model->GetOperationsHandler()->InputOperations();
        if (result)
            simple_model->GetOperationsHandler()->OutputOperations();        
    }
    delete new_model;
 }

