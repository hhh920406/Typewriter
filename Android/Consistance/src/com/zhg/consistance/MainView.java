package com.zhg.consistance;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;

@SuppressLint("DrawAllocation")
public class MainView extends View
{
	public int windowWidth;
	public int windowHeight;
	
	private int currentBallNum = 1;
	public int maxBallNum = 1;
	public int totalBallNum = 0;
	
	private long currentSeconds = 0;
	public long maxSeconds = 0;
	public long totalSeconds = 0;
	
	private long grazeScore = 0;
	public long maxGrazeScore = 0;
	public long totalGrazeScore = 0;
	
	private Ball[] balls = new Ball[128];
	private Ball player = new Ball();
	
	private float ox = 0.0f;
	private float oy = 0.0f;
	
	private int bigIndex = 0;
	
	private MainActivity act;
	
	public void setAct(MainActivity acti)
	{
		act = acti;
	}
	
	private enum State 
	{
		State_Wait,
		State_Moving
	};
	
	private State state = State.State_Wait;
	
	public MainView(Context context) 
	{
		super(context);
		this.setFocusable(true);
		for (int i = 0; i < 128; ++i)
		{
			balls[i] = new Ball();
		}
		this.initTimer();
	}
	
	public void setWindowSize(int width, int height)
	{
		this.windowWidth = width;
		this.windowHeight = height;
		for (int i = 0; i < 128; ++i)
		{
			balls[i].setWindowSize(width, height);
		}
		this.restart();
	}
	
	private void restart()
	{
		currentBallNum = 1;
		currentSeconds = 0;
		grazeScore = 0;
		balls[0].init(windowWidth / 2.0f, windowHeight / 4.0f);
		balls[0].vx = 0.0f;
		balls[0].vy = 0.0f;
		player.init(windowWidth / 2.0f, windowHeight * 3.0f / 4.0f);
		player.color = Color.rgb(255, 255, 255);
		balls[bigIndex].radius = 10;
	}
	
	private void addBall()
	{
		if (currentBallNum < 128)
		{
			balls[currentBallNum].init(windowWidth / 2.0f, windowHeight / 4.0f);
			if (++currentBallNum > maxBallNum)
			{
				maxBallNum = currentBallNum;
			}
			++totalBallNum;
		}
	}
	
	private void move()
	{
		if (state == State.State_Moving)
		{
			if (currentSeconds == 0)
			{
				for (int i = 0; i < 10; ++i)
				{
					this.addBall();
				}
			}
			++totalSeconds;
			if (++currentSeconds > maxSeconds)
			{
				maxSeconds = currentSeconds;
			}
			if (currentSeconds % 70 == 0)
			{
				addBall();
			}
			for (int i = 0; i < currentBallNum; ++i)
			{
				balls[i].move();
				if (player.hitTest(balls[i]))
				{
					act.save();
					state = State.State_Wait;
					break;
				}
				if (i > 0 && player.isNear(balls[i]))
				{
					grazeScore += 100;
					totalGrazeScore += 100;
					if (grazeScore > maxGrazeScore)
					{
						maxGrazeScore = grazeScore;
					}
				}
			}
		}
		else
		{
			balls[bigIndex].radius = 10.0f;
			if (++bigIndex >= currentBallNum)
			{
				bigIndex = 0;
			}
			balls[bigIndex].radius = 11.0f;
		}
	}
	
	@Override
	protected void onDraw(Canvas canvas)
	{
		move();
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setColor(Color.BLACK);
		canvas.drawRect(0, 0, this.windowWidth, this.windowHeight, paint);
		for (int i = 0; i < currentBallNum; ++i)
		{
			balls[i].draw(canvas);
		}
		player.draw(canvas);
		paint.setTextSize(20);
		paint.setColor(Color.WHITE);
		canvas.drawText("躲避弹幕", 10, 30, paint);
		canvas.drawText("当前子弹数目: " + this.currentBallNum, 10, 70, paint);
		canvas.drawText("最多子弹数目：" + this.maxBallNum, 10, 100, paint);
		canvas.drawText("累计子弹数目：" + this.totalBallNum, 10, 130, paint);
		canvas.drawText("当前坚持时间：" + this.currentSeconds, 10, 170, paint);
		canvas.drawText("最长坚持时间：" + this.maxSeconds, 10, 200, paint);
		canvas.drawText("累计坚持时间：" + this.totalSeconds, 10, 230, paint);
		canvas.drawText("当前擦弹分数：" + this.grazeScore, 10, 270, paint);
		canvas.drawText("最高擦弹分数：" + this.maxGrazeScore, 10, 300, paint);
		canvas.drawText("累计擦弹分数：" + this.totalGrazeScore, 10, 330, paint);
		if (state == State.State_Wait)
		{
			canvas.drawText("拖动白球躲避子弹", 10, windowHeight - 30, paint);
		}
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		float x = event.getX();
		float y = event.getY();
		int action = event.getAction();
		if (action == MotionEvent.ACTION_DOWN)
		{
			if (this.state == State.State_Wait)
			{
				this.state = State.State_Moving;
				restart();
			}
		}
		else if (action == MotionEvent.ACTION_MOVE)
		{
			if (this.state == State.State_Moving)
			{
				float tx = x - ox;
				float ty = y - oy;
				player.posX += tx;
				player.posY += ty;
				if (player.posX < player.radius)
				{
					player.posX = player.radius;
				}
				else if (player.posX > windowWidth - player.radius)
				{
					player.posX = windowWidth - player.radius;
				}
				if (player.posY < player.radius)
				{
					player.posY = player.radius;
				}
				else if (player.posY > windowHeight - player.radius)
				{
					player.posY = windowHeight - player.radius;
				}
			}
		}
		ox = x;
		oy = y;
		return true;
	}

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
	
	private void initTimer()
	{
		this.handler = new Handler();
		this.handler.postDelayed(runnable, 33);
	}
}
