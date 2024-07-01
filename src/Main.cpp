#include "ConfigParser.hpp"
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <getopt.h>

using namespace std;

int main(int argc, char **argv){

    int c;
    bool daemon = true;
    string configFile = "/etc/nt_cron.conf"; //default config file
    while (1) {

        c = getopt(argc, argv, "c:fh");
        if (c == -1)
            break;

        switch (c) {
            case 'c':
                if(NULL == optarg) {
                    cerr << " Invalid config param: Empty string" << endl;
                    exit(-1);
                }
                configFile = optarg;
                break;

            case 'f':
                daemon = false;
                break;

            case 'h':
                cout << "usage: \n config file: -c config_file_full_path \n foreground: -f" << endl;
                exit(EXIT_FAILURE);
                break;

            default:
                cout << "usage: \n config file: -c config_file_full_path \n foreground: -f" << endl;
                exit(EXIT_FAILURE);
        }
    }

    if(daemon) {

        pid_t pid;

        pid = fork();

        //if the fork fails, exit the program
        if (pid < 0) {
            exit(EXIT_FAILURE);
        }

        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }

        //Set a new session
        if (setsid() < 0) {
            exit(EXIT_FAILURE);
        }

        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }


    cron::ConfigParser cParser(configFile);
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
