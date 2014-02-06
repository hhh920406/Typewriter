package com.calc;

import java.util.ArrayList;
public class Stack
{
	private ArrayList<Character> data=new ArrayList<Character>();
	private int index=0;

	public char pop()
	{
		char value='0';
		if(!isEmpty())
			value=data.remove(index-1);
		index-=1;
		return value;
	}

	public void push(char elem)
	{
		data.add(index, elem);
		index+=1;
	}

	public boolean isEmpty()
	{
		return data.size()==0;
	}

	public void clear()
	{
		data.clear();
		index=0;
	}

	public boolean contains(char elem)
	{
		return data.contains(elem);
	}
}
