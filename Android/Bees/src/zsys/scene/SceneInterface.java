package zsys.scene;

import android.graphics.Canvas;

public interface SceneInterface 
{
	public int touchDown(int x, int y);
	public int touchMove(int x, int y);
	public int touchUp(int x, int y);
	public int action();
	public void refresh();
	public void draw(Canvas canvas);
}
