package zsys.graphic;

import zsys.geometry.Size;
import zsys.geometry.Position;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.RectF;

public class RotatingArc 
{
	private float rotationAngle;
	private float rotationSpeed;
	private Position position;
	private Size size;
	
	public RotatingArc()
	{
		this.rotationAngle = 0.0f;
		this.rotationSpeed = 5.0f;
		this.position = new Position(0, 0);
		this.size = new Size(20, 20);
	}
	
	public void setRotationSpeed(float speed)
	{
		this.rotationSpeed = speed;
	}
	
	public Position getPosition()
	{
		return this.position;
	}
	
	public Size getSize()
	{
		return this.size;
	}
	
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(3);
		paint.setARGB(50, 100, 100, 100);
		canvas.drawArc(new RectF(this.position.x - (this.size.width >> 1), this.position.y - (this.size.height >> 1), this.position.x + (this.size.width >> 1), this.position.y + (this.size.height >> 1)), this.rotationAngle, 300.0f, false, paint);
		this.rotationAngle += this.rotationSpeed;
	}
}
