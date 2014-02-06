package zsys.creature;

import zsys.geometry.Position;
import zsys.geometry.Size;
import android.graphics.Canvas;

public class AbstractCreature implements CreatureInterface
{
	protected boolean draging;
	protected boolean escaping;
	protected boolean escaped;
	
	protected Position position;
	protected Position offsetPosition;
	protected Size size;
	protected Size stageSize;
	
	public AbstractCreature()
	{
		this.position = new Position(0, 0);
		this.offsetPosition = new Position(0, 0);
		this.size = new Size(60, 60);
		this.stageSize = new Size(320, 480);
	}
	
	@Override
	public Position getPosition() 
	{
		return this.position;
	}

	@Override
	public Position getOffsetPosition() 
	{
		return this.offsetPosition;
	}
	
	@Override
	public Size getSize()
	{
		return this.size;
	}

	@Override
	public Size getStageSize() 
	{
		return this.stageSize;
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.CREATURE_NULL;
	}
	
	@Override
	public int getLeft() 
	{
		return this.position.x - (this.size.width >> 1);
	}

	@Override
	public int getRight() 
	{
		return this.position.x + (this.size.width >> 1);
	}

	@Override
	public int getTop() 
	{
		return this.position.y - (this.size.height >> 1);
	}

	@Override
	public int getBottom() 
	{
		return this.position.y + (this.size.height >> 1);
	}

	@Override
	public boolean isInsideArea(int x, int y) 
	{
		return x >= this.getLeft() && x <= this.getRight() && y >= this.getTop() && y <= this.getBottom();
	}

	@Override
	public boolean isOutsideScene() 
	{
		return this.getRight() < 0 || this.getBottom() < 0 || this.getLeft() > this.stageSize.width || this.getTop() > this.stageSize.height;
	}

	@Override
	public void draw(Canvas canvas) 
	{
		return;
	}

	@Override
	public void action() 
	{
		return;
	}

	@Override
	public void releaseCreature()
	{
		return;
	}

	@Override
	public boolean isDraging() 
	{
		return this.draging;
	}

	@Override
	public boolean isEscaping()
	{
		return this.escaping;
	}
	
	@Override
	public boolean isEscaped() 
	{
		return this.escaped;
	}

	@Override
	public void touchDown(int x, int y) 
	{
		return;
	}

	@Override
	public void touchMove(int x, int y) 
	{
		return;
	}

	@Override
	public void touchUp(int x, int y) 
	{
		return;
	}
}
