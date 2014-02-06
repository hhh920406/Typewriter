package com.zsys.display;

import java.text.DecimalFormat;

import com.zsys.main.Matrix;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Cap;
import android.graphics.Paint.Join;

public class MatrixDisplay extends ZDisplay {
	public Matrix matrix;
	public float interWidth, interHeight;
	
	public MatrixDisplay() {
		this.setPosition(0.0f, 0.0f);
		this.matrix = new Matrix();
		this.interWidth = 40;
		this.interHeight = 30;
		this.selected = false;
	}
	
	private int getNumberLength(double num) {
		int len = 4;
		while(num > 9.99)
		{
			num /= 10;
			++ len;
		}
		return len;
	}
	
	private void getInterWidth() {
		int len = 0;
		for(int i=0;i<this.matrix.getRow();++i) {
			for(int j=0;j<this.matrix.getColumn();++j) {
				if(this.getNumberLength(this.matrix.m[i][j]) > len) {
					len = this.getNumberLength(this.matrix.m[i][j]);
				}
			}
		}
		this.interWidth = len * 9.0f + 15.0f;
	}
	
	@Override
	public float left() {
		return (this.x + this.watchX) * this.zoom;
	}
	
	@Override
	public float right() {
		this.getInterWidth();
		return (this.x + this.interWidth * this.matrix.getColumn() + this.watchX) * this.zoom;
	}
	
	@Override
	public float top() {
		return (this.y + this.watchY) * this.zoom;
	}

	@Override
	public float bottom() {
		return (this.y + this.interHeight * this.matrix.getRow() + this.watchY) * this.zoom;
	}

	@Override
	public void onDraw(Canvas canvas) {
		this.getInterWidth();
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		if(this.selected) {
			paint.setARGB(50, 255, 255, 255);
		} else {
			paint.setARGB(10, 255, 255, 255);
		}
		canvas.drawRect(this.left(), this.top(), this.right(), this.bottom(), paint);
		paint.setColor(Color.WHITE);
		paint.setTextAlign(Align.RIGHT);
		paint.setTextSize(18.0f * this.zoom);
		paint.setStrokeWidth(3.0f);
		paint.setStrokeJoin(Join.ROUND);
		paint.setStrokeCap(Cap.ROUND);
		for(int i=0;i<this.matrix.getRow();++i) {
			for(int j=0;j<this.matrix.getColumn();++j) {
				DecimalFormat df = new DecimalFormat("#0.00");
				canvas.drawText(df.format(this.matrix.m[i][j]), 
						this.left() + this.zoom * this.interWidth * (j + 1) - this.zoom * 10.0f, 
						this.top() + this.zoom * this.interHeight * (i + 1) - this.zoom * this.interHeight / 4, 
						paint);
			}
		}
		canvas.drawLine(this.left(), this.top(), this.left(), this.bottom(), paint);
		canvas.drawLine(this.right(), this.top(), this.right(), this.bottom(), paint);
		canvas.drawLine(this.left(), this.top(), this.left() + 10 * this.zoom, this.top(), paint);
		canvas.drawLine(this.right(), this.top(), this.right() - 10 * this.zoom, this.top(), paint);
		canvas.drawLine(this.left(), this.bottom(), this.left() + 10 * this.zoom, this.bottom(), paint);
		canvas.drawLine(this.right(), this.bottom(), this.right() - 10 * this.zoom, this.bottom(), paint);
	}
}
