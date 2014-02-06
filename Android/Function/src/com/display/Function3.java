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


public class Function3 extends Activity
{
	static int width;
	static int height;
	private boolean inDisplay = false;
	private String input1;
	private String input2;
	private String input3;
	private EditText editText;
	private EditText downEdit;
	private EditText upEdit;
	
	@Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.function3);
        initial();
    }
	
	public void initial()
	{
		editText = (EditText) findViewById(R.id.editText);
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
        		editText.setText("");
        	}
        });
        
        makeButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Parser parser = new Parser();
        		double x[] = new double[50];
        		double y[] = new double[50];
        		double z[][] = new double[50][50];
        		double leftX = (double)Integer.parseInt( downEdit.getText().toString() );
        		double rightX = (double)Integer.parseInt( upEdit.getText().toString() );
        		if(leftX > rightX)
        		{
        			double temp = leftX;
       				leftX = rightX;
       				rightX = temp;
        		}
        		double space = (rightX - leftX) / 49;
        		boolean showToast = false;
        		for(int i=0;i<50;i++)
        		{
        			for(int j=0;j<50;j++)
        			{
        				x[i] = leftX + space * i;
        				y[j] = leftX + space * j;
            			try
            			{
            				z[i][j] = parser.getAnswer(editText.getText().toString(), x[i], y[j]);
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
        		}
        		displayFunction(x, y, z);
        	}
        });
        
        backButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Intent intent = new Intent();
        		intent.setClass(Function3.this, SelectMain.class);
        		startActivity(intent);
        		Function3.this.finish();
        	}
        });
	}
	
	public void displayFunction(double x[], double y[], double z[][])
	{
		DisplayView display = new DisplayView(this);
		display.getValue(x, y, z);
		display.setMode(3);
		this.setContentView(display);
		input1 = editText.getText().toString();
		input2 = upEdit.getText().toString();
		input3 = downEdit.getText().toString();
		inDisplay = true;
	}
	
	public boolean onTouchEvent(MotionEvent event) 
	{
		if(inDisplay)
		{
			this.setContentView(R.layout.function3);
			initial();
			editText.setText(input1);
			downEdit.setText(input2);
			upEdit.setText(input3);
			inDisplay = false;
		}
		return super.onTouchEvent(event);
	}
	
	public void DisplayToast(String str)
	{
		Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
	}
}
