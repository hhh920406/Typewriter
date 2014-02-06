package zsys.geometry;

public class Position 
{
	public int x;
	public int y;
	
	public Position()
	{
		this.setPosition(0, 0);
	}
	
	public Position(int x, int y)
	{
		this.setPosition(x, y);
	}
	
	public void setPosition(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
}
