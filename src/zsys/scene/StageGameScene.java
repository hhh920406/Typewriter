package zsys.scene;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import zsys.common.Environment;
import zsys.common.GameDataRecord;
import zsys.creature.AbstractCreature;
import zsys.geometry.Position;
import zsys.geometry.Size;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Rect;
import android.graphics.Paint.Style;

public class StageGameScene extends AbstractGameScene
{
	private Context context;
	private String stageTitle;
	private String stageText;
	private int timeLimit;
	private int minBeeNumber;
	private Size stageSize;
	private int beeNumber;
	private int beeType[];
	private Position beePosition[];
	private int spiderNumber;
	private int spiderType[];
	private Position spiderPosition[];
	private int creatureNumber;
	private boolean relation[][];

	private static final int MAX_STAGE_NUMBER = 13;
	private int currentStageNumber;
	private int currentTime;
	private int currentBeeNumber;
	private boolean stageComplete;
	private boolean stageFailed;
	private boolean gameComplete;
	
	public StageGameScene(Context context, int stageNumber) 
	{
		this.context = context;
		this.currentStageNumber = stageNumber;
		this.stageComplete = false;
		this.stageFailed = false;
		this.gameComplete = false;
		this.refresh();
	}
	
	@Override
	public void nextStage()
	{
		this.stageComplete = false;
		++ this.currentStageNumber;
		if(this.currentStageNumber > MAX_STAGE_NUMBER)
		{
			this.gameComplete = true;
			return;
		}
		if(this.currentStageNumber > GameDataRecord.STAGE_MODE_MAX_STAGE)
		{
			GameDataRecord.STAGE_MODE_MAX_STAGE = this.currentStageNumber;
		}
		this.readStageInformation();
		this.createStageByInformation();
	}
	
	@Override
	public void refresh()
	{
		if(!this.gameComplete)
		{
			this.readStageInformation();
			this.createStageByInformation();
		}
	}
	
	@Override
	public int action()
	{
		if(!this.gameComplete)
		{
			if(this.stageComplete)
			{
				this.nextStage();
			}
			else 
			{
				if(!this.stageFailed)
				{
					super.action();
					this.currentBeeNumber = this.gameWeb.getReleasedBeeNumber();
					if(this.currentBeeNumber >= this.minBeeNumber)
					{
						this.stageComplete = true;
					}
					if(--this.currentTime <= 0)
					{
						this.stageFailed = true;
					}
				}
			}
		}
		return SceneControl.SCENE_GAME_STAGE;
	}
	
	@Override
	public int touchDown(int x, int y)
	{
		if(!this.gameComplete && !this.stageFailed)
		{
			super.touchDown(x, y);
		}
		return SceneControl.SCENE_GAME_STAGE;
	}
	
	@Override
	public int touchMove(int x, int y)
	{
		if(!this.gameComplete && !this.stageFailed)
		{
			super.touchMove(x, y);
		}
		return SceneControl.SCENE_GAME_STAGE;
	}
	
