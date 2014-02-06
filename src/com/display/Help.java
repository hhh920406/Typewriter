package com.display;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Help extends Activity
{
	@Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.help);
        
        Button backButton = (Button) findViewById(R.id.backButton);
        backButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Intent intent = new Intent();
        		intent.setClass(Help.this, SelectMain.class);
        		startActivity(intent);
        		Help.this.finish();
        	}
        });
    }
}
