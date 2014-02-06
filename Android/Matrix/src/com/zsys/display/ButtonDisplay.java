package com.zsys.display;

import com.zsys.main.BitmapSource;

import android.graphics.Canvas;
import android.graphics.Paint;

public class ButtonDisplay extends ZDisplay{
	
	private int bitmapIndex;
	
	public ButtonDisplay() {
		this.width = 40;
		this.height = 40;
	}
	
	@Override
	public void onDraw(Canvas canvas) {
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		if(this.selected) {
			canvas.drawBitmap(BitmapSource.button[this.bitmapIndex], this.x + 15.0f, this.y, paint);
		} else {
			canvas.drawBitmap(BitmapSource.button[this.bitmapIndex], this.x, this.y, paint);
		}
	}
	
	@Override
	public boolean onTouchDown(float x, float y) {
		return inArea(x, y);
	}

	public int getBitmapIndex() {
		return bitmapIndex;
	}

	public void setBitmapIndex(int bitmapIndex) {
		this.bitmapIndex = bitmapIndex;
	}
}