	@Override
	public int touchUp(int x, int y)
	{
		if(!this.gameComplete && !this.stageFailed)
		{
			super.touchUp(x, y);
		}
		if(this.gameComplete)
		{
			return SceneControl.SCENE_MENU;
		}
		return SceneControl.SCENE_GAME_STAGE;
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		if(!this.gameComplete)
		{
			super.draw(canvas);
		}
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(255, 0, 0, 0);
		paint.setTextSize(15 * Environment.getScaling());
		if(this.gameComplete)
		{
			paint.setARGB(255, 255, 255, 255);
			canvas.drawRect(0, 0, Environment.getWindowSize().width, Environment.getWindowSize().height, paint);
			this.dynamicSizeConcentricDualRotatingArc.draw(canvas);
			paint.setARGB(255, 0, 0, 0);
			paint.setTextAlign(Align.CENTER);
			paint.setTextSize(25 * Environment.getScaling());
			canvas.drawText("关卡模式完成", Environment.getWindowSize().width >> 1, (Environment.getWindowSize().height >> 1) - 25, paint);
		}
		else
		{
			canvas.drawText("关卡" + this.currentStageNumber + "：" + this.stageTitle, 20 * Environment.getScaling(), 30 * Environment.getScaling(), paint);
			canvas.drawText(this.stageText, 20 * Environment.getScaling(), 50 * Environment.getScaling(), paint);
			canvas.drawText("解救蜜蜂数 " + this.currentBeeNumber + "/" + this.minBeeNumber, 20 * Environment.getScaling(), 70 * Environment.getScaling(), paint);

			Rect timeRect = new Rect( Environment.getWindowSize().width - 20, Environment.getWindowSize().height - 50 - (Environment.getWindowSize().height - 100) * this.currentTime / this.timeLimit, Environment.getWindowSize().width - 10, Environment.getWindowSize().height - 50);
			canvas.drawRect(timeRect, paint);
			paint.setARGB(255, 0, 0, 0);
			paint.setStyle(Style.STROKE);
			timeRect = new Rect(Environment.getWindowSize().width - 20, 50, Environment.getWindowSize().width - 10, Environment.getWindowSize().height - 50);
			canvas.drawRect(timeRect, paint);
		}
	}
	
	public void setContext(Context context)
	{
		this.context = context;
	}
	
