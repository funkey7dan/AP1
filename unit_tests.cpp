//
// Created by funke on 11/5/2021.
//

#include <iostream>
#include "commands.h"
#include "unit_tests.h"
#include "CLI.h"

//small test
int main(){
    StandardIO std;
    CLI cli(&std);
    cli.start();
    cout<<"done"<<endl;
    return 0;
}