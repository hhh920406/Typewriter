package zsys.graphic;

import android.graphics.Canvas;

public class DynamicSizeConcentricDualRotatingArc 
{
	private ConcentricDualRotatingArc concentricDualRotatingArc;
	
	private static final int maximumRadius = 60;
	private static final int minimumRadius = 0;
	private int currentRadius;
	
	private boolean isPressed;
	
	public DynamicSizeConcentricDualRotatingArc()
	{
		this.concentricDualRotatingArc = new ConcentricDualRotatingArc();
		this.concentricDualRotatingArc.setRotationSpeed(10.0f);
		this.currentRadius = 0;
		this.isPressed = false;
	}
	
	public void setPosition(int x, int y)
	{
		this.concentricDualRotatingArc.getPosition().setPosition(x, y);
	}
	
	public void setSize(int size)
	{
		this.currentRadius = size;
	}
	
	public void setPressed(boolean pressed)
	{
		this.isPressed = pressed;
	}
	
	public void draw(Canvas canvas)
	{
		if(this.isPressed)
		{
			if(this.currentRadius < maximumRadius)
			{
				this.currentRadius += 5;
			}
		}
		else
		{
			if(this.currentRadius > minimumRadius)
			{
				this.currentRadius -= 5;
			}
		}
		this.concentricDualRotatingArc.getSize().setSize(this.currentRadius, this.currentRadius);
		this.concentricDualRotatingArc.draw(canvas);
	}
}
