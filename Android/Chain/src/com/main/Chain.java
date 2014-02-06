package com.main;

import android.app.Activity;
import android.os.Bundle;
import android.view.Display;
import android.view.Window;
import android.view.WindowManager;

public class Chain extends Activity 
{
	public ChainView view;
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        this.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        view = new ChainView(this);
        this.setContentView(view);
        WindowManager windowManager = getWindowManager();
		Display display = windowManager.getDefaultDisplay();
		int width = display.getWidth();
		int height = display.getHeight();
		view.setWindowSize(width, height);
		view.start();
    }
}