//
//  main.cpp
//  testAnalyse
//
//  Created by Alistair Baxter on 17/07/2017.
//  Copyright © 2017 Alistair Baxter. All rights reserved.
//

#include <string>
#include <iostream>
#include <assert.h>

#include "analyse.hpp"

/**
 * Return the string corresponding to an analysis error number
 *
 * @return Error description
 */
std::string errorDescription(int errNum)
{
    switch (errNum)
    {
    case analysis::Error_NoError:
        return std::string("Success");
    case analysis::Error_InputFileInvalid:
        return std::string("Input File Invalid");
    case analysis::Error_ReadError:
        return std::string("Read Error");
    case analysis::Error_InvalidNumber:
        return std::string("InvalidNumber");
    case analysis::Error_InvalidAnalyis:
        return std::string("InvalidAnalyis");
    case analysis::Error_OutputFileInvalid:
        return std::string("OutputFileInvalid");
    case analysis::Error_WriteError:
        return std::string("WriteError");
    default:
        return std::string("Unknown");
    }
}

// Test Data
enum{
    NumTests = 2
};

std::string testInputFiles[NumTests] =
{
    "test1.txt",
    "FileDoesNotExists.txt",
};

std::string testOutputFiles[NumTests] =
{
    "result1.txt"
    "result2.txt"
};

int expectedTestResults[NumTests] =
{
    analysis::Error_NoError,
    analysis::Error_InputFileInvalid
};

int64_t expectedOutputValues[NumTests][3] =
{
    { 19, 135727, 7143 },
    { 0, 0, 0 }

};

int main(int argc, const char * argv[]) {

    
    // Run through all tests
    for (int i=0; i< NumTests; i++)
    {
        std::cout << "Testing input: " << testInputFiles[i] << "  output: " << testOutputFiles[i];
        std::cout << " Expecting result: " << errorDescription(expectedTestResults[i]) << std::endl;
        int result = analyse(testInputFiles[i].c_str(), testOutputFiles[i].c_str());
        std::cout << "Analysis returned: " << errorDescription(result) << "" << std::endl;

        assert(result == expectedTestResults[i]);
        
        if (result == analysis::Error_NoError)
        {
            // Test resulting values
        }
        
    }
    
    

    
    return 0;
}
