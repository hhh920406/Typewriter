package zsys.graphic;

import android.graphics.Canvas;
import zsys.geometry.Size;
import zsys.geometry.Position;

public class ConcentricDualRotatingArc 
{
	private RotatingArc outsideArc;
	private RotatingArc inSideArc;
	private Position position;
	private Size size;
	
	public ConcentricDualRotatingArc()
	{
		this.inSideArc = new RotatingArc();
		this.outsideArc = new RotatingArc();
		this.position = new Position(0, 0);
		this.size = new Size(20, 20);
		this.setRotationSpeed(5.0f);
	}
	
	public void setRotationSpeed(float speed)
	{
		this.inSideArc.setRotationSpeed(speed);
		this.outsideArc.setRotationSpeed(-speed);
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
		this.inSideArc.getPosition().setPosition(this.position.x, this.position.y);
		this.inSideArc.getSize().setSize((int) (this.size.width * 0.6), (int) (this.size.height * 0.6));
		this.inSideArc.draw(canvas);
		this.outsideArc.getPosition().setPosition(this.position.x, this.position.y);
		this.outsideArc.getSize().setSize(this.size.width, this.size.height);
		this.outsideArc.draw(canvas);
	}
}
