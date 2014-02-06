package zsys.creature;

import android.graphics.Canvas;
import android.graphics.Paint;
import zsys.common.Environment;
import zsys.creature.bee.BeeFactory;
import zsys.creature.spider.SpiderFactory;
import zsys.geometry.Geometry;
import zsys.geometry.Size;
import zsys.geometry.Position;
import zsys.geometry.Segment;

public class NormalGameWeb implements GameWebInterface
{
	protected int beeNumber;
	protected int spiderNumber;
	protected int creatureNumber;
	protected CreatureInterface creatureArray[];
	protected boolean creatureRelation[][];
	protected boolean actuallyCreatureRelation[][];
	protected int creatureDepth[];
	protected boolean releaseTempCreature[];
	protected int creatureStack[];
	protected int creatureStackTop;

	protected Position gamePosition;
	protected Size webSize;
	
	public NormalGameWeb()
	{
		this.clearData();
	}
	
	public void clearData()
	{
		this.beeNumber = 0;
		this.spiderNumber = 0;
		this.creatureArray = null;
		this.creatureRelation = null;
		this.actuallyCreatureRelation = null;
		this.creatureDepth = null;
		this.releaseTempCreature = null;
		this.gamePosition = new Position();
		this.webSize = new Size();
	}
	
	public void setBeeNumber(int number)
	{
		this.beeNumber = number;
		this.creatureNumber = this.beeNumber + this.spiderNumber;
	}
	
	public void setSpiderNumber(int number)
	{
		this.spiderNumber = number;
		this.creatureNumber = this.beeNumber + this.spiderNumber;
	}
	
	public Size getWebSize()
	{
		return this.webSize;
	}
	
	public void initialWeb()
	{
		this.creatureNumber = this.beeNumber + this.spiderNumber;
		this.creatureArray = new CreatureInterface[this.creatureNumber];
		this.creatureRelation = new boolean[this.creatureNumber][this.creatureNumber];
		this.actuallyCreatureRelation = new boolean[this.creatureNumber][this.creatureNumber];
		this.creatureDepth = new int[this.creatureNumber];
		this.releaseTempCreature = new boolean[this.creatureNumber];
		this.creatureStack = new int[this.creatureNumber];
		
		this.gamePosition.setPosition(0, 0);
		this.webSize.width = Math.max(Environment.getWindowSize().width, this.webSize.width);
		this.webSize.height = Math.max(Environment.getWindowSize().height, this.webSize.height);
	}
	
	public void createBee(int beeIndex, int beeSpecies, int x, int y)
	{
		this.creatureArray[beeIndex] = BeeFactory.createBee(beeSpecies);
		this.creatureArray[beeIndex].getPosition().setPosition(x, y);
		this.creatureArray[beeIndex].getStageSize().setSize(this.webSize.width, this.webSize.height);
	}
	
	public void createSpider(int spiderIndex, int spiderSpecies, int x, int y)
	{
		this.creatureArray[spiderIndex + this.beeNumber] = SpiderFactory.createSpider(spiderSpecies);
		this.creatureArray[spiderIndex + this.beeNumber].getPosition().setPosition(x, y);
		this.creatureArray[spiderIndex + this.beeNumber].getStageSize().setSize(this.webSize.width, this.webSize.height);
	}
	
	public void setCreatureRelation(boolean relation[][])
	{
		for(int i=0;i<this.creatureNumber;++i)
		{
			this.creatureRelation[i][i] = false;
			for(int j=i+1;j<this.creatureNumber;++j)
			{
				this.creatureRelation[i][j] = this.creatureRelation[j][i] = relation[i][j];
				if(this.creatureArray[i].getCreatureType() == CreatureInterface.BEE_PASSING || this.creatureArray[j].getCreatureType() == CreatureInterface.BEE_PASSING)
				{
					this.creatureRelation[i][j] = false;
				}
			}
		}
	}
	
