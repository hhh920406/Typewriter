package zsys.scene;

import zsys.common.BitmapSource;
import zsys.common.Environment;
import zsys.widget.ImageWidget;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;

public class MenuScene implements SceneInterface
{
	private ImageWidget titleImageWidget;
	private ImageWidget menuImageWidget[];
	private int menuImageWidgetTargetY[];
	
	public MenuScene() 
	{
		this.titleImageWidget = new ImageWidget(BitmapSource.title);
		this.menuImageWidget = new ImageWidget[BitmapSource.MENU_NUMBER];
		this.menuImageWidgetTargetY = new int[BitmapSource.MENU_NUMBER];
		this.menuImageWidget[BitmapSource.MENU_STAGE] = new ImageWidget(BitmapSource.menu[BitmapSource.MENU_STAGE]);
		this.menuImageWidget[BitmapSource.MENU_TIME] = new ImageWidget(BitmapSource.menu[BitmapSource.MENU_TIME]);
		this.menuImageWidget[BitmapSource.MENU_INFINITY] = new ImageWidget(BitmapSource.menu[BitmapSource.MENU_INFINITY]);
		this.menuImageWidget[BitmapSource.MENU_ACHIEVEMENT] = new ImageWidget(BitmapSource.menu[BitmapSource.MENU_ACHIEVEMENT]);
		this.menuImageWidget[BitmapSource.MENU_QUIT] = new ImageWidget(BitmapSource.menu[BitmapSource.MENU_QUIT]);
		
		this.titleImageWidget.position.x = (Environment.getWindowSize().width - this.titleImageWidget.size.width) >> 1;
		this.titleImageWidget.position.y =(Environment.getWindowSize().height >> 1) - 200;
		for(int i=0;i<BitmapSource.MENU_NUMBER;++i)
		{
			this.menuImageWidget[i].position.x = (Environment.getWindowSize().width - this.menuImageWidget[i].size.width) >> 1;
			this.menuImageWidget[i].position.y = (Environment.getWindowSize().height >> 1) - 50;
			this.menuImageWidgetTargetY[i] = (Environment.getWindowSize().height >> 1) + 50 * i - 50;
		}
	}

	@Override
	public int touchDown(int x, int y) 
	{
		return SceneControl.SCENE_MENU;
	}

	@Override
	public int touchMove(int x, int y) 
	{
		return SceneControl.SCENE_MENU;
	}

	@Override
	public int touchUp(int x, int y) 
	{
		for(int i=0;i<BitmapSource.MENU_NUMBER;++i)
		{
			this.menuImageWidget[i].motionUp(x, y);
		}
		if(this.menuImageWidget[BitmapSource.MENU_STAGE].isFocused())
		{
			return SceneControl.SCENE_GAME_STAGE;
		}
		else if(this.menuImageWidget[BitmapSource.MENU_TIME].isFocused())
		{
			return SceneControl.SCENE_GAME_TIME;
		}
		else if(this.menuImageWidget[BitmapSource.MENU_INFINITY].isFocused())
		{
			return SceneControl.SCENE_GAME_INFINTIY;
		}
		else if(this.menuImageWidget[BitmapSource.MENU_ACHIEVEMENT].isFocused())
		{
			return SceneControl.SCENE_ACHIEVEMENT;
		}
		else if(this.menuImageWidget[BitmapSource.MENU_QUIT].isFocused())
		{
			return SceneControl.SCENE_QUIT;
		}
		return SceneControl.SCENE_MENU;
	}

	@Override
	public int action() 
	{
		for(int i=BitmapSource.MENU_NUMBER-1;i>=0;--i)
		{
			if(this.menuImageWidget[i].position.y < this.menuImageWidgetTargetY[i])
			{
				this.menuImageWidget[i].position.y = this.menuImageWidget[i].position.y + (i<<1);
			}
			else if(this.menuImageWidget[i].position.y > this.menuImageWidgetTargetY[i])
			{
				this.menuImageWidget[i].position.y = this.menuImageWidget[i].position.y - 1;
			}
		}
		return SceneControl.SCENE_MENU;
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
		paint.setARGB(255, 0, 0, 0);
		canvas.drawRect(new Rect(0, 0, Environment.getWindowSize().width, Environment.getWindowSize().height), paint);
		this.titleImageWidget.draw(canvas);
		for(int i=BitmapSource.MENU_NUMBER-1;i>=0;--i)
		{
			this.menuImageWidget[i].draw(canvas);
			if(this.menuImageWidget[i].position.y < this.menuImageWidgetTargetY[i])
			{
				this.menuImageWidget[i].position.y = this.menuImageWidget[i].position.y + (i<<2);
			}
			else if(this.menuImageWidget[i].position.y > this.menuImageWidgetTargetY[i])
			{
				this.menuImageWidget[i].position.y = this.menuImageWidget[i].position.y - 1;
			}
		}
	}
}
