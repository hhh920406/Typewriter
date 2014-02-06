package zsys.geometry;

public class Segment 
{
	private Position startPoint;
	private Position endPoint;
	
	public Segment()
	{
		this.startPoint = new Position();
		this.endPoint = new Position();
	}
	
	public Position getStartPoint()
	{
		return this.startPoint;
	}
	
	public Position getEndPoint()
	{
		return this.endPoint;
	}
}
