package zsys.creature.spider;

import zsys.creature.CreatureInterface;

public class SpiderFactory 
{
	public static CreatureInterface createSpider(int spiderName)
	{
		return new NormalSpider();
	}
}
