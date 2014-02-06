package com.display;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.*;

public class DisplayView extends View
{
	public double x[] = new double[300];
	public double y[] = new double[300];
	public double z[][] = new double[300][300];
	public double zz[] = new double[300];
	
	public double max;
	
	public int mode;
	
	public DisplayView(Context context)
	{
		super(context);
		this.setFocusable(true);
	}
	
	public void getValue(double x[], double y[])
	{
		max = 1e-10;
		for(int i=0;i<300;i++)
		{
			this.x[i] = x[i];
			this.y[i] = -y[i];
			if(Math.abs(x[i])>max) max = Math.abs(x[i]);
			if(Math.abs(y[i])>max) max = Math.abs(y[i]);
		}
	}
	
	public void getValue(double x[], double y[], double z[][])
	{
		max = 1e-10;
		for(int i=0;i<50;i++)
		{
			this.x[i] = -x[i];
			this.y[i] = y[i];
			for(int j=0;j<50;j++)
			{
				this.z[i][j] = -z[i][j];
				if(Math.abs(z[i][j])>max) max = Math.abs(z[i][j]);
			}
			if(Math.abs(x[i])>max) max = Math.abs(x[i]);
			if(Math.abs(y[i])>max) max = Math.abs(y[i]);
		}
	}
	
	public void getValue(double x[], double y[], double z[])
	{
		max = 1e-10;
		for(int i=0;i<300;i++)
		{
			this.x[i] = -x[i];
			this.y[i] = y[i];
			this.zz[i] = -z[i];
			if(Math.abs(zz[i])>max) max = Math.abs(zz[i]);
			if(Math.abs(x[i])>max) max = Math.abs(x[i]);
			if(Math.abs(y[i])>max) max = Math.abs(y[i]);
		}
	}
	
	public void setMode(int mode)
	{
		this.mode = mode;
	}
	
	protected void onDraw(Canvas canvas)
	{
		Paint paint = new Paint();
		canvas.drawColor(Color.WHITE);
		paint.setColor(Color.BLACK);
		switch(mode)
		{
		case 1:
			canvas.drawLine(0, Function1.height / 2, Function1.width, Function1.height / 2, paint);
			canvas.drawLine(Function1.width / 2, 0, Function1.width / 2, Function1.height, paint);
			for(int i=1;i<300;i++)
			{
				canvas.drawLine((float)(x[i-1] / max * Function1.width / 2 + Function1.width / 2), 
						(float)(y[i-1] / max * Function1.height / 2 + Function1.height / 2), 
						(float)(x[i] / max * Function1.width / 2 + Function1.width / 2), 
						(float)(y[i] / max * Function1.height / 2 + Function1.height / 2), 
						paint);
			}
			break;
		case 2:
			canvas.drawLine(0, Function2.height / 2, Function2.width, Function2.height / 2, paint);
			canvas.drawLine(Function2.width / 2, 0, Function2.width / 2, Function2.height, paint);
			for(int i=1;i<300;i++)
			{
				canvas.drawLine((float)(x[i-1] / max * Function2.width / 2 + Function2.width / 2), 
						(float)(y[i-1] / max * Function2.height / 2 + Function2.height / 2), 
						(float)(x[i] / max * Function2.width / 2 + Function2.width / 2), 
						(float)(y[i] / max * Function2.height / 2 + Function2.height / 2), 
						paint);
			}
			break;
		case 3:
			canvas.drawLine(0, Function3.height / 2, Function3.width, Function3.height / 2, paint);
			canvas.drawLine(Function3.width / 2, 0, Function3.width / 2, Function3.height, paint);
			canvas.drawLine(0, Function3.height, Function3.width, 0, paint);
			for(int i=49;i>0;i--)
			{
				for(int j=1;j<50;j++)
				{
					canvas.drawLine((float)((y[j-1] - x[i] / 1.414) / max * Function3.width / 2 + Function3.width / 2 ), 
							(float)((z[i][j-1] - x[i] / 1.414) / max * Function3.height / 2 + Function3.height / 2), 
							(float)((y[j] - x[i] / 1.414) / max * Function3.width / 2 + Function3.width / 2), 
							(float)((z[i][j] - x[i] / 1.414) / max * Function3.height / 2 + Function3.height / 2), 
							paint);
					canvas.drawLine((float)((y[j] - x[i-1] / 1.414) / max * Function3.width / 2 + Function3.width / 2 ), 
							(float)((z[i-1][j] - x[i-1] / 1.414) / max * Function3.height / 2 + Function3.height / 2), 
							(float)((y[j] - x[i] / 1.414) / max * Function3.width / 2 + Function3.width / 2), 
							(float)((z[i][j] - x[i] / 1.414) / max * Function3.height / 2 + Function3.height / 2), 
							paint);
				}
			}
			break;
		case 4:
			canvas.drawLine(0, Function4.height / 2, Function4.width, Function4.height / 2, paint);
			canvas.drawLine(Function4.width / 2, 0, Function4.width / 2, Function4.height, paint);
			canvas.drawLine(0, Function4.height, Function4.width, 0, paint);
			for(int i=49;i>0;i--)
			{
				for(int j=1;j<50;j++)
				{
					canvas.drawLine((float)((y[j-1] - x[i] / 1.414) / max * Function4.width / 2 + Function4.width / 2 ), 
							(float)((z[i][j-1] - x[i] / 1.414) / max * Function4.height / 2 + Function4.height / 2), 
							(float)((y[j] - x[i] / 1.414) / max * Function4.width / 2 + Function4.width / 2), 
							(float)((z[i][j] - x[i] / 1.414) / max * Function4.height / 2 + Function4.height / 2), 
							paint);
					canvas.drawLine((float)((y[j] - x[i-1] / 1.414) / max * Function4.width / 2 + Function4.width / 2 ), 
							(float)((z[i-1][j] - x[i-1] / 1.414) / max * Function4.height / 2 + Function4.height / 2), 
							(float)((y[j] - x[i] / 1.414) / max * Function4.width / 2 + Function4.width / 2), 
							(float)((z[i][j] - x[i] / 1.414) / max * Function4.height / 2 + Function4.height / 2), 
							paint);
				}
			}
		case 5:
			canvas.drawLine(0, Function5.height / 2, Function5.width, Function5.height / 2, paint);
			canvas.drawLine(Function5.width / 2, 0, Function5.width / 2, Function5.height, paint);
			canvas.drawLine(0, Function5.height, Function5.width, 0, paint);
			for(int i=1;i<300;i++)
			{
				canvas.drawLine((float)((y[i-1] - x[i-1] / 1.414) / max * Function5.width / 2 + Function5.width / 2 ), 
						(float)((zz[i-1] - x[i-1] / 1.414) / max * Function5.height / 2 + Function5.height / 2), 
						(float)((y[i] - x[i] / 1.414) / max * Function5.width / 2 + Function5.width / 2), 
						(float)((zz[i] - x[i] / 1.414) / max * Function5.height / 2 + Function5.height / 2), 
						paint);
			}
		}
	}
}
