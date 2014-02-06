package zsys.creature.bee;

import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;

public class DyingBee extends NormalBee
{
	public DyingBee()
	{
		this.bitmap = BitmapSource.BEE_BLUE;
	}
	
	@Override
	protected void addReleasedBeeNumber()
	{
		GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_DYING] ++;
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.BEE_DYING;
	}
	
	public void touchDown(int x, int y)
	{
		return;
	}
}
