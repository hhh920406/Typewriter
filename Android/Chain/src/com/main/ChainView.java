package com.main;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;

public class ChainView extends View
{
	public int windowWidth;
	public int windowHeight;
	public int currentScore;
	public int maxScore;
	public int currentChain;
	public int totalScore;
	public boolean clicked;
	public int appearTime;
	public boolean gameEnd;
	
	private Ball ball[];
	
	private Handler handler;
	private Runnable runnable = new Runnable()
	{
		@Override
		public void run() 
		{
			handler.postDelayed(this, 33);
			invalidate();
		}
	};
	
	public ChainView(Context context) 
	{
		super(context);
		this.setFocusable(true);
	}
	
	public void setWindowSize(int width, int height)
	{
		this.windowWidth = width;
		this.windowHeight = height;
	}
	
	public void start()
	{
		this.maxScore = 0;
		this.totalScore = 0;
		this.initTimer();
		this.ball = new Ball[20];
		for(int i=0;i<20;i++)
		{
			this.ball[i] = new Ball();
			this.ball[i].setWindowSize(this.windowWidth, this.windowHeight);
		}
		this.startGame();
		this.ball[0].chainNumber = 1;
		this.ball[0].color = Color.argb(200, 255, 255, 255);
	}
	
	private void initTimer()
	{
		this.handler = new Handler();
		this.handler.postDelayed(runnable, 33);
	}
	
	private void startGame()
	{
		this.currentScore = 0;
		this.currentChain = 0;
		this.clicked = false;
		for(int i=1;i<20;i++)
		{
			this.ball[i].initBall();
		}
		this.appearTime = 20;
		this.gameEnd = false;
		this.ball[0].ballEnd = false;
	}
	
	@Override
	protected void onDraw(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setColor(Color.BLACK);
		canvas.drawRect(0, 0, this.windowWidth, this.windowHeight, paint);
		paint.setColor(Color.GRAY);
		for(int i=60;i<this.windowWidth;i+=60)
		{
			canvas.drawLine(i, 0, i, this.windowHeight, paint);
		}
		for(int i=60;i<this.windowHeight;i+=60)
		{
			canvas.drawLine(0, i, this.windowWidth, i, paint);
		}
		for(int i=0;i<20;i++)
		{
			this.ball[i].move();
			for(int j=0;j<20;j++)
			{
				if(i!=j)
				{
					int score = this.ball[i].hitTest(this.ball[j]);
					if(score > 0)
					{
						this.currentScore += score;
						this.totalScore += score;
						if(this.currentScore > this.maxScore)
						{
							this.maxScore = this.currentScore;
						}
						if(this.ball[i].chainNumber > this.currentChain)
						{
							this.currentChain = this.ball[i].chainNumber;
						}
					}
				}
			}
			this.ball[i].draw(canvas);
		}
		paint.setColor(Color.WHITE);
		canvas.drawText("The Chain", 10, 20, paint);
		canvas.drawText("Total Score: " + this.totalScore, 10, 40, paint);
		canvas.drawText("MaxScore: " + this.maxScore, 10, 55, paint);
		canvas.drawText("Current Score： " + this.currentScore, 10, 70, paint);
		canvas.drawText("Current Chain: " + this.currentChain, 10, 85, paint);
		canvas.drawText("Zsys Studio 2011", this.windowWidth - 100, this.windowHeight - 15, paint);
		if(this.checkEnd())
		{
			gameEnd = true;
			if(this.appearTime > 0)
			{
				this.appearTime --;
			}
			else
			{
				this.startGame();
			}
		}
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		if(!this.clicked)
		{
			this.clicked = true;
			this.ball[0].posX = event.getX();
			this.ball[0].posY = event.getY();
			this.ball[0].appearTime = 100;
		}
		return super.onTouchEvent(event);
	}
	
	public boolean checkEnd()
	{
		if(gameEnd)
		{
			return true;
		}
		boolean flag = true;
		if(this.clicked)
		{
			for(int i=0;i<20;i++)
			{
				if(ball[i].chainNumber != 0 && !this.ball[i].ballEnd)
				{
					flag = false;
					break;
				}
			}
		}
		else
		{
			flag = false;
		}
		return flag;
	}
}
