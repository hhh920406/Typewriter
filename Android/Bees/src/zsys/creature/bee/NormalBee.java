package zsys.creature.bee;

import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.creature.AbstractCreature;
import zsys.creature.CreatureInterface;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class NormalBee extends AbstractCreature
{
	protected int escapeDirectionX;
	protected int escapeDirectionY;
	
	protected int bitmap;
	
	public NormalBee()
	{
		this.draging = false;
		this.escaping = false;
		this.escaped = false;
		this.escapeDirectionX = 0;
		this.escapeDirectionY = 0;
		this.bitmap = BitmapSource.BEE_YELLOW;
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.BEE_NORMAL;
	}
	
	protected void addReleasedBeeNumber()
	{
		GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_NORMAL] ++;
	}

	@Override
	public void releaseCreature() 
	{
		if(!this.isEscaping())
		{
			this.escapeDirectionX = (int) (Math.random() * 3 + 6);
			this.escapeDirectionY = (int) (Math.random() * 3 + 6);
			this.addReleasedBeeNumber();
			this.escaping = true;
			if(Math.random() > 0.5)
			{
				this.escapeDirectionX = - this.escapeDirectionX;
			}
			if(Math.random() > 0.5)
			{
				this.escapeDirectionY = - this.escapeDirectionY;
			}
		}
	}

	@Override
	public void touchDown(int x, int y) 
	{
		this.draging = this.isInsideArea(x, y);
	}

	@Override
	public void touchMove(int x, int y) 
	{
		if(this.isDraging())
		{
			this.position.setPosition(x, y);
		}
	}

	@Override
	public void touchUp(int x, int y) 
	{
		this.draging = false;
	}
	
	@Override
	public void action()
	{
		if(this.isEscaping() && !this.isEscaped())
		{
			this.position.x += (Math.random() - 0.5) * 2 + this.escapeDirectionX;
			this.position.y += (Math.random() - 0.5) * 2 + this.escapeDirectionY;
			if(this.isOutsideScene())
			{
				this.escaped = true;
			}
		}
	}

	@Override
	public void draw(Canvas canvas) 
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		Rect rect = new Rect(this.getLeft() - this.offsetPosition.x, this.getTop() - this.offsetPosition.y, this.getRight() - this.offsetPosition.x, this.getBottom() - this.offsetPosition.y);
		if(!this.isEscaped())
		{
			canvas.drawBitmap(BitmapSource.bee[bitmap], null, rect, paint);
		}
	}
}
