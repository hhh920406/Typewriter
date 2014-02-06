package zsys.creature;

import zsys.geometry.Position;
import zsys.geometry.Size;
import android.graphics.Canvas;

public interface CreatureInterface 
{
	public static final int CREATURE_NULL = -1;
	
	public static final int BEE_NORMAL = 0;
	public static final int BEE_DYING = 1;
	public static final int BEE_HIDING = 2;
	public static final int BEE_MOVING = 3;
	public static final int BEE_PASSING = 4;
	public static final int BEE_SPECIES_NUMBER = 5;

	public static final int SPIDER_NORMAL = 5;
	public static final int SPIDER_SPECIES_NUMBER = 1;
	
	public int getCreatureType();
	public void releaseCreature();
	public boolean isDraging();
	public boolean isEscaping();
	public boolean isEscaped();
	public Position getPosition();
	public Position getOffsetPosition();
	public Size getSize();
	public Size getStageSize();
	public int getLeft();
	public int getRight();
	public int getTop();
	public int getBottom();
	public void action();
	public void touchDown(int x, int y);
	public void touchMove(int x, int y);
	public void touchUp(int x, int y);
	public void draw(Canvas canvas);
	public boolean isInsideArea(int x, int y);
	public boolean isOutsideScene();
}
