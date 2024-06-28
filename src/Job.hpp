#pragma once
#include <set>
#include <string>
using namespace std;
namespace cron {
    constexpr const int MIN_MINUTES = 0;
    constexpr const int MIN_HOURS = 0;
    constexpr const int MIN_DAYS_OF_MONTH = 1;
    constexpr const int MIN_MONTH = 1;
    constexpr const int MIN_DAYS_OF_WEEK = 0;


    constexpr const int MAX_MINUTES = 59;
    constexpr const int MAX_HOURS = 23;
    constexpr const int MAX_DAYS_OF_MONTH = 31;
    constexpr const int MAX_MONTH = 12;
    constexpr const int MAX_DAYS_OF_WEEK = 6;

    class Job {

        public:
            void  SetMinutes(const set<int>&);
            void  SeHours(const set<int>&);
            void  SetDaysOfMonths(const set<int>&);
            void  SetMonths(const set<int>&);
            void  SetDaysOfWeek(const set<int>&);
            void  SetCommand(const string&);
            bool SpawnProcess(int, int, int ,int, int);

        private:
            set<int> mMinutes; // 0-59
            set<int> mHours; // 0-23
            set<int> mDaysOfMonth; // 1-31
            set<int> mMonths; // 1-12
            set<int> mDaysOfWeek; // 0-6
            string mCommand;
    };

}