	protected void calculateActuallyCreatureRelation()
	{
		int segmentNumber = 0;;
		for(int i=0;i<this.creatureNumber;++i)
		{
			this.actuallyCreatureRelation[i][i] = false;
			for(int j=i+1;j<this.creatureNumber;++j)
			{
				this.actuallyCreatureRelation[i][j] = this.actuallyCreatureRelation[j][i] = this.creatureRelation[i][j];
				if(this.creatureRelation[i][j])
				{
					segmentNumber = segmentNumber + 1;
				}
			}
		}
		Segment segment[] = new Segment[segmentNumber];
		Position segmentIndex[] = new Position[segmentNumber];
		segmentNumber = 0;
		for(int i=0;i<this.creatureNumber;++i)
		{
			for(int j=i+1;j<this.creatureNumber;++j)
			{
				if(this.creatureRelation[i][j])
				{
					segment[segmentNumber] = new Segment();
					segment[segmentNumber].getStartPoint().setPosition(this.creatureArray[i].getPosition().x, this.creatureArray[i].getPosition().y);
					segment[segmentNumber].getEndPoint().setPosition(this.creatureArray[j].getPosition().x, this.creatureArray[j].getPosition().y);
					segmentIndex[segmentNumber] = new Position(i, j);
					segmentNumber = segmentNumber + 1;
				}
			}
		}
		for(int i=0;i<segmentNumber;++i)
		{
			for(int j=i+1;j<segmentNumber;++j)
			{
				if(Geometry.isSegmentIntersect(segment[i], segment[j]))
				{
					this.actuallyCreatureRelation[segmentIndex[i].x][segmentIndex[i].y] = false;
					this.actuallyCreatureRelation[segmentIndex[i].y][segmentIndex[i].x] = false;
					this.actuallyCreatureRelation[segmentIndex[j].x][segmentIndex[j].y] = false;
					this.actuallyCreatureRelation[segmentIndex[j].y][segmentIndex[j].x] = false;
				}
			}
		}
	}
	
	protected void releaseCreature(int creatureIndex)
	{
		for(int i=0;i<this.creatureNumber;++i)
		{
			this.creatureRelation[i][creatureIndex] = this.creatureRelation[creatureIndex][i] = false;
			this.actuallyCreatureRelation[i][creatureIndex] = this.actuallyCreatureRelation[creatureIndex][i] = false;
		}
		this.creatureArray[creatureIndex].releaseCreature();
	}
	
	protected boolean tryToReleaseCreature()
	{
		int connectionNumber;
		boolean releasedCreature = false;
		for(int i=0;i<this.creatureNumber;++i)
		{
			this.releaseTempCreature[i] = false;
			connectionNumber = 0;
			for(int j=0;j<this.creatureNumber;++j)
			{
				if(this.creatureRelation[i][j])
				{
					connectionNumber = connectionNumber + 1;
				}
			}
			if(connectionNumber < 2 && !this.creatureArray[i].isEscaping())
			{
				this.releaseCreature(i);
				releasedCreature = true;
			}
		}
		for(int i=0;i<this.creatureNumber;++i)
		{
			for(int j=0;j<this.creatureNumber;++j)
			{
				this.creatureDepth[j] = -1;
			}
			this.creatureDepth[i] = 0;
			if(!this.creatureArray[i].isEscaping())
			{
				this.creatureStackTop = 0;
				this.findLoop(i, 0);
			}
		}
		for(int i=0;i<this.creatureNumber;++i)
		{
			if(this.releaseTempCreature[i])
			{
				this.releaseCreature(i);
				releasedCreature = true;
			}
		}
		return releasedCreature;
	}
	
