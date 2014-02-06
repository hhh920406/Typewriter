package zsys.scene;

import zsys.common.Environment;
import zsys.creature.GameWebInterface;
import zsys.creature.NormalGameWeb;
import zsys.geometry.Position;
import zsys.graphic.DynamicSizeConcentricDualRotatingArc;
import android.graphics.Canvas;
import android.graphics.Paint;

public class AbstractGameScene implements SceneInterface
{
	protected GameWebInterface gameWeb;
	private Position historyMousePosition;
	
	DynamicSizeConcentricDualRotatingArc dynamicSizeConcentricDualRotatingArc;
	
	public AbstractGameScene() 
	{
		this.gameWeb = new NormalGameWeb();
		this.historyMousePosition = new Position();
		this.dynamicSizeConcentricDualRotatingArc = new DynamicSizeConcentricDualRotatingArc();
	}
	
	@Override
	public int touchDown(int x, int y) 
	{
		if(!this.gameWeb.touchDown(x, y))
		{
			this.historyMousePosition.setPosition(x, y);
			this.dynamicSizeConcentricDualRotatingArc.setPosition(x, y);
		}
		this.dynamicSizeConcentricDualRotatingArc.setPressed(true);
		this.dynamicSizeConcentricDualRotatingArc.setSize(0);
		return SceneControl.SCENE_NULL;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		if(!this.gameWeb.touchMove(x, y))
		{
			this.gameWeb.moveWeb(x - this.historyMousePosition.x, y - this.historyMousePosition.y);
			this.historyMousePosition.setPosition(x, y);
		}
		this.dynamicSizeConcentricDualRotatingArc.setPosition(x, y);
		this.dynamicSizeConcentricDualRotatingArc.setPressed(true);
		return SceneControl.SCENE_NULL;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		this.gameWeb.touchUp(x, y);
		this.dynamicSizeConcentricDualRotatingArc.setPosition(x, y);
		this.dynamicSizeConcentricDualRotatingArc.setPressed(false);
		return SceneControl.SCENE_NULL;
	}

	@Override
	public int action()
	{
		this.gameWeb.action();
		return SceneControl.SCENE_NULL;
	}

	@Override
	public void refresh() 
	{
		return;
	}
	
	public void nextStage()
	{
		return;
	}
	
	@Override
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setARGB(255, 255, 255, 255);
		canvas.drawRect(0, 0, Environment.getWindowSize().width, Environment.getWindowSize().height, paint);
		this.gameWeb.draw(canvas);
		this.dynamicSizeConcentricDualRotatingArc.draw(canvas);
	}
}
