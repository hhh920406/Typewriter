package zsys.graphic;

import zsys.common.BitmapSource;
import zsys.geometry.Position;
import zsys.geometry.Size;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class TrackTimePoint 
{
	private Position position;
	private Size size;
	private Bitmap bitmap;
	private int time;
	private int moveSpeed;
	private boolean arriveTarget;
	private boolean couldDisappear;
	
	public TrackTimePoint()
	{
		this.bitmap = null;
		this.position = new Position();
		this.size = new Size(0, 0);
		this.moveSpeed = 10;
	}
	
	public boolean alive()
	{
		return !this.couldDisappear;
	}
	
	public void create()
	{
		this.arriveTarget = false;
		this.couldDisappear = false;
	}
	
	public void delete()
	{
		this.arriveTarget = true;
		this.couldDisappear = true;
	}
	
	public void setImage(int time)
	{
		this.time = time;
		switch(this.time)
		{
		case 20: 
			this.bitmap = BitmapSource.time[BitmapSource.TIME_POINT_20];
			break;
		case 30: 
			this.bitmap = BitmapSource.time[BitmapSource.TIME_POINT_30];
			break;
		case 40: 
			this.bitmap = BitmapSource.time[BitmapSource.TIME_POINT_40];
			break;
		case 50: 
			this.bitmap = BitmapSource.time[BitmapSource.TIME_POINT_50];
			break;
		default:
			this.bitmap = BitmapSource.time[BitmapSource.TIME_POINT_10];
		}
		this.size = new Size(this.bitmap.getWidth(), this.bitmap.getHeight());
	}
	
	public Position getPosition()
	{
		return this.position;
	}
	
	public void setMoveSpeed(int speed)
	{
		this.moveSpeed = speed;
	}
	
	public int move(int x, int y)
	{
		if(!this.couldDisappear)
		{
			if(this.arriveTarget)
			{
				this.size.width -= 5;
				this.size.height -= 5;
				if(this.size.width <= 0 || this.size.height <= 0)
				{
					this.couldDisappear = true;
				}
			}
			else
			{
				int tempX = x - this.position.x;
				int tempY = y - this.position.y;
				int tempDistance = (int)Math.sqrt((double)(tempX * tempX + tempY * tempY));
				if(tempDistance < this.moveSpeed)
				{
					this.arriveTarget = true;
					return this.time;
				}
				this.position.x += this.moveSpeed * tempX / tempDistance;
				this.position.y += this.moveSpeed * tempY / tempDistance;
			}
		}
		return 0;
	}
	
	public void draw(Canvas canvas)
	{
		if(!this.couldDisappear)
		{
			Paint paint = new Paint();
			paint.setAntiAlias(true);
			canvas.drawBitmap(this.bitmap, null, new Rect(
					this.position.x - (this.size.width >> 1), this.position.y - (this.size.height >> 1),
					this.position.x + (this.size.width >> 1), this.position.y + (this.size.height >> 1)), paint);
		}
	}
}
