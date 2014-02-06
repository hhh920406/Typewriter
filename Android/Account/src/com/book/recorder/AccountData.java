package com.book.recorder;

public class AccountData {
	public long id;
	public int year;
	public int month;
	public int day;
	public float amount;
	public boolean isIncome;
	public String description;
	
	public boolean isBigger(AccountData data) {
		if (year == data.year)
		{
			if (month == data.month)
			{
				if (day == data.day)
				{
					return false;
				}
				return day > data.day;
			}
			return month > data.month;
		}
		return year > data.year;
	}
}
