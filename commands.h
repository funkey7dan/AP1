

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>

#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;

class DefaultIO{
public:
	virtual string read()=0;
	virtual void write(string text)=0;
	virtual void write(float f)=0;
	virtual void read(float* f)=0;
	virtual ~DefaultIO(){}

	// you may add additional methods here
    // add function to read/write to file?
};

// you may add here helper classes
struct MutualInfo{
    float threshold;
    vector<AnomalyReport> ar;
};


/**
 * standard input output class inherits from DefaultIO
 */
class StandardIO:public DefaultIO{
    string read() override{
        string s;
        cin >> s;
        return s;
    }
    void write(string text) override{
        cout << text << endl;
    }
    void write(float f) override{
        cout << f << endl;
    }
    void read(float* f) override{
        cin >> *f;
    }
};

// you may edit this class
class Command{
protected:
	DefaultIO* dio;
    const string description;
public:
	Command(DefaultIO* dio, string description):dio(dio), description(description){}
    string getDescription(){
        return this->description;
    }
    virtual void execute(MutualInfo *pInfo) =0;
	virtual ~Command(){}
};

// implement here your command classes
class UploadCSV: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit UploadCSV(DefaultIO* dio): Command(dio,"upload a time series csv file"){}
    void execute(MutualInfo *pInfo) override{

    }
};

class Settings: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Settings(DefaultIO* dio): Command(dio,"algorithm settings"){}
    void execute(MutualInfo *pInfo) override{

    }
};
class Detect: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Detect(DefaultIO* dio): Command(dio,"detect anomalies"){}
    void execute(MutualInfo *pInfo) override{

    }
};
class Display: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Display(DefaultIO* dio): Command(dio,"display results"){}
    void execute(MutualInfo *pInfo) override{

    }
};
class UploadAndAnalyze: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit UploadAndAnalyze(DefaultIO* dio): Command(dio,
                                                       "upload anomalies and analyze results"){}
    void execute(MutualInfo *pInfo) override{

    }
};
class Exit: public Command{
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Exit(DefaultIO* dio): Command(dio,"exit"){}
    void execute(MutualInfo *pInfo) override{

    }
};


#endif /* COMMANDS_H_ */
