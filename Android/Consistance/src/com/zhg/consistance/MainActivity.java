package com.zhg.consistance;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.DisplayMetrics;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity 
{
    public MainView view;
    
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        this.getWindow().requestFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        view = new MainView(this);
        this.setContentView(view);
        WindowManager windowManager = getWindowManager();
        DisplayMetrics displayMetrics = new DisplayMetrics();
        windowManager.getDefaultDisplay().getMetrics(displayMetrics);
        int width = displayMetrics.widthPixels;
        int height = displayMetrics.heightPixels;
        view.setWindowSize(width, height);
        load();
        view.setAct(this);
    }
    
    public void save() 
    {
		SharedPreferences shared = this.getSharedPreferences("Data", Context.MODE_PRIVATE);
		Editor edit = shared.edit();
		edit.putInt("ball", view.maxBallNum);
		edit.putLong("second", view.maxSeconds);
		edit.putLong("graze", view.maxGrazeScore);
		edit.putInt("t_ball", view.totalBallNum);
		edit.putLong("t_second", view.totalSeconds);
		edit.putLong("t_graze", view.totalGrazeScore);
		edit.commit();
    }
    
    public void load() 
    {
    	SharedPreferences shared = this.getSharedPreferences("Data", Context.MODE_PRIVATE);
    	view.maxBallNum = shared.getInt("ball", 0);
    	view.maxSeconds = shared.getLong("second", 0);
    	view.maxGrazeScore = shared.getLong("graze", 0);
    	view.totalBallNum = shared.getInt("t_ball", 0);
    	view.totalSeconds = shared.getLong("t_second", 0);
    	view.totalGrazeScore = shared.getLong("t_graze", 0);
    }
}
