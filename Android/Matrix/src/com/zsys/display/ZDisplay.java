package com.zsys.display;

import android.graphics.Canvas;

public abstract class ZDisplay {
	protected float x;
	protected float y;
	protected float width;
	protected float height;
	protected boolean selected;
	protected float watchX;
	protected float watchY;
	protected float zoom;
	
	public ZDisplay() {
		this.setPosition(0.0f, 0.0f);
		this.setSize(1.0f, 1.0f);
		this.setWatchPoint(0.0f, 0.0f);
		this.zoom = 1.0f;
	}
	
	public boolean onTouchDown(float x, float y) {
		return this.selected = this.inArea(x, y);
	}
	
	public boolean onTouchUp(float x, float y) {
		this.selected = false;
		return this.inArea(x, y);
	}
	
	public abstract void onDraw(Canvas canvas);
	
	public float getX() {
		return x;
	}
	public void setX(float x) {
		this.x = x;
	}
	public float getY() {
		return y;
	}
	public void setY(float y) {
		this.y = y;
	}
	public float getWidth() {
		return width;
	}
	public void setWidth(float width) {
		this.width = width;
	}
	public float getHeight() {
		return height;
	}
	public void setHeight(float height) {
		this.height = height;
	}
	
	public void setPosition(float x, float y) {
		this.setX(x);
		this.setY(y);
	}
	
	public void setSize(float width, float height) {
		this.setWidth(width);
		this.setHeight(height);
	}
	
	public boolean isSelected() {
		return this.selected;
	}
	
	public void setSelected(boolean selected) {
		this.selected = selected;
	}
	
	public float left() {
		return this.x;
	}
	
	public float right() {
		return this.x + this.width;
	}
	
	public float top() {
		return this.y;
	}
	
	public float bottom() {
		return this.y + this.height;
	}
	
	public float midX() {
		return (this.left() + this.right()) * 0.5f;
	}
	
	public float midY() {
		return (this.top() + this.bottom()) * 0.5f;
	}
	
	public boolean inArea(float x, float y) {
		return x >= this.left() && x <= this.right() &&
				y >= this.top() && y <= this.bottom();
	}

	public float getWatchX() {
		return watchX;
	}

	public void setWatchX(float watchX) {
		this.watchX = watchX;
	}

	public float getWatchY() {
		return watchY;
	}

	public void setWatchY(float watchY) {
		this.watchY = watchY;
	}
	
	public void setWatchPoint(float watchX, float watchY) {
		this.watchX = watchX;
		this.watchY = watchY;
	}

	public float getZoom() {
		return zoom;
	}

	public void setZoom(float zoom) {
		this.zoom = zoom;
	}
}
