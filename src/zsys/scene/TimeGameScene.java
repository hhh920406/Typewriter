package zsys.scene;

import zsys.common.Environment;
import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;
import zsys.creature.TimeGameWeb;
import zsys.geometry.Size;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Style;
import android.graphics.Rect;

public class TimeGameScene extends InfinityGameScene
{
	private int totalTimePoint;
	private int currentTimePoint;
	private int showTimePoint;
	private int stageNumber;
	private boolean timeUp;
	private boolean justAddTime;
	
	public TimeGameScene() 
	{
		this.totalTimePoint = 1800;
		this.currentTimePoint = 1800;
		this.showTimePoint = 1800;
		this.stageNumber = 1;
		this.timeUp = false;
		this.justAddTime = false;
		this.gameWeb = new TimeGameWeb();
		this.randomCreateCreature();
	}
	
	@Override
	public int touchDown(int x, int y) 
	{
		super.touchDown(x, y);
		return SceneControl.SCENE_GAME_TIME;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		super.touchMove(x, y);
		return SceneControl.SCENE_GAME_TIME;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		super.touchUp(x, y);
		if(this.timeUp)
		{
			return SceneControl.SCENE_MENU;
		}
		return SceneControl.SCENE_GAME_TIME;
	}
	
	@Override
	public int action()
	{
		if(!this.timeUp)
		{
			super.action();
			if(--this.currentTimePoint <= 0)
			{
				this.timeUp = true;
			}
			if(this.showTimePoint < this.currentTimePoint)
			{
				this.showTimePoint += 2;
				if(this.showTimePoint > 1800)
				{
					this.showTimePoint = 1800;
				}
			}
			else
			{
				this.showTimePoint = this.currentTimePoint;
			}
			int tempX = Environment.getWindowSize().width - 15;
			int tempY = 50;
			if(this.showTimePoint < 1800)
			{
				tempY = Environment.getWindowSize().height - 50 - (Environment.getWindowSize().height - 100) * this.showTimePoint / 1800;
			}
			int temp = ((TimeGameWeb)this.gameWeb).moveTimePoint(tempX, tempY);
			if(temp > 0)
			{
				this.justAddTime = true;
				this.currentTimePoint += temp;
				this.totalTimePoint += temp;
				if(GameDataRecord.TIME_MODE_MAX_TIME_POINT < this.totalTimePoint)
				{
					GameDataRecord.TIME_MODE_MAX_TIME_POINT = this.totalTimePoint;
				}
			}
		}
		return SceneControl.SCENE_GAME_TIME;
	}
	
	@Override
	public void nextStage()
	{
		this.stageNumber = this.stageNumber + 1;
		if(GameDataRecord.TIME_MODE_MAX_STAGE < this.stageNumber)
		{
			GameDataRecord.TIME_MODE_MAX_STAGE = this.stageNumber;
		}
		this.randomCreateCreature();
	}
	
	@Override
	public void refresh()
	{
		this.currentTimePoint -= 150;
		this.randomCreateCreature();
	}
	
	@Override
	public void randomCreateCreature()
	{
		int beeNumber;
		int spiderNumber;
		int creatureNumber;
		Size stageSize = new Size();
		boolean creatureRelation[][];
		
		beeNumber = 15;
		spiderNumber = 0;
		creatureNumber = beeNumber + spiderNumber;
		creatureRelation = new boolean[creatureNumber][creatureNumber];
		this.gameWeb.setBeeNumber(beeNumber);
		this.gameWeb.setSpiderNumber(spiderNumber);
		stageSize.width = 320;
		stageSize.height = 480;
		this.gameWeb.getWebSize().setSize(stageSize.width, stageSize.height);
		this.gameWeb.initialWeb();
		
		for(int i=0;i<beeNumber;++i)
		{
			double temp = Math.random();
			int x = 60 + (int)(Math.random() * (stageSize.width - 120));
			int y = 60 + (int)(Math.random() * (stageSize.height - 120));
			if(temp < 0.9)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_NORMAL, x, y);
			}
			else if(temp < 0.93)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_DYING, x, y);
			}
			else if(temp < 0.96)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_MOVING, x, y);
			}
			else if(temp < 0.97)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_HIDING, x, y);
			}
			else
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_PASSING, x, y);
			}
		}
		
		for(int i=0;i<creatureNumber;++i)
		{
			creatureRelation[i][i] = false;
			for(int j=i+1;j<creatureNumber;++j)
			{
				creatureRelation[i][j] = creatureRelation[j][i] = (Math.random() > 0.65);
			}
		}
		
		this.gameWeb.setCreatureRelation(creatureRelation);
		this.gameWeb.touchUp(0, 0);
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(255, 255, 255, 255);
		canvas.drawRect(0, 0, Environment.getWindowSize().width, Environment.getWindowSize().height, paint);
		paint.setARGB(255, 0, 0, 0);
		paint.setTextSize(15.0f);
		canvas.drawText("时间模式 第 " + this.stageNumber + " 网", 20, 30, paint);
		canvas.drawText("时间点：" + this.totalTimePoint + " / " + GameDataRecord.TIME_MODE_MAX_TIME_POINT, 20, 50, paint);
		if(this.timeUp)
		{
			paint.setTextAlign(Align.CENTER);
			paint.setTextSize(23.0f);
			canvas.drawText("时间到，最终得分：" + this.totalTimePoint, Environment.getWindowSize().width >> 1, (Environment.getWindowSize().height >> 1) - 30, paint);
			this.dynamicSizeConcentricDualRotatingArc.draw(canvas);
		}
		else
		{
			Rect timeRect = new Rect( Environment.getWindowSize().width - 20, Environment.getWindowSize().height - 50 - (Environment.getWindowSize().height - 100) * this.showTimePoint / 1800, Environment.getWindowSize().width - 10, Environment.getWindowSize().height - 50);
			canvas.drawRect(timeRect, paint);
			paint.setARGB(255, 0, 0, 0);
			paint.setStyle(Style.STROKE);
			timeRect = new Rect(Environment.getWindowSize().width - 20, 50, Environment.getWindowSize().width - 10, Environment.getWindowSize().height - 50);
			if(this.justAddTime)
			{
				this.justAddTime = false;
				paint.setARGB(50, 0, 0, 0);
			}
			canvas.drawRect(timeRect, paint);
			this.gameWeb.draw(canvas);
			this.dynamicSizeConcentricDualRotatingArc.draw(canvas);
		}
	}
}
