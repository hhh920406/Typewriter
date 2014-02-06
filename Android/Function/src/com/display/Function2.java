package com.display;

import com.calc.ParseException;
import com.calc.Parser;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class Function2 extends Activity
{
	static int width;
	static int height;
	private boolean inDisplay = false;
	private String input1;
	private String input2;
	private String input3;
	private String input4;
	private EditText editText1;
	private EditText editText2;
	private EditText downEdit;
	private EditText upEdit;
	
	@Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.function2);
        initial();
    }
	
	public void initial()
	{
		editText1 = (EditText) findViewById(R.id.editText1);
		editText2 = (EditText) findViewById(R.id.editText2);
        Button clearButton = (Button) findViewById(R.id.clearButton);
        Button makeButton = (Button) findViewById(R.id.makeButton);
        Button backButton = (Button) findViewById(R.id.backButton);
        downEdit = (EditText) findViewById(R.id.downNumber);
        upEdit = (EditText) findViewById(R.id.upNumber);
        
        WindowManager windowManager = getWindowManager();
		Display display = windowManager.getDefaultDisplay();
		width = display.getWidth();
		height = display.getHeight();
        
        clearButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		editText1.setText("");
        		editText2.setText("");
        	}
        });
        
        makeButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Parser parser = new Parser();
        		double x[] = new double[300];
        		double y[] = new double[300];
        		double leftX = (double)Integer.parseInt( downEdit.getText().toString() );
        		double rightX = (double)Integer.parseInt( upEdit.getText().toString() );
        		if(leftX > rightX)
        		{
        			double temp = leftX;
       				leftX = rightX;
       				rightX = temp;
        		}
        		double space = (rightX - leftX) / 299;
        		boolean showToast = false;
        		for(int i=0;i<300;i++)
        		{
        			try
        			{
        				x[i] = parser.getAnswer(editText1.getText().toString(), leftX + space * i);
        				y[i] = parser.getAnswer(editText2.getText().toString(), leftX + space * i);
        			}
        			catch (ParseException e)
        			{
        				if(!showToast)
        				{
        					DisplayToast(getText(R.string.funcerror).toString());
        					showToast = true;
        				}
        			}
        		}
        		displayFunction(x, y);
        	}
        });
        
        backButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Intent intent = new Intent();
        		intent.setClass(Function2.this, SelectMain.class);
        		startActivity(intent);
        		Function2.this.finish();
        	}
        });
	}
	
	public void displayFunction(double x[], double y[])
	{
		DisplayView display = new DisplayView(this);
		display.getValue(x, y);
		display.setMode(2);
		this.setContentView(display);
		input1 = editText1.getText().toString();
		input2 = editText2.getText().toString();
		input3 = upEdit.getText().toString();
		input4 = downEdit.getText().toString();
		inDisplay = true;
	}
	
	public boolean onTouchEvent(MotionEvent event) 
	{
		if(inDisplay)
		{
			this.setContentView(R.layout.function2);
			initial();
			editText1.setText(input1);
			editText2.setText(input2);
			downEdit.setText(input3);
			upEdit.setText(input4);
			inDisplay = false;
		}
		return super.onTouchEvent(event);
	}
	
	public void DisplayToast(String str)
	{
		Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
	}
}
