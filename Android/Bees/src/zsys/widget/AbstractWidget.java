package zsys.widget;

import zsys.geometry.Size;
import zsys.geometry.Position;
import android.graphics.Canvas;

public class AbstractWidget implements WidgetInterface
{
	public Position position;
	public Size size;
	private boolean focused;
	
	public AbstractWidget()
	{
		this.position = new Position();
		this.size = new Size();
	}
	
	@Override
	public void motionDown(int x, int y) 
	{
		this.focused = this.isInsideWidget(x, y);
	}

	@Override
	public void motionMove(int x, int y) 
	{
		this.focused = this.isInsideWidget(x, y);
	}

	@Override
	public void motionUp(int x, int y) 
	{
		this.focused = this.isInsideWidget(x, y);
	}

	@Override
	public void draw(Canvas canvas) 
	{
		return;
	}
	
	protected int getRight()
	{
		return this.position.x + this.size.width;
	}
	
	protected int getBottom()
	{
		return this.position.y + this.size.height;
	}

	protected boolean isInsideWidget(int x, int y)
	{
		return x >= this.position.x && x <= this.getRight() && y >= this.position.y && y <= this.getBottom();
	}

	@Override
	public boolean isFocused() 
	{
		return this.focused;
	}
}
