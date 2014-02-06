package zsys.scene;

import zsys.common.BitmapSource;
import zsys.common.Environment;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;

public class HelpScene implements SceneInterface
{
	@Override
	public int touchDown(int x, int y) 
	{
		return SceneControl.SCENE_HELP;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		return SceneControl.SCENE_HELP;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		return SceneControl.SCENE_LONGTERM;
	}

	@Override
	public int action() 
	{
		return SceneControl.SCENE_HELP;
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
		paint.setARGB(255, 0, 0, 0);
		paint.setTextAlign(Align.CENTER);
		paint.setTextSize(20 * Environment.getScaling());
		canvas.drawText("混乱蜜蜂游戏说明", Environment.getWindowSize().width >> 1, 30 * Environment.getScaling(), paint);
		paint.setTextSize(13 * Environment.getScaling());
		canvas.drawText("基本规则：蜜蜂被蜘蛛网困住，如果困住蜜蜂的网可", Environment.getWindowSize().width >> 1, 55 * Environment.getScaling(), paint);
		canvas.drawText("　　　　　以形成一个封闭多边形，且多边形内没有", Environment.getWindowSize().width >> 1, 70 * Environment.getScaling(), paint);
		canvas.drawText("　　　　　网或蜜蜂，则蜜蜂可以逃脱。　　　　　", Environment.getWindowSize().width >> 1, 85 * Environment.getScaling(), paint);

		paint.setTextAlign(Align.LEFT);
		paint.setARGB(255, 154, 130, 16);
		canvas.drawBitmap(BitmapSource.bee[BitmapSource.BEE_YELLOW], 20 * Environment.getScaling(), 95 * Environment.getScaling(), paint);
		canvas.drawText("普通蜜蜂，同名字一样没什么特", BitmapSource.bee[BitmapSource.BEE_YELLOW].getWidth() + 40, 120 * Environment.getScaling(), paint);
		canvas.drawText("殊之处。　　　　　　　　　　", BitmapSource.bee[BitmapSource.BEE_YELLOW].getWidth() + 40, 135 * Environment.getScaling(), paint);
		
		paint.setARGB(255, 2, 3, 100);
		canvas.drawBitmap(BitmapSource.bee[BitmapSource.BEE_BLUE], 20 * Environment.getScaling(), 155 * Environment.getScaling(), paint);
		canvas.drawText("濒死蜜蜂，处于绝望的模式，所", BitmapSource.bee[BitmapSource.BEE_BLUE].getWidth() + 40, 180 * Environment.getScaling(), paint);
		canvas.drawText("以无法移动。　　　　　　　　", BitmapSource.bee[BitmapSource.BEE_BLUE].getWidth() + 40, 195 * Environment.getScaling(), paint);
		
		paint.setARGB(255, 2, 100, 1);
		canvas.drawBitmap(BitmapSource.bee[BitmapSource.BEE_GREEN], 20 * Environment.getScaling(), 215 * Environment.getScaling(), paint);
		canvas.drawText("藏匿蜜蜂，善于隐藏的蜜蜂，连", BitmapSource.bee[BitmapSource.BEE_GREEN].getWidth() + 40, 240 * Environment.getScaling(), paint);
		canvas.drawText("接蜜蜂的网不可见。　　　　　", BitmapSource.bee[BitmapSource.BEE_GREEN].getWidth() + 40, 255 * Environment.getScaling(), paint);
		
		paint.setARGB(255, 100, 2, 1);
		canvas.drawBitmap(BitmapSource.bee[BitmapSource.BEE_RED], 20 * Environment.getScaling(), 275 * Environment.getScaling(), paint);
		canvas.drawText("挣扎蜜蜂，会不断的移动，可以", BitmapSource.bee[BitmapSource.BEE_RED].getWidth() + 40, 300 * Environment.getScaling(), paint);
		canvas.drawText("接受移动控制。　　　　　　　", BitmapSource.bee[BitmapSource.BEE_RED].getWidth() + 40, 315 * Environment.getScaling(), paint);
		
		paint.setARGB(255, 109, 35, 116);
		canvas.drawBitmap(BitmapSource.bee[BitmapSource.BEE_PURPLE], 20 * Environment.getScaling(), 335 * Environment.getScaling(), paint);
		canvas.drawText("酱油蜜蜂，其实没被粘住，只是", BitmapSource.bee[BitmapSource.BEE_PURPLE].getWidth() + 40, 360 * Environment.getScaling(), paint);
		canvas.drawText("过来围观的。　　　　　　　　", BitmapSource.bee[BitmapSource.BEE_PURPLE].getWidth() + 40, 375 * Environment.getScaling(), paint);
		
		paint.setARGB(255, 0, 0, 0);
		paint.setTextAlign(Align.RIGHT);
		canvas.drawText("点击任意位置返回。。。", Environment.getWindowSize().width, 420 * Environment.getScaling(), paint);
	}
}
