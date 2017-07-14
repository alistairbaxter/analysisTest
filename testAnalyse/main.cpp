//
//  main.cpp
//  testAnalyse
//
//  Created by Alistair Baxter on 14/07/2017.
//  Copyright © 2017 Alistair Baxter. All rights reserved.
//

#include <string>
#include <iostream>

#include "analyse.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    int result = analyse("test1.txt", "result1.txt");
    
    return result;
}
