package zsys.common;

import zsys.creature.CreatureInterface;
import zsys.main.Main;
import android.graphics.Bitmap;

public class BitmapSource 
{
	public static final int BEE_YELLOW 	= 0;
	public static final int BEE_BLUE 		= 1;
	public static final int BEE_GREEN 	= 2;
	public static final int BEE_PURPLE 	= 3;
	public static final int BEE_RED 		= 4;
	public static final int BEE_NUMBER 	= 5;
	public static Bitmap bee[] = new Bitmap[CreatureInterface.BEE_SPECIES_NUMBER];
	public static final int MENU_STAGE 		= 0;
	public static final int MENU_TIME 		= 1;
	public static final int MENU_INFINITY 	= 2;
	public static final int MENU_ACHIEVEMENT = 3;
	public static final int MENU_QUIT 		= 4;
	public static final int MENU_NUMBER 		= 5;
	public static Bitmap menu[] = new Bitmap[Main.MENU_NUMBER];
	public static final int TIME_POINT_10	 = 0;
	public static final int TIME_POINT_20	 = 1;
	public static final int TIME_POINT_30	 = 2;
	public static final int TIME_POINT_40	 = 3;
	public static final int TIME_POINT_50	 = 4;
	public static final int TIME_POINT_NUMBER = 5;
	public static Bitmap time[] = new Bitmap[TIME_POINT_NUMBER];
	public static Bitmap title;
	public static Bitmap about;
}
