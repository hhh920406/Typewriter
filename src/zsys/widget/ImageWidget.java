package zsys.widget;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class ImageWidget extends AbstractWidget
{
	private Bitmap bitmap;
	
	public ImageWidget()
	{
		this.bitmap = null;
	}
	
	public ImageWidget(Bitmap bitmap)
	{
		this.setImage(bitmap);
	}
	
	public void setImage(Bitmap bitmap)
	{
		this.bitmap = bitmap;
		this.size.setSize(this.bitmap.getWidth(), this.bitmap.getHeight());
	}
	
	@Override
	public void motionDown(int x, int y) 
	{
		super.motionDown(x, y);
	}

	@Override
	public void motionMove(int x, int y) 
	{
		super.motionMove(x, y);
	}

	@Override
	public void motionUp(int x, int y) 
	{
		super.motionUp(x, y);
	}

	@Override
	public void draw(Canvas canvas) 
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		Rect rect = new Rect(this.position.x, this.position.y, this.getRight(), this.getBottom());
		canvas.drawBitmap(this.bitmap, null, rect, paint);
		if(this.isFocused())
		{
			paint.setARGB(20, 255, 255, 255);
			canvas.drawRect(rect, paint);
		}
	}

}
