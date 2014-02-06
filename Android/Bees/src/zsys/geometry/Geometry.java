package zsys.geometry;

public class Geometry 
{
	public static int pointMultiplication(Position point1, Position point2)
	{
		return point1.x * point2.x + point1.y * point2.y;
	}
	
	public static int crossProduct(Position point1, Position point2, Position point0)
	{
		return (point1.x - point0.x) * (point2.y - point0.y) - (point1.y - point0.y) * (point2.x - point0.x);
	}
	
	public static int dblcmp(int number)
	{
		if(0 == number)
		{
			return 0;
		}
		return number>0?1:-1;
	}
	
	public static boolean isSegmentIntersect(Segment segment1, Segment segment2)
	{
		return dblcmp(crossProduct(segment1.getStartPoint(), segment2.getStartPoint(), segment2.getEndPoint())) *
				dblcmp(crossProduct(segment1.getEndPoint(), segment2.getStartPoint(), segment2.getEndPoint())) < 0 &&
				dblcmp(crossProduct(segment2.getStartPoint(), segment1.getStartPoint(), segment1.getEndPoint())) *
				dblcmp(crossProduct(segment2.getEndPoint(), segment1.getStartPoint(), segment1.getEndPoint())) < 0;
	}
	
	public static Position getInteractPoint(Segment segment1, Segment segment2)
	{
		Position result = new Position();
		double v = crossProduct(segment2.getStartPoint(), segment1.getEndPoint(), segment1.getStartPoint());
		double u = crossProduct(segment2.getEndPoint(), segment1.getEndPoint(), segment1.getStartPoint());
		double w = u - v;
		result.x = (int)((u * segment2.getStartPoint().x - v * segment2.getEndPoint().x) / w);
		result.y = (int)((u * segment2.getStartPoint().y - v * segment2.getEndPoint().y) / w);
		return result;
	}
	
	public static boolean isPointInside(Segment segment[], Position point)
	{
		Segment judgeSegment = new Segment();
		Position temp = new Position();
		int i;
		for(i=0;i<segment.length;++i)
		{
			temp.x = (segment[i].getEndPoint().x - segment[i].getStartPoint().x) >> 1;
			temp.y = (segment[i].getEndPoint().y - segment[i].getStartPoint().y) >> 1;
			if(temp.x != point.x || temp.y != point.y)
			{
				temp.x = temp.x + (temp.x - point.x) * 10000;
				temp.y = temp.y + (temp.y - point.y) * 10000;
				judgeSegment.getStartPoint().x = point.x;
				judgeSegment.getStartPoint().y = point.y;
				judgeSegment.getEndPoint().x = temp.x;
				judgeSegment.getEndPoint().y = temp.y;
				break;
			}
		}
		if(i == segment.length)
		{
			return false;
		}
		Position pointRecord[] = new Position[segment.length];
		int pointNumber = 0;
		for(i=0;i<segment.length;++i)
		{
			if(isSegmentIntersect(judgeSegment, segment[i]))
			{
				temp = getInteractPoint(judgeSegment, segment[i]);
				int j;
				for(j=0;j<pointNumber;++j)
				{
					if(pointRecord[j].x == temp.x && pointRecord[j].y == temp.y)
					{
						break;
					}
				}
				if(j == pointNumber)
				{
					pointRecord[pointNumber] = new Position();
					pointRecord[pointNumber].x = temp.x;
					pointRecord[pointNumber].y = temp.y;
					++ pointNumber;
				}
			}
		}
		return (pointNumber & 1) > 0;
	}
}
