#pragma once
#include "gameHandler.h"


#define LOG_ERROR(errorMessage, line) do { \
  cout << "Debug message: <-- Logger detected an error --> (" << errorMessage  << "..." << "at line: " << line << ")" << std::endl;  \
} while (0)  