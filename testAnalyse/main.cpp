//
//  main.cpp
//  testAnalyse
//
//  Created by Alistair Baxter on 17/07/2017.
//  Copyright © 2017 Alistair Baxter. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>

#include "analyse.hpp"

// Since this is the test program, also include internal headers
// so that we can reuse our text file i/o
#include "NumberListParser.hpp"
#include "NumberListWriter.hpp"

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
    NumTests = 6
};

std::string testInputFiles[NumTests] =
{
    "test1.txt",
    "FileDoesNotExists.txt",
    "test3generated.txt",
    "test4generated.txt",
    "test5.txt",
    "test1.txt"
};

std::string testOutputFiles[NumTests] =
{
    "result1.txt",
    "result2.txt",
    "result3.txt",
    "result4.txt",
    "result5.txt",
    ""
};

int expectedTestResults[NumTests] =
{
    analysis::Error_NoError,
    analysis::Error_InputFileInvalid,
    analysis::Error_InvalidAnalyis,
    analysis::Error_NoError,
    analysis::Error_InvalidNumber,
    analysis::Error_OutputFileInvalid
};

int64_t expectedOutputValues[NumTests][3] =
{
    { 19, 135727, 7143 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 3, INT64_MAX / 2, INT64_MAX / 6 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

int main(int argc, const char * argv[])
{
    int64_t veryLargeNumber = INT64_MAX / 2;
    
    // Generate a test file with very large numbers in
    {
        analysis::NumberListWriter testFile3(testInputFiles[2]);
        testFile3.writeNumber(veryLargeNumber);
        testFile3.writeNumber(veryLargeNumber);
        testFile3.writeNumber(veryLargeNumber);
        
    }
    
    // Generate a test file with very large, but valid numbers in
    {
        analysis::NumberListWriter testFile4(testInputFiles[3]);
        testFile4.writeNumber( veryLargeNumber);
        testFile4.writeNumber(-veryLargeNumber);
        testFile4.writeNumber( veryLargeNumber);
    }
    
    
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
            
            analysis::NumberListParser outputsParser( testOutputFiles[i] );
            
            if (outputsParser.isValid())
            {
                int64_t countVal = 0;
                int64_t sumVal = 0;
                int64_t averageVal = 0;
                
                outputsParser.getNextNumber(countVal);
                outputsParser.getNextNumber(sumVal);
                outputsParser.getNextNumber(averageVal);

                std::cout << "Expected output count: " << expectedOutputValues[i][0];
                std::cout << " sum: " << expectedOutputValues[i][1];
                std::cout << " average: " << expectedOutputValues[i][2] << std::endl;
                
                std::cout << "Actual output count: " << countVal;
                std::cout << " sum: " << sumVal;
                std::cout << " average: " << averageVal << std::endl;
                
                assert(countVal == expectedOutputValues[i][0]);
                assert(sumVal == expectedOutputValues[i][1]);
                assert(averageVal == expectedOutputValues[i][2]);
            }
        }
    
    }

    
    return 0;
}
