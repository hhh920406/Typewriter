package zsys.widget;

import android.graphics.Canvas;

public interface WidgetInterface 
{
	public void motionDown(int x, int y);
	public void motionMove(int x, int y);
	public void motionUp(int x, int y);
	public void draw(Canvas canvas);
	public boolean isFocused();
}