	private void readStageInformation()
	{
		this.stageSize = new Size();
		AssetManager assetManager = this.context.getAssets();
		BufferedReader input;
		String fileName = "Stage_";
		if(this.currentStageNumber<1000)
		{
			fileName += "0";
		}
		if(this.currentStageNumber<100)
		{
			fileName += "0";
		}
		if(this.currentStageNumber<10)
		{
			fileName += "0";
		}
		fileName += this.currentStageNumber;
		try 
		{
			input = new BufferedReader(new InputStreamReader(assetManager.open(fileName)));
			String line;
			String instruction[];
			while((line = input.readLine()) != null)
			{
				if(line.length() == 0)
				{
					continue;
				}
				instruction = line.split(" ");
				if(instruction[0].equalsIgnoreCase("StageTitle"))
				{
					this.stageTitle = new String(instruction[1].getBytes(), "UTF-8");
				}
				else if(instruction[0].equalsIgnoreCase("StageText"))
				{
					this.stageText = new String(instruction[1].getBytes(), "UTF-8");
				}
				else if(instruction[0].equalsIgnoreCase("TimeLimit"))
				{
					this.timeLimit = Integer.parseInt(instruction[1]);
				}
				else if(instruction[0].equalsIgnoreCase("MinBeeNumber"))
				{
					this.minBeeNumber = Integer.parseInt(instruction[1]);
				}
				else if(instruction[0].equalsIgnoreCase("Width"))
				{
					this.stageSize.width = (int)(Integer.parseInt(instruction[1]) * Environment.getScaling());
				}
				else if(instruction[0].equalsIgnoreCase("Height"))
				{
					this.stageSize.height = (int)(Integer.parseInt(instruction[1]) * Environment.getScaling());
				}
				else if(instruction[0].equalsIgnoreCase("BeeNumber"))
				{
					this.beeNumber = Integer.parseInt(instruction[1]);
					if(this.beeNumber != 0)
					{
						this.beePosition = new Position[this.beeNumber];
						this.beeType = new int[this.beeNumber];
					}
				}
				else if(instruction[0].equalsIgnoreCase("SpiderNumber"))
				{
					this.spiderNumber = Integer.parseInt(instruction[1]);
					if(this.spiderNumber != 0)
					{
						this.spiderPosition = new Position[this.spiderNumber];
						this.spiderType = new int[this.spiderNumber];
					}
				}
				else if(instruction[0].equalsIgnoreCase("StartCreateBee"))
				{
					for(int i=0;i<this.beeNumber;++i)
					{
						line = input.readLine();
						instruction = line.split(" ");
						if(instruction[0].equalsIgnoreCase("BEE_NORMAL"))
						{
							this.beeType[i] = AbstractCreature.BEE_NORMAL;
						}
						else if(instruction[0].equalsIgnoreCase("BEE_DYING"))
						{
							this.beeType[i] = AbstractCreature.BEE_DYING;
						}
						else if(instruction[0].equalsIgnoreCase("BEE_MOVING"))
						{
							this.beeType[i] = AbstractCreature.BEE_MOVING;
						}
						else if(instruction[0].equalsIgnoreCase("BEE_HIDING"))
						{
							this.beeType[i] = AbstractCreature.BEE_HIDING;
						}
						else if(instruction[0].equalsIgnoreCase("BEE_PASSING"))
						{
							this.beeType[i] = AbstractCreature.BEE_PASSING;
						}
						this.beePosition[i] = new Position();
						this.beePosition[i].x = (int)(Integer.parseInt(instruction[1]) * Environment.getScaling());
						this.beePosition[i].y = (int)(Integer.parseInt(instruction[2]) * Environment.getScaling());
					}
				}
				else if(instruction[0].equalsIgnoreCase("StartCreateSpider"))
				{
					for(int i=0;i<this.spiderNumber;++i)
					{
						line = input.readLine();
						instruction = line.split(" ");
						if(instruction[0].equalsIgnoreCase("SPIDER_NORMAL"))
						{
							this.spiderType[i] = AbstractCreature.SPIDER_NORMAL;
						}
						this.spiderPosition[i] = new Position();
						this.spiderPosition[i].x = (int)(Integer.parseInt(instruction[1]) * Environment.getScaling());
						this.spiderPosition[i].y = (int)(Integer.parseInt(instruction[2]) * Environment.getScaling());
					}
				}
				else if(instruction[0].equalsIgnoreCase("StartSetRelationWithPair"))
				{
					this.creatureNumber = this.beeNumber + this.spiderNumber;
					this.relation = new boolean[this.creatureNumber][this.creatureNumber];
					for(int i=0;i<this.creatureNumber;++i)
					{
						for(int j=0;j<this.creatureNumber;++j)
						{
							this.relation[i][j] = false;
						}
					}
					while(true)
					{
						line = input.readLine();
						if(line.equalsIgnoreCase("EndSetRelationWithPair"))
						{
							break;
						}
						instruction = line.split(" ");
						this.relation[Integer.parseInt(instruction[0])][Integer.parseInt(instruction[1])] = true;
						this.relation[Integer.parseInt(instruction[1])][Integer.parseInt(instruction[0])] = true;
					}
				}
				else if(instruction[0].equalsIgnoreCase("StartSetRelationWithMatrix"))
				{
					this.creatureNumber = this.beeNumber + this.spiderNumber;
					this.relation = new boolean[this.creatureNumber][this.creatureNumber];
					for(int i=0;i<this.creatureNumber;++i)
					{
						line = input.readLine();
						instruction = line.split(" ");
						for(int j=0;j<this.creatureNumber;++j)
						{
							this.relation[i][j] = instruction[j].equals("1");
						}
					}
					input.readLine();
				}
			}
			input.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	private void createStageByInformation()
	{
		this.stageFailed = false;
		this.stageComplete = false;
		this.currentBeeNumber = 0;
		this.currentTime = this.timeLimit;
		this.gameWeb.getWebSize().setSize(this.stageSize.width,this. stageSize.height);
		this.gameWeb.setBeeNumber(this.beeNumber);
		this.gameWeb.setSpiderNumber(this.spiderNumber);
		this.gameWeb.initialWeb();
		for(int i=0;i<this.beeNumber;++i)
		{
			this.gameWeb.createBee(i, this.beeType[i], this.beePosition[i].x, this.beePosition[i].y);
		}
		for(int i=0;i<this.spiderNumber;++i)
		{
			this.gameWeb.createSpider(i, this.spiderType[i], this.spiderPosition[i].x, this.spiderPosition[i].y);
		}
		this.gameWeb.setCreatureRelation(this.relation);
		this.gameWeb.touchUp(0, 0);
	}
}
