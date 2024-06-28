#include "Job.hpp"
#include <thread>
#include <cstdlib>
#include <iostream>

using namespace std;
namespace cron {

    void threadFunc(string command) {
        if( 0 != system(command.c_str())){
            cerr << "failed to execute: " << command.c_str() <<endl;

        }
    }
    void Job:: SetMinutes(const set<int>& minList){
        mMinutes = minList;
    }
    void Job:: SeHours(const set<int>& hourList){
        mHours = hourList;
    }
    void Job:: SetDaysOfMonths(const set<int>& dayList){
        mDaysOfMonth = dayList;
    }
    void Job:: SetMonths(const set<int>& monList){
        mMonths = monList;
    }
    void Job:: SetDaysOfWeek(const set<int>& dayList ){
        mDaysOfWeek = dayList;
    }
    void Job:: SetCommand(const string& command){
        mCommand = command;
    }
    bool Job:: SpawnProcess(int min, int hr, int dayOfMon,int mon, int dayOfWeek){
        if( mMinutes.find(min) != mMinutes.end()
                && mHours.find(hr) != mHours.end()
                && mDaysOfMonth.find(dayOfMon) != mDaysOfMonth.end()
                && mMonths.find(mon) != mMonths.end()
                && mDaysOfWeek.find(dayOfWeek) != mDaysOfWeek.end() ) {

            thread(threadFunc,mCommand).detach();
            return true;
        }

        return false;
    }


}
