package zsys.creature;

import android.graphics.Canvas;
import zsys.graphic.TrackTimePoint;

public class TimeGameWeb extends NormalGameWeb
{
	private static final int MAX_TIME_POINT_NUMBER = 30;
	private TrackTimePoint timePoint[];
	
	public TimeGameWeb()
	{
		this.timePoint = new TrackTimePoint[MAX_TIME_POINT_NUMBER];
		for(int i=0;i<MAX_TIME_POINT_NUMBER;++i)
		{
			this.timePoint[i] = new TrackTimePoint();
			this.timePoint[i].delete();
		}
	}
	
	private void addTimePoint(int time, int x, int y)
	{
		int index = -1;
		for(int i=0;i<MAX_TIME_POINT_NUMBER;++i)
		{
			if(!this.timePoint[i].alive())
			{
				index = i;
				break;
			}
		}
		if(index == -1)
		{
			return;
		}
		this.timePoint[index].setImage(time);
		this.timePoint[index].getPosition().setPosition(x, y);
		this.timePoint[index].create();
	}
	
	@Override
	protected void releaseCreature(int creatureIndex)
	{
		super.releaseCreature(creatureIndex);
		float temp = (float)Math.random();
		if(temp < 0.9)
		{
			this.addTimePoint(10, this.creatureArray[creatureIndex].getPosition().x, this.creatureArray[creatureIndex].getPosition().y);
		}
		else if(temp < 0.99)
		{
			this.addTimePoint(20, this.creatureArray[creatureIndex].getPosition().x, this.creatureArray[creatureIndex].getPosition().y);
		}
		else if(temp < 0.999)
		{
			this.addTimePoint(30, this.creatureArray[creatureIndex].getPosition().x, this.creatureArray[creatureIndex].getPosition().y);
		}
		else if(temp < 0.9999)
		{
			this.addTimePoint(40, this.creatureArray[creatureIndex].getPosition().x, this.creatureArray[creatureIndex].getPosition().y);
		}
		else
		{
			this.addTimePoint(50, this.creatureArray[creatureIndex].getPosition().x, this.creatureArray[creatureIndex].getPosition().y);
		}
	}
	
	public int moveTimePoint(int x, int y)
	{
		int total = 0;
		for(int i=0;i<MAX_TIME_POINT_NUMBER;++i)
		{
			total += this.timePoint[i].move(x, y);
		}
		return total;
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		for(int i=0;i<MAX_TIME_POINT_NUMBER;++i)
		{
			this.timePoint[i].draw(canvas);
		}
		super.draw(canvas);
	}
}
