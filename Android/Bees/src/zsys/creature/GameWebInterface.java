package zsys.creature;

import zsys.geometry.Size;
import android.graphics.Canvas;

public interface GameWebInterface 
{
	public void setBeeNumber(int number);
	public void setSpiderNumber(int number);
	public int getReleasedBeeNumber();
	public int getReleasedSpiderNumber();
	public Size getWebSize();
	public void initialWeb();
	public void createBee(int beeIndex, int beeSpecies, int x, int y);
	public void createSpider(int spiderIndex, int spiderSpecies, int x, int y);
	public void setCreatureRelation(boolean relation[][]);
	public void moveWeb(int x, int y);
	public boolean isAllReleased();
	public boolean touchDown(int x, int y);
	public boolean touchMove(int x, int y);
	public boolean touchUp(int x, int y);
	public void action();
	public void draw(Canvas canvas);
}
