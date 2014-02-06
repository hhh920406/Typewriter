package zsys.common;

import zsys.geometry.Size;

public class Environment 
{
	public static String GAME_VERSION;
	private static Size windowSize = new Size();
	
	public static Size getWindowSize()
	{
		return windowSize;
	}
	
	public static float getScaling()
	{
		return (float)windowSize.width / 320;
	}
}