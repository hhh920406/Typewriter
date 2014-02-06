package zsys.creature.bee;

import zsys.creature.CreatureInterface;

public class BeeFactory 
{
	public static CreatureInterface createBee(int beeName)
	{
		switch(beeName)
		{
		case CreatureInterface.BEE_DYING: return new DyingBee();
		case CreatureInterface.BEE_HIDING: return new HidingBee();
		case CreatureInterface.BEE_MOVING: return new MovingBee();
		case CreatureInterface.BEE_PASSING: return new PassingBee();
		}
		return new NormalBee();
	}
}
