package zsys.geometry;

public class Size 
{
	public int width;
	public int height;
	
	public Size()
	{
		this.setSize(0, 0);
	}
	
	public Size(int width, int height)
	{
		this.setSize(width, height);
	}
	
	public void setSize(int width, int height)
	{
		this.width = width;
		this.height = height;
	}
}
