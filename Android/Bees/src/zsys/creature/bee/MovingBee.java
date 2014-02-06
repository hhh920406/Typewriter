package zsys.creature.bee;

import android.graphics.Canvas;
import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;
import zsys.geometry.Position;

public class MovingBee extends NormalBee
{
	private Position moveTarget;
	private boolean isInTarget;
	
	public MovingBee()
	{
		this.bitmap = BitmapSource.BEE_RED;
		this.isInTarget = true;
		this.moveTarget = new Position();
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.BEE_MOVING;
	}
	
	@Override
	public void touchUp(int x, int y)
	{
		super.touchUp(x, y);
	}
	
	protected void move()
	{
		if(this.isInTarget)
		{
			this.isInTarget = false;
			this.moveTarget.x = (int) (Math.random() * this.stageSize.width);
			this.moveTarget.y = (int) (Math.random() * this.stageSize.height);
		}
		else
		{
			if(this.position.x < this.moveTarget.x)
			{
				this.position.x += Math.random() * 3;
			}
			else if(this.position.x > this.moveTarget.x)
			{
				this.position.x -= Math.random() * 3;
			}
			if(this.position.y < this.moveTarget.y)
			{
				this.position.y += Math.random() * 3;
			}
			else if(this.position.y > this.moveTarget.y)
			{
				this.position.y -= Math.random() * 3;
			}
			if(this.position.x == this.moveTarget.x && this.position.y == this.moveTarget.y)
			{
				this.isInTarget = true;
			}
		}
	}
	
	@Override
	protected void addReleasedBeeNumber()
	{
		GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_MOVING] ++;
	}
	
	@Override
	public void action()
	{
		if(!this.isEscaping() && !this.isDraging())
		{
			this.move();
		}
		if(this.isEscaping())
		{
			super.action();
		}
	}
	
	@Override
	public void draw(Canvas canvas) 
	{
		super.draw(canvas);
	}
}
