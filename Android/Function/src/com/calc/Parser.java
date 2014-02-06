package com.calc;

import java.util.HashMap;
import java.lang.reflect.Method;

public class Parser
{
	//标识符的类型
	private static final int NONE=0;//空标识
	private static final int DELM=1;//运算符
	private static final int VAR=2;//变量
	private static final int NUM=3;//数字
  	private static final int FUNC=4;//函数
  
  	//表达式错误类型
  	private static final int SYNTAX=0;//语法错误
  	private static final int BRACE=1;//括号不匹配
  	private static final int NULLEXP=2;//空表达式
  	private static final int DIVBYZERO=3;//除数为零
  	private static final int VAR_UNDEFINED=4;//变量未定义
  	private static final int UNKNOWNFUNC=5;//不支持的函数
  	private static final int WRONGINVOKE=6;//错误的函数调用
  
  	String[] errs;
  
  	private static final String EOF="\0";
  
  	private String tok;
  	private String exp;
  	private int expIdx;
  	private int tokType;
  
  	private HashMap<String,Double> vars=
  	         	new HashMap<String,Double>();
  
  	public static final String PI=String.valueOf(Math.PI);
  	public static final String E=String.valueOf(Math.E); 
  	public Parser()
  	{
  		vars.put("PI", Math.PI);
  		vars.put("E",Math.E);
  	}

  	private void handleErr(int errIdx) throws ParseException
  	{
  		if(errs==null)
  			errs=new String[]{"语法错误","括号不匹配","表达式为空","除数为零",
  		                	"变量未定义","不支持的函数","错误的函数调用"};
  		throw new ParseException(errs[errIdx]+" 位置"+expIdx+":"+exp.substring(0, expIdx));
  	}

  	private Double findVar(String name) throws ParseException
  	{
  		if(!Character.isLetter(name.charAt(0)))
  			handleErr(SYNTAX);
  		return vars.get(name);
  	}

  	private void backIndex() 
  	{
  		if(EOF.equals(tok))
  			return ;
  		expIdx-=tok.length();
  	}

  	private boolean isDelm(char c)
  	{
  		return "+-*/%()=;".indexOf(c)>-1;
  	}

  	private boolean isOperator(char c)
  	{
  		return "+-*/%".indexOf(c)>-1;
  	}

  	private boolean moreVars()
  	{
  		return exp.indexOf('=',expIdx)>-1;
  	}

  	private void skipSem() throws ParseException
  	{
  		if(";".equals(tok))
  			nextToken();
  	}
  
  	private void nextToken() throws ParseException
  	{
  		tokType=NONE;
  		tok="";
  		if(expIdx==exp.length())
  		{
  			tok=EOF;
  			return;
  		}
  		while(expIdx<exp.length()&&
  				Character.isWhitespace(exp.charAt(expIdx)))
  			expIdx++;
  		if(expIdx==exp.length())
  		{
  			tok=EOF;
  			return ;
  		}
  		if(isDelm(exp.charAt(expIdx)))
  		{
  			tok+=exp.charAt(expIdx++);
  			tokType=DELM;
  		}
  		else if(Character.isLetter(exp.charAt(expIdx)))
  			checkBrace();
  		else if(Character.isDigit(exp.charAt(expIdx)))
  		{
  			while(!isDelm(exp.charAt(expIdx)))
  			{
  				tok+=exp.charAt(expIdx++);
  				if(expIdx>=exp.length())
  					break;
  			}
  			tokType=NUM;
  		}
  		else
  		{
  			tok=EOF;
  		}
  	}

  	private void checkBrace() throws ParseException
  	{
  		Stack braces=new Stack();
  		char curChar;
  		while(expIdx<exp.length()&&(!isOperator(exp.charAt(expIdx))||!braces.isEmpty()))
  		{
  			curChar=exp.charAt(expIdx);
  			if(curChar=='(')
  				braces.push(curChar);
  			else if(curChar==')')
  			{
  				if(braces.isEmpty())
  					break;
  				braces.pop();
  			}
  			if(curChar=='='||curChar==';')
  				break;
  			tok+=curChar;
  			expIdx++;
  		}
  		if(!braces.isEmpty())
  			handleErr(BRACE);
  		if(tok.indexOf('(')>-1)
  			tokType=FUNC;
  		else
  			tokType=VAR;
  	}

  	private String getFuncName(String func)
  	{
  		return func.substring(0,func.indexOf('('));
  	}

  	private String[] getParamsStr(String func)
  	{
  		int braceIndex=func.indexOf('(');
  		String inner=func.substring(braceIndex+1,func.length()-1);
  		return inner.split(",");
  	}

  	private double atom() throws ParseException
  	{
  		double value=0;
  		if(tokType==NUM)
  		{
  			try
  			{
  				value=Double.parseDouble(tok);
  			}
  			catch(NumberFormatException ex)
  			{
  				handleErr(SYNTAX);
  			}
  			nextToken();
  			skipSem();
  		}
  		else if(tokType==VAR)
  		{
  			try
  			{
  				value=findVar(tok);
  			}
  			catch(NullPointerException e)
  			{
  				handleErr(VAR_UNDEFINED);
  			}
  			nextToken();
  			skipSem();
  		}
  		else if(tokType==FUNC)
  		{
  			value=funcValue();
  			nextToken();
  		}
  		else
  			handleErr(SYNTAX);
  		return value;		
  	}

