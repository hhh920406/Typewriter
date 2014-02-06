package com.zhg.consistance;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;

public class Ball 
{
	public int color;
	public float posX;
	public float posY;
	public float vx;
	public float vy; 
	
	public int windowWidth;
	public int windowHeight;
	
	public float radius = 10;
	
	private static int[] r = new int[] {248, 254, 253, 105, 57, 42, 253};
	private static int[] g = new int[] {87, 204, 254, 251, 255, 39, 148};
	private static int[] b = new int[] {87, 82, 118, 115, 255, 221, 255};
	
	public void setWindowSize(int width, int height)
	{
		this.windowWidth = width;
		this.windowHeight = height;
	}
	
	public void init(float x, float y)
	{
		this.posX = x;
		this.posY = y;
		double dir = Math.random() * Math.PI * 2;
		double speed = Math.random() * 4.9 + 0.1;
		this.vx = (float) (Math.cos(dir) * speed);
		this.vy = (float) (Math.sin(dir) * speed);
		int rc = (int)Math.floor(Math.random() * 7);
		this.color = Color.rgb(r[rc], g[rc], b[rc]);
	}
	
	public void move()
	{
		this.posX += this.vx;
		this.posY += this.vy;
		if(this.posX < radius || this.posX + radius > this.windowWidth)
		{
			vx = -vx;
		}
		if(this.posY < radius || this.posY + radius > this.windowHeight)
		{
			vy = -vy;
		}
	}
	
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setColor(this.color);
		canvas.drawCircle(this.posX, this.posY, radius, paint);
	}
	
	public boolean hitTest(Ball ball)
	{
		return dist(this, ball) < radius * radius * 3.6f;
	}
	
	public boolean isNear(Ball ball)
	{
		return dist(this, ball) < radius * radius * 36.0f;
	}
	
	public float dist(Ball a, Ball b)
	{
		return (a.posX - b.posX) * (a.posX - b.posX) + (a.posY - b.posY) * (a.posY - b.posY);
	}
}
