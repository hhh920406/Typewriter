package com.zsys.view;

import com.zsys.main.MainActivity;
import com.zsys.main.Matrix;

import android.content.Context;
import android.view.View;

public abstract class ZView extends View {
	
	protected MainActivity activity;

	public ZView(Context context) {
		super(context);
	}
	
	public void setActivity(MainActivity activity) {
		this.activity = activity;
	}
	
	public void setCurrentView(int fromView, int targetView) {
		this.activity.setCurrentView(fromView, targetView);
	}
	
	public Matrix getTransferMatrix() {
		return this.activity.getTransferMatrix();
	}

}
