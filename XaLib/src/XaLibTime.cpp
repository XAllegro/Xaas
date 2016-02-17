#include <XaLibTime.h>
#include <XaLibBase.h>

XaLibTime::XaLibTime() {

};

string XaLibTime::GetDateTimeIsoComplete() {
 
	time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%X", &tstruct);

	//YYYY-MM-DDThh:mm:ssTZD
    return buf;
}

string XaLibTime::GetDateTimeMySql() {

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	//YYYY-MM-DDThh:mm:ssTZD
    return buf;
}

string XaLibTime::GetDateMySql() {

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
	//YYYY-MM-DDThh:mm:ssTZD
    return buf;
}

string XaLibTime::GetOtherDateMySql(int Days,int Months, int Years) {
	/* returns the date Days+Months+Years after today (thus |Days| before if Days<0 etc.) */

    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
	tstruct.tm_mday=tstruct.tm_mday+Days;
	tstruct.tm_mon =tstruct.tm_mon +Months;
	tstruct.tm_year=tstruct.tm_year+Years;
	mktime(&tstruct);

    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

int XaLibTime::GetDayOfYearFromDateTime(string StrDateTime) {
	// returns 1 for 1st January and so on
	// input datum date or datetime
	// input format: Iso or MySql
	// e.g.  2014-01-30 , 2014-01-30 12:00:00 , 2014-01-30T12:00:00	 return 30 (30th day of year)

	time_t datetime=time(0);
	struct tm tstruct;
	tstruct = *localtime ( &datetime );

	string StrYear=StrDateTime.substr(0,4);
	string StrMonth=StrDateTime.substr(5,2);
	string StrDay=StrDateTime.substr(8,2);
	
	int IntYear=XaLibBase::FromStringToInt(StrYear);
	int IntMonth=XaLibBase::FromStringToInt(StrMonth);
	int IntDay=XaLibBase::FromStringToInt(StrDay);

	tstruct.tm_year=IntYear-1900;
	tstruct.tm_mon =IntMonth-1;
	tstruct.tm_mday=IntDay;

	mktime(&tstruct);

	int IntDays=tstruct.tm_yday +1;

	return IntDays;

}

int XaLibTime::GetYearFromDateTime(string StrDateTime) {
	// input datum date or datetime
	// input format: Iso or MySql
	// e.g.  2014-01-30 , 2014-01-30 12:00:00 , 2014-01-30T12:00:00

	string StrYear=StrDateTime.substr(0,4);
	int IntYear=XaLibBase::FromStringToInt(StrYear);

	return IntYear;

}

int XaLibTime::GetDayOfWeekFromDayOfYear(int IntDayOfYear, int IntYear) {
	// returns day of week (0=Sunday, 6=Saturday) of the IntDayOfYear-th day of year IntYear

	time_t datetime=time(0);
	struct tm tstruct;
	tstruct = *localtime ( &datetime );

	tstruct.tm_year=IntYear-1900;
	tstruct.tm_mon=0;
	tstruct.tm_mday=IntDayOfYear;	// set as the IntDayOfYear-th day of January

	mktime(&tstruct);

	int dow=tstruct.tm_wday;

	return dow;

}

void XaLibTime::PrintDateTime(){
    
    time_t now = time(0);
    char* dt = ctime(&now);
    cout <<dt<< endl;
}

void XaLibTime::TimeOutSeconds(int seconds){

            clock_t temp;
            temp = clock () + seconds * CLOCKS_PER_SEC ;
            while (clock() < temp) { }
}


string XaLibTime::DateStringFromStruct(vector<string> DateStruct,string DateFormat) {

	string StrDate;

	string StrYear =DateStruct[0];
	string StrMonth=DateStruct[1];
	string StrDay  =DateStruct[2];

	if (CheckDateValidityFromStrings(StrYear,StrMonth,StrDay)) {

		if (DateFormat=="YYYY-mm-dd") {
			StrDate=StrYear+"-"+StrMonth+"-"+StrDay;
		} else {
			// invalid format
			// LOG
		}

	} else {
		StrDate="0";
		//invalid input date
		// LOG
	}

	return StrDate;
}


bool XaLibTime::CheckDateValidityFromStrings(string StrYear, string StrMonth, string StrDay) {
	// controlla la validita di una data yyyy mm dd
	// anno compreso tra il 1901 e il 2099	

	bool Check=false;

	int IntYear=XaLibBase::FromStringToInt(StrYear);
	int IntMonth=XaLibBase::FromStringToInt(StrMonth);
	int IntDay=XaLibBase::FromStringToInt(StrDay);

	if (StrYear.size()==4 and StrMonth.size()==2 and StrDay.size()==2 and IntMonth>0 and IntDay>0) {
		if(IntYear<2100 and IntYear>1900) {
			if (IntMonth<13) {
				if (IntMonth==2){
						if (IntYear % 4==0 and IntDay<30) {Check=true;};
						if (IntYear % 4!=0 and IntDay<29) {Check=true;};
				} else if (IntMonth==4 or IntMonth==6 or IntMonth==9 or IntMonth==11) {
					if (IntDay<31) {Check=true;};
				} else {
					if (IntDay<32) {Check=true;}
				}
			} else {
				// invalid month
			}
		} else {
			// year out of bounds
		}
	} else {
		//invalid input date format
		// LOG
	}

	return Check;
}

string XaLibTime::LastDateOfMonth(string StrYear,string StrMonth) {

	string StrDate;

	string StrDay;
	
	if (StrMonth=="02") {
		int IntYear=XaLibBase::FromStringToInt(StrYear);
		if (IntYear % 4==0) {StrDay="29";};
		if (IntYear % 4!=0) {StrDay="28";};
	} else if (StrMonth=="11" or StrMonth=="04" or StrMonth=="06" or StrMonth=="09") {
		StrDay="30";
	} else {
		StrDay="31";
	}
	
	StrDate=StrYear+"-"+StrMonth+"-"+StrDay;
	
	return StrDate;
}


XaLibTime::~XaLibTime() {
};
