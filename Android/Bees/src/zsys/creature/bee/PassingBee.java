package zsys.creature.bee;

import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;


public class PassingBee extends MovingBee
{
	public PassingBee()
	{
		this.bitmap = BitmapSource.BEE_PURPLE;
		this.escaping = true;
		this.escaped = true;
		GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_PASSING] ++;
	}
	
	@Override
	protected void addReleasedBeeNumber()
	{
		return;
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.BEE_PASSING;
	}
	
	@Override
	public void action()
	{
		if(!this.isDraging())
		{
			this.move();
		}
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		this.move();
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		Rect rect = new Rect(this.getLeft() - this.offsetPosition.x, this.getTop() - this.offsetPosition.y, this.getRight() - this.offsetPosition.x, this.getBottom() - this.offsetPosition.y);
		canvas.drawBitmap(BitmapSource.bee[bitmap], null, rect, paint);;
	}
}