	protected boolean findLoop(int creatureIndex, int depth)
	{
		this.creatureDepth[creatureIndex] = depth;
		this.creatureStack[this.creatureStackTop ++] = creatureIndex;
		for(int i=0;i<this.creatureNumber;++i)
		{
			if(!this.creatureArray[i].isEscaping() && this.actuallyCreatureRelation[creatureIndex][i])
			{
				if(this.creatureDepth[i] != -1)
				{
					if(depth - this.creatureDepth[i] > 1)
					{
						return this.checkLoop2(this.creatureDepth[i], depth);
					}
				}
				else
				{
					if(this.findLoop(i, depth + 1))
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	
	protected boolean checkLoop2(int start, int end)
	{
		int count = 0;
		for(int i=0;i<this.creatureStackTop;++i)
		{
			if(this.creatureDepth[this.creatureStack[i]] >= start && this.creatureDepth[this.creatureStack[i]] <= end)
			{
				++ count;
			}
		}
		int creatureLoop[] = new int[count];
		count = 0;
		for(int i=0;i<this.creatureStackTop;++i)
		{
			if(this.creatureDepth[this.creatureStack[i]] >= start && this.creatureDepth[this.creatureStack[i]] <= end)
			{
				creatureLoop[count ++] = this.creatureStack[i];
			}
		}
		for(int i=0;i<count;++i)
		{
			for(int j=i+2;j<(i>0?count:count-1);++j)
			{
				if(this.creatureRelation[creatureLoop[i]][creatureLoop[j]])
				{
					return false;
				}
			}
		}
		for(int i=0;i<count;++i)
		{
			this.releaseTempCreature[creatureLoop[i]] = true;
		}
		return true;
	}
	
	protected void checkLoop(int start, int end)
	{
		int segmentNumber = 0;
		for(int i=0;i<this.creatureStackTop;++i)
		{
			if(this.creatureDepth[this.creatureStack[i]] >= start && this.creatureDepth[this.creatureStack[i]] <= end)
			{
				++ segmentNumber;
			}
		}
		Segment polygon[] = new Segment[segmentNumber];
		int i;
		for(i=0;i<this.creatureStackTop;++i)
		{
			if(this.creatureDepth[this.creatureStack[i]] >= start)
			{
				break;
			}
		}
		for(int j=1;j<segmentNumber;++j)
		{
			polygon[j] = new Segment();
			polygon[j].getStartPoint().x = this.creatureArray[this.creatureStack[i + j - 1]].getPosition().x;
			polygon[j].getStartPoint().x = this.creatureArray[this.creatureStack[i + j - 1]].getPosition().y;
			polygon[j].getEndPoint().y = this.creatureArray[this.creatureStack[i + j]].getPosition().x;
			polygon[j].getEndPoint().y = this.creatureArray[this.creatureStack[i + j]].getPosition().y;
		}
		polygon[0] = new Segment();
		polygon[0].getStartPoint().x = polygon[segmentNumber - 1].getEndPoint().x;
		polygon[0].getStartPoint().y = polygon[segmentNumber - 1].getEndPoint().y;
		polygon[0].getEndPoint().x = polygon[1].getStartPoint().x;
		polygon[0].getEndPoint().y = polygon[1].getStartPoint().y;
		for(i=0;i<this.beeNumber;++i)
		{
			if(!this.creatureArray[i].isEscaping())
			{
				int j;
				for(j=0;j<this.creatureStackTop;++j)
				{
					if(this.creatureDepth[this.creatureStack[j]] >= start && this.creatureDepth[this.creatureStack[j]] <= end)
					{
						if(i == this.creatureStack[j])
						{
							break;
						}
					}
				}
				if(j == this.creatureStackTop)
				{
					if(Geometry.isPointInside(polygon, this.creatureArray[i].getPosition()))
					{
						return;
					}
				}
			}
		}
		for(i=0;i<this.creatureStackTop;++i)
		{
			if(this.creatureDepth[this.creatureStack[i]] >= start && this.creatureDepth[this.creatureStack[i]] <= end)
			{
				this.releaseTempCreature[this.creatureStack[i]] = true;
			}
		}
	}
	
	public void moveWeb(int x, int y)
	{
		this.gamePosition.setPosition(this.gamePosition.x - x, this.gamePosition.y - y);
		if(this.gamePosition.x < 0)
		{
			this.gamePosition.x = 0;
		}
		else if(this.gamePosition.x > this.webSize.width - Environment.getWindowSize().width)
		{
			this.gamePosition.x = this.webSize.width - Environment.getWindowSize().width;
		}
		if(this.gamePosition.y < 0)
		{
			this.gamePosition.y = 0;
		}
		else if(this.gamePosition.y > this.webSize.height - Environment.getWindowSize().height)
		{
			this.gamePosition.y = this.webSize.height - Environment.getWindowSize().height;
		}
	}
	
	public boolean isAllReleased()
	{
		for(int i=0;i<this.creatureNumber;++i)
		{
			if(!this.creatureArray[i].isEscaped())
			{
				return false;
			}
		}
		return true;
	}
	
	public boolean touchDown(int x, int y)
	{
		for(int i=0;i<this.beeNumber;++i)
		{
			this.creatureArray[i].touchDown(x + this.gamePosition.x, y + this.gamePosition.y);
			if(this.creatureArray[i].isDraging())
			{
				return true;
			}
		}
		return false;
	}
	
	public boolean touchMove(int x, int y)
	{
		for(int i=0;i<this.beeNumber;++i)
		{
			this.creatureArray[i].touchMove(x + this.gamePosition.x, y + this.gamePosition.y);
			if(this.creatureArray[i].isDraging())
			{
				return true;
			}
		}
		return false;
	}
	
	public boolean touchUp(int x, int y)
	{
		this.calculateActuallyCreatureRelation();
		while(this.tryToReleaseCreature())
		{
			this.calculateActuallyCreatureRelation();
		}
		for(int i=0;i<this.beeNumber;++i)
		{
			this.creatureArray[i].touchUp(x + this.gamePosition.x, y + this.gamePosition.y);
		}
		return false;
	}
	
	public void action()
	{
		if(this.creatureArray != null)
		{
			for(int i=0;i<this.creatureNumber;++i)
			{
				if(this.creatureArray[i] != null)
				{
					this.creatureArray[i].action();
				}
			}
		}
	}
	
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true); 
		paint.setStrokeWidth(2.0f);
		for(int i=0;i<this.creatureNumber;++i)
		{
			for(int j=i+1;j<this.creatureNumber;++j)
			{
				if(this.creatureRelation[i][j])
				{
					if(CreatureInterface.BEE_HIDING == this.creatureArray[i].getCreatureType())
					{
						continue;
					}
					if(CreatureInterface.BEE_HIDING == this.creatureArray[j].getCreatureType())
					{
						continue;
					}
					if(this.actuallyCreatureRelation[i][j])
					{
						paint.setARGB(100, 200, 200, 200);
					}
					else
					{
						paint.setARGB(200, 200, 200, 200);
					}
					canvas.drawLine(
							this.creatureArray[i].getPosition().x - this.gamePosition.x, 
							this.creatureArray[i].getPosition().y - this.gamePosition.y,
							this.creatureArray[j].getPosition().x - this.gamePosition.x, 
							this.creatureArray[j].getPosition().y - this.gamePosition.y, paint);
				}
			}
		}
		for(int i=0;i<this.beeNumber;++i)
		{
			this.creatureArray[i].getOffsetPosition().setPosition(this.gamePosition.x, this.gamePosition.y);
			this.creatureArray[i].draw(canvas);
		}
		for(int j=0;j<this.spiderNumber;++j)
		{
			this.creatureArray[j + this.beeNumber].getOffsetPosition().setPosition(this.gamePosition.x, this.gamePosition.y);
			this.creatureArray[j + this.beeNumber].draw(canvas);
		}
	}

	@Override
	public int getReleasedBeeNumber() 
	{
		int count = 0;
		for(int i=0;i<this.beeNumber;++i)
		{
			if(this.creatureArray[i].isEscaped())
			{
				++ count;
			}
		}
		return count;
	}

	@Override
	public int getReleasedSpiderNumber() 
	{
		int count = 0;
		for(int i=0;i<this.spiderNumber;++i)
		{
			if(this.creatureArray[i + this.beeNumber].isEscaped())
			{
				++ count;
			}
		}
		return count;
	}
}
