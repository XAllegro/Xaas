#ifndef XALIBTIME_H
#define XALIBTIME_H

#include <XaLibBase.h>

class XaLibTime : protected XaLibBase {

	private:

	protected:

	public:

		XaLibTime();
		~XaLibTime();
		
		static string GetDateTimeIsoComplete();
        static string GetDateTimeMySql();
        static string GetDateMySql();
		string GetOtherDateMySql(int Days,int Months, int Years);
        int GetDayOfYearFromDateTime(string StrDateTime);
        int GetYearFromDateTime(string StrDateTime);
        int GetDayOfWeekFromDayOfYear(int IntDayOfYear, int IntYear);
        void PrintDateTime();
        void TimeOutSeconds(int seconds);
        bool CheckDateValidityFromStrings(string StrYear,string StrMonth,string StrDay);
        string DateStringFromStruct(vector<string> DateStruct,string DateFormat);
        string LastDateOfMonth(string StrYear,string StrMonth);
};
#endif