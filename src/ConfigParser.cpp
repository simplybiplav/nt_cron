#include "ConfigParser.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

namespace cron {
    ConfigParser::ConfigParser(string filename) {
        mFileName = filename;
    }

    std::vector<std::string> ConfigParser::Split(const std::string &s, char delim) {
        std::vector<std::string> returnList;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            if (item.length() > 0) {
                returnList.push_back(item);
            }
        }
        return returnList;
    }

    int ConfigParser::StoiRange(const string& str, int minValue, int maxValue) {

        int val = 0;
        try {
             val = stoi(str);
            if (val < minValue || val > maxValue){
                cerr << "invalid value:" << str <<endl;
                throw std::invalid_argument("invalid range");
            }
        }
        catch(...){
                cerr << "invalid value:" << str <<endl;
                throw std::invalid_argument("invalid range");
        }
        return val;

    }

    bool ConfigParser::PopulateValues(const string& str, set<int>& returnSet,int minValue, int maxValue) {

        if (str.compare("*")==0) {
            for(int val = minValue; val <= maxValue; ++val){
                returnSet.insert(val);
            }
            return true;
        }

        if (str.find('/') != string::npos){
            vector<string> periodSplit = Split(str, '/');
            if (periodSplit.size() != 2 ){
                return false;
            }
            int incVal = 0;
            if(periodSplit[0].compare("*") == 0 ) {
                try{
                    incVal = StoiRange(periodSplit[1],minValue == 0? minValue+1 : minValue,maxValue);
                }
                catch(const exception& e)
                {
                    cerr << "Execption Occured::" << e.what() <<endl;
                    return false;
                }
                for(int val = minValue; val <= maxValue; val+= incVal){
                    returnSet.insert(val);
                }
                return true;
            }
            vector<string> intervalSplit = Split(str, '-');
            if (intervalSplit.size() != 2 ){
                return false;
            }
            int startVal = minValue;
            int endVal = maxValue;
            try{
                startVal = StoiRange(intervalSplit[0],minValue,maxValue);
                endVal = StoiRange(intervalSplit[1],minValue,maxValue);
                incVal = StoiRange(periodSplit[1],minValue == 0? minValue+1 : minValue,maxValue);
            }
            catch(const exception& e)
            {
                cerr << "Execption Occured::" << e.what() <<endl;
                return false;
            }
            for(int val = startVal; val <= endVal; val+= incVal){
                returnSet.insert(val);
            }
            return true;
        }
        vector<string> listOfNums = Split(str, ',');
        for( vector<string>::iterator it = listOfNums.begin() ; it != listOfNums.end() ; ++it ) {
            vector<string> numRange = Split(*it, '-');
            if (numRange.size() > 2 ){
                return false;
            }
            if (numRange.size() == 1) {
                try{
                    int val = StoiRange(numRange[0],minValue,maxValue);
                    returnSet.insert(val);
                }
                catch(const exception& e)
                {
                    cerr << "Execption Occured::" << e.what() <<endl;
                    return false;
                }
            }
            if (numRange.size() == 2) {
                try{
                    int startVal = StoiRange(numRange[0],minValue,maxValue);
                    int endVal = StoiRange(numRange[1],minValue,maxValue);
                    if (startVal > endVal) {
                        throw std::invalid_argument("invalid range");
                    }
                    for(int val = startVal; val <= endVal; ++val){
                        returnSet.insert(val);
                    }
                }
                catch(const exception& e)
                {
                    cerr << "Execption Occured::" << e.what() <<endl;
                    return false;
                }
            }
        }

        if(returnSet.size() > 0) {
            return true;
        }
        return false;


    }

    bool ConfigParser::ParseJob(const string& line, cron::Job& job) {
        string re =  "[[:space:]]*([^[:space:]]+)[[:space:]]+([^[:space:]]+)[[:space:]]+([^[:space:]]+)[[:space:]]+([^[:space:]]+)[[:space:]]+([^[:space:]]+)[[:space:]]+(.*)";
        std::smatch m;
        std::regex_search(line, m, std::regex(re));
        if (!m.empty() && m.size()==7) {
            set<int> minuteSet, hoursSet, daysOfMonthSet, monthSet,daysOfWeekSet;
            if ( PopulateValues(string(m[1]),minuteSet,MIN_MINUTES, MAX_MINUTES)
                    && PopulateValues(string(m[2]),hoursSet,MIN_HOURS, MAX_HOURS)
                    && PopulateValues(string(m[3]),daysOfMonthSet,MIN_DAYS_OF_MONTH, MAX_DAYS_OF_MONTH)
                    && PopulateValues(string(m[4]),monthSet,MIN_MONTH, MAX_MONTH)
                    && PopulateValues(string(m[5]),daysOfWeekSet,MIN_DAYS_OF_WEEK, MAX_DAYS_OF_WEEK)
               ) {

                job.SetMinutes(minuteSet);
                job.SeHours(hoursSet);
                job.SetDaysOfMonths(daysOfMonthSet);
                job.SetMonths(monthSet);
                job.SetDaysOfWeek(daysOfWeekSet);
                job.SetCommand(string(m[6]));
                return true;
            }
        }

        cerr << "invalid config format: " << line << endl;
        return false;
    }

    bool ConfigParser::Parse(vector<Job>& jobList) {
        fstream fs;
        bool ret = false;
        try {
            fs.open (mFileName.c_str(), fstream::in);
            if (fs.is_open()){
                string line;
                while (getline(fs,line)){
                    cron::Job job;
                    if (ParseJob(line,job)){
                        jobList.push_back(job);
                    }
                }
                ret = true;
            }

        }
        catch(const exception& e)
        {
            cerr << "Execption Occured::" << e.what() <<endl;
        }
        fs.close();

        return ret;
    }
}
