package zsys.scene;

import zsys.common.GameDataRecord;
import zsys.common.Environment;
import zsys.creature.CreatureInterface;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Align;

public class AchievementScene implements SceneInterface
{
	@Override
	public int touchDown(int x, int y)
	{
		return SceneControl.SCENE_ACHIEVEMENT;
	}

	@Override
	public int touchMove(int x, int y)
	{
		return SceneControl.SCENE_ACHIEVEMENT;
	}

	@Override
	public int touchUp(int x, int y)
	{
		return SceneControl.SCENE_LONGTERM;
	}

	@Override
	public int action()
	{
		return SceneControl.SCENE_ACHIEVEMENT;
	}

	@Override
	public void refresh()
	{
		return;
	}
	@Override
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(255, 255, 255, 255);
		canvas.drawRect(0.0f, 0.0f, (float)Environment.getWindowSize().width, (float)Environment.getWindowSize().height, paint);

		paint.setARGB(255, 0, 0, 0);
		paint.setTextAlign(Align.CENTER);
		paint.setTextSize(20 * Environment.getScaling());
		canvas.drawText("混乱蜜蜂游戏数据统计", Environment.getWindowSize().width >> 1, 30, paint);

		paint.setTextAlign(Align.LEFT);
		paint.setTextSize(15 * Environment.getScaling());
		canvas.drawText("打开游戏次数：" + GameDataRecord.TIME_OPEN_APP, 40, 60, paint);
		canvas.drawText("打开关卡模式次数：" + GameDataRecord.TIME_OPEN_STAGE_MODE, 40, 80, paint);
		canvas.drawText("打开时间模式次数：" + GameDataRecord.TIME_OPEN_TIME_MODE, 40, 100, paint);
		canvas.drawText("打开无限模式次数：" + GameDataRecord.TIME_OPEN_INFINITY_MODE, 40, 120, paint);
		canvas.drawText("最大关卡模式网数：" + GameDataRecord.STAGE_MODE_MAX_STAGE, 40, 150, paint);
		canvas.drawText("最大时间模式网数：" + GameDataRecord.TIME_MODE_MAX_STAGE, 40, 170, paint);
		canvas.drawText("最大无限模式网数：" + GameDataRecord.INFINTIY_MODE_MAX_STAGE, 40, 190, paint);
		canvas.drawText("时间模式最大时间点数：" + GameDataRecord.TIME_MODE_MAX_TIME_POINT, 40, 210, paint);
		canvas.drawText("解救普通蜜蜂数量：" + GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_NORMAL], 40, 240, paint);
		canvas.drawText("解救濒死蜜蜂数量：" + GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_DYING], 40, 260, paint);
		canvas.drawText("解救挣扎蜜蜂数量：" + GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_MOVING], 40, 280, paint);
		canvas.drawText("解救藏匿蜜蜂数量：" + GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_HIDING], 40, 300, paint);
		canvas.drawText("解救酱油蜜蜂数量：" + GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_PASSING], 40, 320, paint);
		int day = GameDataRecord.TIME_RUN_GAME / 86400;
		int hour = GameDataRecord.TIME_RUN_GAME / 3600 % 24;
		int minute = GameDataRecord.TIME_RUN_GAME / 60 % 60;
		int second = GameDataRecord.TIME_RUN_GAME % 60;
		canvas.drawText("游戏运行时间：" + day + "天" + hour + "小时" + minute + "分" + second + "秒", 40, 350, paint);
	}
}
