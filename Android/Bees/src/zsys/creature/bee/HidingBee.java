package zsys.creature.bee;

import zsys.common.BitmapSource;
import zsys.common.GameDataRecord;
import zsys.creature.CreatureInterface;

public class HidingBee extends NormalBee
{
	public HidingBee()
	{
		this.bitmap = BitmapSource.BEE_GREEN;
	}
	
	@Override
	protected void addReleasedBeeNumber()
	{
		GameDataRecord.BEE_RESCUED[CreatureInterface.BEE_HIDING] ++;
	}
	
	@Override
	public int getCreatureType() 
	{
		return CreatureInterface.BEE_HIDING;
	}
}
