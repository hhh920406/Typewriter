package zsys.scene;

import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;
import zsys.geometry.Size;
import android.graphics.Canvas;
import android.graphics.Paint;

public class InfinityGameScene extends AbstractGameScene
{
	public InfinityGameScene()
	{
		this.randomCreateCreature();
	}
	
	@Override
	public int action()
	{
		if(this.gameWeb.isAllReleased())
		{
			this.nextStage();
		}
		super.action();
		return SceneControl.SCENE_GAME_INFINTIY;
	}
	
	@Override
	public void nextStage()
	{
		GameDataRecord.INFINTIY_MODE_MAX_STAGE = GameDataRecord.INFINTIY_MODE_MAX_STAGE + 1;
		this.randomCreateCreature();
	}
	
	@Override
	public void refresh()
	{
		this.randomCreateCreature();
	}
	
	public void randomCreateCreature()
	{
		int beeNumber;
		int spiderNumber;
		int creatureNumber;
		Size stageSize = new Size();
		boolean creatureRelation[][];
		
		beeNumber = (int) (Math.random() * 10) + 10;
		spiderNumber = 0;
		creatureNumber = beeNumber + spiderNumber;
		creatureRelation = new boolean[creatureNumber][creatureNumber];
		this.gameWeb.setBeeNumber(beeNumber);
		this.gameWeb.setSpiderNumber(spiderNumber);
		stageSize.width = (int)(Math.random() * 500) + 320;
		stageSize.height = (int)(Math.random() * 500) + 320;
		this.gameWeb.getWebSize().setSize(stageSize.width, stageSize.height);
		this.gameWeb.initialWeb();
		
		for(int i=0;i<beeNumber;++i)
		{
			double temp = Math.random();
			int x = 60 + (int)(Math.random() * (stageSize.width - 120));
			int y = 60 + (int)(Math.random() * (stageSize.height - 120));
			if(temp < 0.8)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_NORMAL, x, y);
			}
			else if(temp < 0.85)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_DYING, x, y);
			}
			else if(temp < 0.9)
			{
				this.gameWeb.createBee(i, CreatureInterface.BEE_MOVING, x, y);
			}
			else if(temp < 0.95)
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
				creatureRelation[i][j] = creatureRelation[j][i] = (Math.random() > 0.6);
			}
		}
		
		this.gameWeb.setCreatureRelation(creatureRelation);
		this.gameWeb.touchUp(0, 0);
	}

	@Override
	public int touchDown(int x, int y) 
	{
		super.touchDown(x, y);
		return SceneControl.SCENE_GAME_INFINTIY;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		super.touchMove(x, y);
		return SceneControl.SCENE_GAME_INFINTIY;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		super.touchUp(x, y);
		return SceneControl.SCENE_GAME_INFINTIY;
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		super.draw(canvas);
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(255, 0, 0, 0);
		paint.setTextSize(15.0f);
		canvas.drawText("无限模式 第 " + GameDataRecord.INFINTIY_MODE_MAX_STAGE + " 网", 20, 30, paint);
	}
}
