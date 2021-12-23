#include "CLI.h"

/**
 * construcor.
 * @param dio is DefaultIO tool (standard or network based (sockets).
 */
CLI::CLI(DefaultIO* dio) {
    this->dio = dio;
    this->commands.push_back(new UploadCSV(dio));
    this->commands.push_back(new Settings(dio));
    this->commands.push_back(new Detect(dio));
    this->commands.push_back(new Display(dio));
    this->commands.push_back(new UploadAndAnalyze(dio));
    this->commands.push_back(new Exit(dio));
}

/**
 * main program's fuction - display server's menu and activates each command.
 */
void CLI::start(){
    MutualInfo mutualInfo;
    int size = this->commands.size();
    int choiceNum = -99;
    // size - 1 is the index of exit command
    while (choiceNum != size - 1){
        // print menu
        this->dio->write("Welcome to the Anomaly Detection Server.\nPlease choose an option:\n");
        for (int i = 0; i < size; ++i){
            // first, write option number
            this->dio->write((char)(i + 1));
            this->dio->write(".");
            this->dio->write(this->commands[i]->getDescription() + "\n");
        }
        string choice = dio->read();
        // convert choice to int
        choiceNum = choice[0] - '0' - 1;
        if (choiceNum >= 0 && choiceNum < size){
            this->commands[choiceNum]->execute(&mutualInfo);
        }
    }
}

/**
 * destructor - delete each element in commands vecor we created in constructor.
 */
CLI::~CLI() {
    int size = this->commands.size();
    for (int i = 0; i < size; ++i) {
        delete this->commands[i];
    }
}

