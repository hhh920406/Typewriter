package zsys.scene;

import zsys.common.BitmapSource;
import zsys.common.Environment;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;

public class AboutScene implements SceneInterface
{
	@Override
	public int touchDown(int x, int y) 
	{
		return SceneControl.SCENE_ABOUT;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		return SceneControl.SCENE_ABOUT;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		return SceneControl.SCENE_LONGTERM;
	}

	@Override
	public int action() 
	{
		return SceneControl.SCENE_ABOUT;
	}
	
	@Override
	public void refresh() 
	{
		return;
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(255, 255, 255, 255);
		canvas.drawRect(0.0f, 0.0f, (float)Environment.getWindowSize().width, (float)Environment.getWindowSize().height, paint);
		canvas.drawBitmap(BitmapSource.about, 
				(Environment.getWindowSize().width - BitmapSource.about.getWidth()) >> 1, 
				((Environment.getWindowSize().height - BitmapSource.about.getHeight()) >> 1) - 20, paint);
		paint.setARGB(255, 0, 0, 0);
		paint.setTextAlign(Align.RIGHT);
		paint.setTextSize(13);
		canvas.drawText("游戏版本：" + Environment.GAME_VERSION, Environment.getWindowSize().width, Environment.getWindowSize().height - 30, paint);
	}
}
