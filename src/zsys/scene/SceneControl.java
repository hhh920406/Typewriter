package zsys.scene;

import java.util.Timer;
import java.util.TimerTask;

import zsys.common.GameDataRecord;
import zsys.main.Main;
import android.content.Context;
import android.graphics.Canvas;
import android.view.MotionEvent;
import android.view.View;

public class SceneControl extends View
{
	Main main;
	
	public static final int SCENE_NULL			= 0;
	public static final int SCENE_LONGTERM		= 1;
	public static final int SCENE_QUIT 			= 2;
	
	public static final int SCENE_MENU 			= 3;
	public static final int SCENE_GAME_STAGE 		= 4;
	public static final int SCENE_GAME_TIME 		= 5;
	public static final int SCENE_GAME_INFINTIY 	= 6;
	public static final int SCENE_ACHIEVEMENT 	= 7;
	public static final int SCENE_HELP 			= 8;
	public static final int SCENE_ABOUT 			= 9;
	
	private SceneInterface shortTermScene;
	private SceneInterface longTermScene;
	private boolean showLongTermScene;
	private int currentScene;
	
	private Timer timer;
	
	public SceneControl(Context context) 
	{
		super(context);
		this.shortTermScene = null;
		this.longTermScene = new MenuScene();
		this.showLongTermScene = true;
		this.currentScene = SCENE_MENU;
		this.timer = new Timer();
		this.timer.scheduleAtFixedRate(new Task(this), 0, 33);
	}
	
	public void sendMain(Main main)
	{
		this.main = main;
	}
	
	public void refresh()
	{
		if(this.showLongTermScene)
		{
			this.longTermScene.refresh();
		}
		else
		{
			this.shortTermScene.refresh();
		}
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		if(this.showLongTermScene)
		{
			switch(event.getAction())
			{
			case MotionEvent.ACTION_DOWN:
				this.setScene(this.longTermScene.touchDown((int)event.getX(), (int)event.getY()));
				break;
			case MotionEvent.ACTION_MOVE:
				this.setScene(this.longTermScene.touchMove((int)event.getX(), (int)event.getY()));
				break;
			case MotionEvent.ACTION_UP:
				this.setScene(this.longTermScene.touchUp((int)event.getX(), (int)event.getY()));
				break;
			}
		}
		else
		{
			switch(event.getAction())
			{
			case MotionEvent.ACTION_DOWN:
				this.setScene(this.shortTermScene.touchDown((int)event.getX(), (int)event.getY()));
				break;
			case MotionEvent.ACTION_MOVE:
				this.setScene(this.shortTermScene.touchMove((int)event.getX(), (int)event.getY()));
				break;
			case MotionEvent.ACTION_UP:
				this.setScene(this.shortTermScene.touchUp((int)event.getX(), (int)event.getY()));
				break;
			}
		}
		return true;
	}
	
	public void action()
	{
		if(this.showLongTermScene)
		{
			this.setScene(this.longTermScene.action());
		}
		else
		{
			this.setScene(this.shortTermScene.action());
		}
	}
	
	@Override
	public void onDraw(Canvas canvas)
	{
		if(this.showLongTermScene)
		{
			this.longTermScene.draw(canvas);
		}
		else
		{
			this.shortTermScene.draw(canvas);
		}
	}
	
	public void saveGameDataRecord()
	{
		this.main.saveGameDataRecord();
	}
	
	public void setScene(int sceneName)
    {
    	if(this.currentScene == sceneName)
    	{
    		return;
    	}
    	switch(sceneName)
    	{
    	case SCENE_LONGTERM:
    		this.showLongTermScene = true;
    		return;
    	case SCENE_QUIT:
    		this.main.saveGameDataRecord();
    		this.main.finish();
    		return;
    	}
    	this.currentScene = sceneName;
    	switch(sceneName)
    	{
    	case SCENE_MENU:
    		this.longTermScene = new MenuScene();
    		this.showLongTermScene = true;
    		break;
    	case SCENE_GAME_STAGE:
    		GameDataRecord.TIME_OPEN_STAGE_MODE ++;
    		this.longTermScene = new StageGameScene(main, 1);
    		this.showLongTermScene = true;
    		break;
    	case SCENE_GAME_TIME:
    		GameDataRecord.TIME_OPEN_TIME_MODE ++;
        	this.longTermScene = new TimeGameScene();
    		this.showLongTermScene = true;
    		break;
    	case SCENE_GAME_INFINTIY:
    		GameDataRecord.TIME_OPEN_INFINITY_MODE ++;
        	this.longTermScene = new InfinityGameScene();
    		this.showLongTermScene = true;
    		break;
    	case SCENE_ACHIEVEMENT:
    		this.shortTermScene = new AchievementScene();
    		this.showLongTermScene = false;
    		break;
    	case SCENE_HELP:
        	this.shortTermScene = new HelpScene();
    		this.showLongTermScene = false;
    		break;
    	case SCENE_ABOUT:
        	this.shortTermScene = new AboutScene();
    		this.showLongTermScene = false;
    		break;
    	}
		this.main.saveGameDataRecord();
    }
	
	static class Task extends TimerTask
	{
		private SceneControl sceneControl;
		private int time;
		
		public Task(SceneControl sceneControl)
		{
			this.sceneControl = sceneControl;
			this.time = 0;
		}
		
		@Override
		public void run()
		{
			this.sceneControl.action();
			this.sceneControl.postInvalidate();
			++ time;
			if(time % 30 == 0)
			{
				++ GameDataRecord.TIME_RUN_GAME;
			}
			if(time % 1000 == 0)
			{
				this.sceneControl.saveGameDataRecord();
			}
		}
	}
}
