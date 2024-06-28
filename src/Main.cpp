#include "ConfigParser.hpp"
#include <ctime>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){

    cron::ConfigParser cParser("nt_cron.conf");
    vector<cron::Job> jobList;
    time_t triggerTime;
    struct tm triggerTm;

    time(&triggerTime);
    triggerTm = *(localtime(&triggerTime));
    if ( false == cParser.Parse(jobList) ){

        cerr << "Config file is not proper" <<endl;
        exit(-1);
    }

    while(1) {
        for(auto it = jobList.begin(); it != jobList.end(); ++it) {

            (*it).SpawnProcess(triggerTm.tm_min, triggerTm.tm_hour, triggerTm.tm_mday, triggerTm.tm_mon + 1, triggerTm.tm_wday);

        }
        time_t currTime;
        time(&currTime);
        int sleep_time = 60 - (int)difftime(currTime,triggerTime);

        if (sleep_time >0){
            sleep(sleep_time);
        }
        time(&triggerTime);
        triggerTm = *(localtime(&triggerTime));
    }

}
