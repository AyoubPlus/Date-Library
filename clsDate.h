#pragma once
#pragma warning(disable : 4996)

#include<iostream>
#include<vector>
#include<ctime>
using namespace std;

#include"../UsefulLib/usefulLib.h"

class clsDate
{
private:

	struct stTime
	{
	public:
		short Hour;
		short Minute;
		short Second;
	};

	stTime _Time;
	short _Day;
	short _Month;
	short _Year;

	static stTime _FullTime(short Hour, short Minute, short Second)
	{
		stTime Time;
		Time.Hour = Hour;
		Time.Minute = Minute;
		Time.Second = Second;
		return Time;
	}

public:

	void SetStrTime(string Time)
	{
		vector<string> vTime = UsefullLib::SplitString(Time, ":");
		_Time.Hour = stoi(vTime[0]);
		_Time.Minute = stoi(vTime[1]);
		_Time.Second = stoi(vTime[2]);
	}

	static clsDate KnowDate()
	{
		clsDate Date;
		time_t t = time(NULL);
		tm* d = localtime(&t);

		Date.$Time = _FullTime(d->tm_hour, d->tm_min, d->tm_sec);
		Date.$Day = d->tm_mday;
		Date.$Month = d->tm_mon + 1;
		Date.$Year = d->tm_year + 1900;

		return Date;
	}

	string StrDate(string Format = "dd/mm/yy")
	{
		string Str = Format;

		UsefullLib::ReplaceStrInText(Str, "dd", to_string(this->$Day));
		UsefullLib::ReplaceStrInText(Str, "mm", to_string(this->$Month));
		UsefullLib::ReplaceStrInText(Str, "yy", to_string(this->$Year));
		UsefullLib::ReplaceStrInText(Str, "hh", to_string(this->$Hour));
		UsefullLib::ReplaceStrInText(Str, "nn", to_string(this->$Minute));
		UsefullLib::ReplaceStrInText(Str, "ss", to_string(this->$Second));

		return Str;
	}

	static bool IsTime1BeforeTime2(stTime Time1, stTime Time2)
	{
		return (Time1.Hour < Time2.Hour) ? true : (Time1.Hour == Time2.Hour) ?
			(Time1.Minute < Time2.Minute) ? true : (Time1.Minute == Time2.Minute) ?
			(Time1.Second < Time2.Second) ? true : false : false : false;
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : (Date1._Year == Date2._Year) ?
			(Date1._Month < Date2._Month) ? true : (Date1._Month == Date2._Month) ?
			(Date1._Day < Date2._Day) ? true : (Date1._Day == Date2._Day) ?
			IsTime1BeforeTime2(Date1._Time, Date2.$Time) ?
			true : false : false : false : false;
	}

	void SetDate(short Year, short Month, short Day, short Hour = 0, short Minute = 0, short Second = 0)
	{
		this->$Year = Year;
		this->$Month = Month;
		this->$Day = Day;
		this->$Hour = Hour;
		this->$Minute = Minute;
		this->$Second = Second;
	}

	static bool IsALeapYear(short Year)
	{
		return (Year % 400 == 0) ? true : (Year % 4 == 0 && Year % 100 != 0) ? true : false;
	}

	static short NumberOfDaysInAMonth(short Year, short Month)
	{
		short NumberOfDayInMonth[12] = { 31,28 + (short)IsALeapYear(Year),31,30,31,30,31,31,30,31,30,31 };

		return NumberOfDayInMonth[Month - 1];
	}

	void AddYears(int Years)
	{
		$Year += Years;
	}

	void AddMonths(int Months)
	{
		for (short i = 0; i < Months; i++)
		{
			if ($Month < 12)
			{
				$Month++;
			}
			else
			{
				$Month = 1;
				$Year++;
			}
		}
	}

	void AddDays(int Days)
	{
		for (short i = 0; i < Days; i++)
		{
			if ($Day < NumberOfDaysInAMonth($Year, $Month))
			{
				$Day++;
			}
			else
			{
				$Day = 1;
				AddMonths(1);
			}
		}
	}

	void AddHours(int Hours)
	{
		for (short i = 0; i < Hours; i++)
		{
			if ($Hour < 23)
			{
				$Hour++;
			}
			else
			{
				$Hour = 0;
				AddDays(1);
			}
		}
	}

	void AddMinutes(int Minutes)
	{
		for (short i = 0; i < Minutes; i++)
		{
			if ($Minute < 59)
			{
				$Minute++;
			}
			else
			{
				$Minute = 0;
				AddHours(1);
			}
		}
	}

	void AddSeconds(int Seconds)
	{
		for (short i = 0; i < Seconds; i++)
		{
			if ($Second < 59)
			{
				$Second++;
			}
			else
			{
				$Second = 0;
				AddMinutes(1);
			}
		}
	}

	void AddDate(clsDate Date)
	{
		AddSeconds(Date.$Second);
		AddMinutes(Date.$Minute);
		AddHours(Date.$Hour);
		AddDays(Date.$Day);
		AddMonths(Date.$Month);
		AddYears(Date.$Year);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return IsDate1BeforeDate2(Date2, Date1);
	}

	short NumberOfDaysInAMonth()
	{
		return NumberOfDaysInAMonth(_Year, _Month);
	}

	bool IsDateAfterKnowDate()
	{
		return IsDate1AfterDate2(*this, KnowDate());
	}



	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec (property(get = GetDay, put = SetDay))short $Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	__declspec (property(get = GetMonth, put = SetMonth))short $Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}
	__declspec (property(get = GetYear, put = SetYear))short $Year;

	void SetHour(short Hour)
	{
		_Time.Hour = Hour;
	}
	short GetHour()
	{
		return _Time.Hour;
	}
	__declspec (property(get = GetHour, put = SetHour))short $Hour;

	void SetMinute(short Minute)
	{
		_Time.Minute = Minute;
	}
	short GetMinute()
	{
		return _Time.Minute;
	}
	__declspec (property(get = GetMinute, put = SetMinute))short $Minute;

	void SetSecond(short Second)
	{
		_Time.Second = Second;
	}
	short GetSecond()
	{
		return _Time.Second;
	}
	__declspec (property(get = GetSecond, put = SetSecond))short $Second;

	void SetTime(stTime Time)
	{
		_Time = Time;
	}
	stTime GetTime()
	{
		return _Time;
	}
	__declspec (property(get = GetTime, put = SetTime))stTime $Time;
};

