
#ifndef COMMANDS_H_
#define COMMANDS_H_
#include<iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"
using namespace std;
class DefaultIO {
public:
    virtual string read() = 0;
    virtual void write(string text) = 0;
    virtual void write(float f) = 0;
    virtual void read(float *f) = 0;

    virtual ~DefaultIO()
    {}

    // you may add additional methods here
    // add function to read/write to file?
    void readFile(string fileName)
    {

        std::ofstream outfile(fileName);
        string line = "";
        while ((line = read()) != "done")
        {
            outfile << line << endl;
        }
        outfile.close();
    }
};
// a struct to represent the union of reports into a time period.
struct comboReport {
    long start;
    long end;
    string description;
    bool isFP = false;
};
// you may add here helper classes
struct MutualInfo {
    float threshold = 0.9;
    vector<AnomalyReport> ar;
    vector<comboReport> crVector;
    int numOfRows;
};
/**
 * standard input output class inherits from DefaultIO
 */
class StandardIO : public DefaultIO {
    string read() override
    {

        string s;
        cin >> s;
        return s;
    }

    void write(string text) override
    {

        cout << text;
    }

    void write(float f) override
    {

        cout << f;
    }

    void read(float *f) override
    {

        cin >> *f;
    }
};
// you may edit this class
class Command {
protected:
    DefaultIO *dio;
    const string description;
public:
    Command(DefaultIO *dio, string description) : dio(dio), description(description)
    {}

    string getDescription()
    {

        return this->description;
    }

    virtual void execute(MutualInfo *pInfo) = 0;

    virtual ~Command()
    {}
};
// implement here your command classes
class UploadCSV : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit UploadCSV(DefaultIO *dio) : Command(dio, "upload a time series csv file")
    {}

    void execute(MutualInfo *pInfo) override
    {

        dio->write("Please upload your local train CSV file.\n");
        dio->readFile("anomalyTrain.csv");
        dio->write("Upload complete.\n");
        dio->write("Please upload your local test CSV file.\n");
        dio->readFile("anomalyTest.csv");
        dio->write("Upload complete.\n");
    }
};
class Settings : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Settings(DefaultIO *dio) : Command(dio, "algorithm settings")
    {}

    void execute(MutualInfo *pInfo) override
    {

        float thrshld;
        bool isCorrect = false;
        do
        {
            dio->write("The current correlation threshold is ");
            dio->write(pInfo->threshold);
            dio->write("\n");
            dio->write("Type a new threshold\n");
            dio->read(&thrshld);
            if(thrshld <= 0 || thrshld > 1)
            {
                dio->write("please choose a value between 0 and 1.\n");
            }
            else
            {
                isCorrect = true;
                pInfo->threshold = thrshld;
            }
        } while (!isCorrect);
    }
};
class Detect : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Detect(DefaultIO *dio) : Command(dio, "detect anomalies")
    {}

    void execute(MutualInfo *pInfo) override
    {

        HybridAnomalyDetector had;
        had.setThreshold(pInfo->threshold);
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        had.learnNormal(train);
        pInfo->ar = had.detect(test);
        pInfo->numOfRows = test.getColSize();
        comboReport cr;
        cr.start = 0;
        cr.end = 0;
        cr.description = "";
        for (auto &report: pInfo->ar)
        {
            if(report.timeStep == cr.end + 1 && report.description == cr.description)
            {
                cr.end++;
            }
            else
            {
                pInfo->crVector.push_back(cr);
                cr.start = report.timeStep;
                cr.end = cr.start;
                cr.description = report.description;
            }
        }
        pInfo->crVector.push_back(cr);
        pInfo->crVector.erase(pInfo->crVector.begin());
        dio->write("anomaly detection complete.\n");
    }
};
class Display : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Display(DefaultIO *dio) : Command(dio, "display results")
    {}

    void execute(MutualInfo *pInfo) override
    {

        for (auto &report: pInfo->ar)
        {
            dio->write(report.timeStep);
            dio->write("\t ");
            dio->write(report.description);
            dio->write("\n");
        }
        dio->write("Done.\n");
    }
};
class UploadAndAnalyze : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit UploadAndAnalyze(DefaultIO *dio) : Command(dio,
                                                        "upload anomalies and analyze results")
    {}

    void execute(MutualInfo *pInfo) override
    {
        // initiate to "false" to avoid errors in further calls to this commands
        for (auto &cr: pInfo->crVector) {
            cr.isFP = false;
        }
        string line = "";
        long num1 = 0, num2 = 0;
        float tpCount = 0, fpCount = 0, P = 0, N = pInfo->numOfRows;
        dio->write("Please upload your local anomalies file.\n");
        while ((line = dio->read()) != "done")
        {

            // we get line in format: "num1,num2"
            stringstream ss(line);
            vector<string> result;
            while (ss.good())
            {
                string substr;
                getline(ss, substr, ',');
                result.push_back(substr);
            }
            num1 = stol(result[ 0 ]);
            num2 = stol(result[ 1 ]);
            for (auto &cr: pInfo->crVector) {
                if(num2 >= cr.start && num1 <= cr.end) {
                    cr.isFP = true;
                    tpCount++;
                    break;
                }
            }
            // increment the counter for positives
            P++;
            // substract the rows that are passed to us from total rows of timeseries.
            N -= (num2 - num1 + 1);
        }
        for (auto &cr: pInfo->crVector)
            if(!cr.isFP)
                fpCount++;
        dio->write("Upload complete.\n");
        dio->write("True Positive Rate: ");
        dio->write((int) (1000.0 * tpCount / P) / 1000.0f);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write((int) (1000.0 * fpCount / N) / 1000.0f);
        dio->write("\n");
    }
};
class Exit : public Command {
public:
    // initialize base class, this method called "Member Initializer List in C++".
    explicit Exit(DefaultIO *dio) : Command(dio, "exit")
    {}

    void execute(MutualInfo *pInfo) override
    {
    }
};
#endif /* COMMANDS_H_ */
