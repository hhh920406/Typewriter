package com.zsys.view;

import com.zsys.main.MainActivity;
import com.zsys.main.Matrix;

public abstract class IView {
	
	protected MainActivity activity;
	
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
