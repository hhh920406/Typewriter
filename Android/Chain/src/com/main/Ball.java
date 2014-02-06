package com.main;

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
	public int chainNumber;
	public int appearTime;
	public boolean ballEnd;
	
	public int windowWidth;
	public int windowHeight;
	
	public void setWindowSize(int width, int height)
	{
		this.windowWidth = width;
		this.windowHeight = height;
	}
	
	public void initBall()
	{
		this.posX = (float)(20 + Math.random() * ( this.windowWidth - 40 ));
		this.posY = (float)(20 + Math.random() * ( this.windowHeight - 40 ));
		double dir = Math.random() * 6.28;
		this.vx = (float) Math.cos(dir) * 5;
		this.vy = (float) Math.sin(dir) * 5;
		this.chainNumber = 0;
		switch((int)Math.floor(Math.random() * 7))
		{
		case 0: this.color = Color.argb(200, 193, 28, 28); break;
		case 1: this.color = Color.argb(200, 255, 127, 39); break;
		case 2: this.color = Color.argb(200, 200, 155, 21); break;
		case 3: this.color = Color.argb(200, 24, 197, 24); break;
		case 4: this.color = Color.argb(200, 36, 185, 177); break;
		case 5: this.color = Color.argb(200, 28, 40, 193); break;
		case 6: this.color = Color.argb(200, 173, 41, 180); break;
		}
		this.appearTime = 100;
		this.ballEnd = false;
	}
	
	public void move()
	{
		if(this.chainNumber == 0)
		{
			this.posX += this.vx;
			this.posY += this.vy;
			if(this.posX < 10 || this.posX + 10 > this.windowWidth)
			{
				vx = -vx;
			}
			if(this.posY < 10 || this.posY + 10 > this.windowHeight)
			{
				vy = -vy;
			}
		}
		else
		{
			if(this.appearTime > 0)
			{
				this.appearTime --;
			}
			else
			{
				this.ballEnd = true;
			}
		}
	}
	
	public void draw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setColor(this.color);
		if(this.chainNumber == 0)
		{
			canvas.drawCircle(this.posX, this.posY, 10.0f,  paint);
		}
		else if(this.appearTime > 0)
		{
			canvas.drawCircle(this.posX, this.posY, 40.0f, paint);
			paint.setColor(Color.argb(200, 255, 255, 255));
			canvas.drawText("+" + this.chainNumber * 100, this.posX - 15, this.posY + 5, paint);
		}
	}
	
	public int hitTest(Ball ball)
	{
		if(this.chainNumber == 0)
		{
			if(ball.chainNumber != 0 && ball.appearTime != 0)
			{
				if(dist(this, ball)<2500)
				{
					this.chainNumber = ball.chainNumber + 1;
					return this.chainNumber * 100;
				}
			}
		}
		return 0;
	}
	
	public float dist(Ball a, Ball b)
	{
		return (a.posX - b.posX) * (a.posX - b.posX) + (a.posY - b.posY) * (a.posY - b.posY);
	}
}
