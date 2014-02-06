package com.display;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class AboutUs extends Activity
{
	@Override
    public void onCreate(Bundle savedInstanceState) 
    {
		super.onCreate(savedInstanceState);
        setContentView(R.layout.about);
        
        Button backButton = (Button) findViewById(R.id.backButton);
        backButton.setOnClickListener(new Button.OnClickListener()
        {
        	public void onClick(View v)
        	{
        		Intent intent = new Intent();
        		intent.setClass(AboutUs.this, SelectMain.class);
        		startActivity(intent);
        		AboutUs.this.finish();
        	}
        });
    }
}