  	private double funcValue()throws ParseException
  	{
  		String name=getFuncName(tok);
  		String[] paramStr=getParamsStr(tok);
  		double param1,param2;
  		Double value=null;
  		Parser p1=new Parser(),p2=new Parser();
  		p1.vars=this.vars;
  		p2.vars=this.vars;
  		Class[] cls=new Class[paramStr.length];
  		for(int i=0;i<cls.length;i++)
  			cls[i]=double.class;
  		try
  		{
  			Method m=Math.class.getMethod(name, cls);
  			if(paramStr.length==2)
			{
				param1=p1.eval(paramStr[0]);
				param2=p2.eval(paramStr[1]);
				value=(Double)m.invoke(null,param1,param2);
			}
			else if(paramStr.length==1)
			{
				param1=p1.eval(paramStr[0]);
				value=(Double)m.invoke(null, param1);
			}
		} 
  		catch (SecurityException e)
		{
			e.printStackTrace();
		} 
  		catch (NoSuchMethodException e)
		{
			handleErr(UNKNOWNFUNC);
		}
		catch(IllegalArgumentException e)
		{
			handleErr(WRONGINVOKE);
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return value;
  	}

  	private double evalSingle() throws ParseException
  	{
  		double value;
  		String op="";
	  	if(tokType==DELM&&(tok.equals("+")||tok.equals("-")))
	  	{	
	  		op=tok;
	  		nextToken();
	  	}
	  	value=evalSyn();
	  	if(op.equals("-"))
	  		value=-value;
	  	return value;
  	}

  	private double evalMD() throws ParseException
  	{
	  	double value,partValue;
	  	char op;
	  	value=evalSingle();
	  	while((op=tok.charAt(0))=='*'||op=='/'||op=='%')
	  	{
	  		nextToken();
	  		partValue=evalSingle();
	  		if(op=='*')
	  			value=value*partValue;
	  		else if(op=='/')
	  		{
	  			if(partValue==0)
	  				handleErr(DIVBYZERO);
	  			value=value/partValue;
	  		}
	  		else if(op=='%')
	  		{
	  			if(partValue==0)
	  				handleErr(DIVBYZERO);
	  			value=value%partValue;
	  		}
	  	}
	  	return value; 
  	}

  	private double evalAS() throws ParseException
  	{
	  	char op;
	  	double value,partValue;
	  	value=evalMD();
	  	while((op=tok.charAt(0))=='+'||op=='-')
	  	{
	  		nextToken();
	  		partValue=evalMD();
	  		if(op=='+')
	  			value=value+partValue;
	  		else if(op=='-')
	  			value=value-partValue;
	  	}
	  	return value;
  	}

  	private double evalSyn() throws ParseException
  	{ 
	  	double value;
	  	if(tok.equals("("))
	  	{
	  		nextToken();
	  		value=evalAS();
	  		if(!tok.equals(")"))
	  			handleErr(BRACE);
	  		nextToken();
	  		skipSem();
	  	}
	  	else
	  		value=atom();
	  	return value;
  	}
  
  	private double evalBegin() throws ParseException
  	{
	  	double value;
	  	int lastTokType;
	  	String lastToken;
	  	while(tokType==VAR&&moreVars())
	  	{
	  		lastToken=tok;
	  		lastTokType=tokType;
	  		nextToken();
	  		if(!"=".equals(tok))
	  		{
	  		 if(findVar(lastToken)==null)
	  	  		handleErr(VAR_UNDEFINED);
	  			backIndex();
	  			tok=lastToken;
	  			tokType=lastTokType;
	  		}
	  		else{
	  			nextToken();
	  			value=evalAS();
	  			vars.put(lastToken, value);
	  		}
	  	}
	  	return evalAS();
  	}
  
  	public double eval(String expStr) throws ParseException
  	{
	  	double result;
	  	exp=expStr;
	  	expIdx=0;
	  	nextToken();
	  	if(tok.equals(EOF))
	  		handleErr(NULLEXP);
	  	result=evalBegin();
	  	if(!tok.equals(EOF))
	  		handleErr(SYNTAX);
	  	return result;
  	}
 
  	public double getAnswer(String expStr, double x)throws ParseException
  	{
  		String result = "";
  		for(int i=0;i<expStr.length();++i)
  		{
  			if(expStr.charAt(i)=='X')
  			{
  				result += x;
  			}
  			else
  			{
  				result += expStr.charAt(i);
  			}
  		}
  		return getAnswer(result);
  	}
  	
  	public double getAnswer(String expStr, double x, double y)throws ParseException
  	{
  		String result = "";
  		for(int i=0;i<expStr.length();++i)
  		{
  			if(expStr.charAt(i)=='X')
  			{
  				result += x;
  			}
  			else if(expStr.charAt(i)=='Y')
  			{
  				result += y;
  			}
  			else
  			{
  				result += expStr.charAt(i);
  			}
  		}
  		return getAnswer(result);
  	}
  
  	public double getAnswer(String expStr) throws ParseException
  	{
	    Parser ps=new Parser();
	    if(expStr==null||expStr.equals("")) return 0;
	    return ps.eval(expStr);
  	}
}
