package com.calc;

public class ParseException extends Exception
{
	private static final long serialVersionUID = 1L;
	private String msg;
	public ParseException(String msg)
	{
		this.msg=msg;
	}
  
	public String toString()
	{
		return msg;
	}
}
