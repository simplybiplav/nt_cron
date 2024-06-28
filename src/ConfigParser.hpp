#pragma once
#include <vector>
#include <string>
#include "Job.hpp"
using namespace std;
namespace cron {
    class ConfigParser {

        private:
            string mFileName;
            bool ParseJob(const string&, Job&);
            int StoiRange(const string&, int, int); 
            std::vector<std::string> Split(const std::string &, char);
            bool PopulateValues(const string&, set<int>&,int, int);
        public:
            bool Parse(vector<Job>& jobList);
            ConfigParser(string);


    };
}
