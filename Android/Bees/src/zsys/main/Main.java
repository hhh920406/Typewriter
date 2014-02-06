package zsys.main;

import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.common.Environment;
import zsys.creature.CreatureInterface;
import zsys.scene.SceneControl;

import com.main.R;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.Display;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;

public class Main extends Activity 
{
	SceneControl sceneControl;
	
	private static final int MENU_MENU = Menu.FIRST;
	private static final int MENU_REFRESH = Menu.FIRST + 1;
	private static final int MENU_HELP = Menu.FIRST + 2;
	private static final int MENU_ABOUT = Menu.FIRST + 3;
	private static final int MENU_QUIT = Menu.FIRST + 4;
	public static final int MENU_NUMBER = 5;
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        this.getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
        this.loadGameDataRecord();
        GameDataRecord.TIME_OPEN_APP ++;
        this.loadEnvironment();
        this.loadBitmapSource();
        this.sceneControl = new SceneControl(this);
        this.sceneControl.sendMain(this);
        this.setContentView(this.sceneControl);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
    	menu.add(0, MENU_MENU, 0, "返回主菜单");
    	menu.add(0, MENU_REFRESH, 0, "重新开局");
    	menu.add(1, MENU_HELP, 0, "帮助");
    	menu.add(2, MENU_ABOUT, 0, "关于");
    	menu.add(3, MENU_QUIT, 0, "退出游戏");
    	return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem menuItem)
    {
    	switch(menuItem.getItemId())
    	{
    	case MENU_MENU:
    		this.sceneControl.setScene(SceneControl.SCENE_MENU);
    		break;
    	case MENU_REFRESH:
    		this.sceneControl.refresh();
    		break;
    	case MENU_HELP:
    		this.sceneControl.setScene(SceneControl.SCENE_HELP);
    		break;
    	case MENU_ABOUT:
    		this.sceneControl.setScene(SceneControl.SCENE_ABOUT);
    		break;
    	case MENU_QUIT:
    		this.sceneControl.setScene(SceneControl.SCENE_QUIT);
    		break;
    	}
    	return super.onOptionsItemSelected(menuItem);
    }
    
    private void loadEnvironment()
    {
        WindowManager windowManager = getWindowManager();
        Display display = windowManager.getDefaultDisplay();
        Environment.getWindowSize().setSize(display.getWidth(), display.getHeight());
		try 
		{
			PackageInfo info;
			info = this.getPackageManager().getPackageInfo(this.getPackageName(), 0);
			Environment.GAME_VERSION = info.versionName;
		} 
		catch (NameNotFoundException e) 
		{
			Environment.GAME_VERSION = "无法获得";
			e.printStackTrace();
		}
    }
    
    private void loadBitmapSource()
    {
        BitmapSource.bee[BitmapSource.BEE_YELLOW] 	= BitmapFactory.decodeResource(this.getResources(), R.drawable.bees_yellow);
        BitmapSource.bee[BitmapSource.BEE_BLUE] 	= BitmapFactory.decodeResource(this.getResources(), R.drawable.bees_blue);
        BitmapSource.bee[BitmapSource.BEE_GREEN] 	= BitmapFactory.decodeResource(this.getResources(), R.drawable.bees_green);
        BitmapSource.bee[BitmapSource.BEE_PURPLE] 	= BitmapFactory.decodeResource(this.getResources(), R.drawable.bees_purple);
        BitmapSource.bee[BitmapSource.BEE_RED] 		= BitmapFactory.decodeResource(this.getResources(), R.drawable.bees_red);

        BitmapSource.title = BitmapFactory.decodeResource(this.getResources(), R.drawable.title);
        BitmapSource.about = BitmapFactory.decodeResource(this.getResources(), R.drawable.about);
        
        BitmapSource.menu[BitmapSource.MENU_STAGE] 			= BitmapFactory.decodeResource(this.getResources(), R.drawable.menu_stage);
        BitmapSource.menu[BitmapSource.MENU_TIME] 			= BitmapFactory.decodeResource(this.getResources(), R.drawable.menu_time);
        BitmapSource.menu[BitmapSource.MENU_INFINITY] 		= BitmapFactory.decodeResource(this.getResources(), R.drawable.menu_infinity);
        BitmapSource.menu[BitmapSource.MENU_ACHIEVEMENT] 	= BitmapFactory.decodeResource(this.getResources(), R.drawable.menu_achieve);
        BitmapSource.menu[BitmapSource.MENU_QUIT] 			= BitmapFactory.decodeResource(this.getResources(), R.drawable.menu_quit);
        
        BitmapSource.time[BitmapSource.TIME_POINT_10] = BitmapFactory.decodeResource(this.getResources(), R.drawable.time_10);
        BitmapSource.time[BitmapSource.TIME_POINT_20] = BitmapFactory.decodeResource(this.getResources(), R.drawable.time_20);
        BitmapSource.time[BitmapSource.TIME_POINT_30] = BitmapFactory.decodeResource(this.getResources(), R.drawable.time_30);
        BitmapSource.time[BitmapSource.TIME_POINT_40] = BitmapFactory.decodeResource(this.getResources(), R.drawable.time_40);
        BitmapSource.time[BitmapSource.TIME_POINT_50] = BitmapFactory.decodeResource(this.getResources(), R.drawable.time_50);
    }
    
    public void loadGameDataRecord()
    {
    	SharedPreferences sharedPreferences;
    	
    	sharedPreferences = this.getSharedPreferences("混乱蜜蜂", Context.MODE_WORLD_READABLE);
    	GameDataRecord.TIME_OPEN_APP = sharedPreferences.getInt("打开游戏次数", 1);
    	GameDataRecord.TIME_OPEN_STAGE_MODE = sharedPreferences.getInt("打开关卡模式次数", 1);
    	GameDataRecord.TIME_OPEN_TIME_MODE = sharedPreferences.getInt("打开时间模式次数", 1);
    	GameDataRecord.TIME_OPEN_INFINITY_MODE = sharedPreferences.getInt("打开无限模式次数", 1);
    	GameDataRecord.TIME_RUN_GAME = sharedPreferences.getInt("游戏运行时间", 0);

    	sharedPreferences = this.getSharedPreferences("关卡模式", Context.MODE_WORLD_READABLE);
    	GameDataRecord.STAGE_MODE_MAX_STAGE = sharedPreferences.getInt("关卡模式最大关卡数", 0);
    	
    	sharedPreferences = this.getSharedPreferences("时间模式", Context.MODE_WORLD_READABLE);
    	GameDataRecord.TIME_MODE_MAX_TIME_POINT = sharedPreferences.getInt("时间模式最大时间点数Reset1", 0);
    	GameDataRecord.TIME_MODE_MAX_STAGE = sharedPreferences.getInt("时间模式最大关卡数Reset1", 0);
    	
    	sharedPreferences = this.getSharedPreferences("无限模式", Context.MODE_WORLD_READABLE);
    	GameDataRecord.INFINTIY_MODE_MAX_STAGE = sharedPreferences.getInt("关卡数目", 1);
    	
    	sharedPreferences = this.getSharedPreferences("蜜蜂信息", Context.MODE_WORLD_READABLE);
    	GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_NORMAL] = sharedPreferences.getInt("普通蜜蜂数量", 0);
    	GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_DYING] = sharedPreferences.getInt("濒死蜜蜂数量", 0);
    	GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_MOVING] = sharedPreferences.getInt("挣扎蜜蜂数量", 0);
    	GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_HIDING] = sharedPreferences.getInt("藏匿蜜蜂数量", 0);
    	GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_PASSING] = sharedPreferences.getInt("酱油蜜蜂数量", 0);
    }
    
    public void saveGameDataRecord()
    {
    	SharedPreferences sharedPreferences;
    	Editor edit;
    	
    	sharedPreferences = this.getSharedPreferences("混乱蜜蜂", Context.MODE_WORLD_WRITEABLE);
        edit = sharedPreferences.edit();
        edit.putInt("打开游戏次数", GameDataRecord.TIME_OPEN_APP);
        edit.putInt("打开关卡模式次数", GameDataRecord.TIME_OPEN_STAGE_MODE);
        edit.putInt("打开时间模式次数", GameDataRecord.TIME_OPEN_TIME_MODE);
        edit.putInt("打开无限模式次数", GameDataRecord.TIME_OPEN_INFINITY_MODE);
        edit.putInt("游戏运行时间", GameDataRecord.TIME_RUN_GAME);
        edit.commit();
    	
    	sharedPreferences = this.getSharedPreferences("关卡模式", Context.MODE_WORLD_WRITEABLE);
        edit = sharedPreferences.edit();
        edit.putInt("关卡模式最大关卡数", GameDataRecord.STAGE_MODE_MAX_STAGE);
        edit.commit();
    	
        sharedPreferences = this.getSharedPreferences("时间模式", Context.MODE_WORLD_WRITEABLE);
        edit = sharedPreferences.edit();
        edit.putInt("时间模式最大时间点数Reset1", GameDataRecord.TIME_MODE_MAX_TIME_POINT);
        edit.putInt("时间模式最大关卡数Reset1", GameDataRecord.TIME_MODE_MAX_STAGE);
        edit.commit();
        
    	sharedPreferences = this.getSharedPreferences("无限模式", Context.MODE_WORLD_WRITEABLE);
        edit = sharedPreferences.edit();
        edit.putInt("关卡数目", GameDataRecord.INFINTIY_MODE_MAX_STAGE);
        edit.commit();
        
        sharedPreferences = this.getSharedPreferences("蜜蜂信息", Context.MODE_WORLD_WRITEABLE);
        edit = sharedPreferences.edit();
        edit.putInt("普通蜜蜂数量", GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_NORMAL]);
        edit.putInt("濒死蜜蜂数量", GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_DYING]);
        edit.putInt("挣扎蜜蜂数量", GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_MOVING]);
        edit.putInt("藏匿蜜蜂数量", GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_HIDING]);
        edit.putInt("酱油蜜蜂数量", GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_PASSING]);
        edit.commit();
    }
}