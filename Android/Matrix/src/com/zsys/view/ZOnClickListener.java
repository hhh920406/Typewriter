package com.zsys.view;

import com.zsys.main.MainActivity;

import android.view.View;

public abstract class ZOnClickListener implements View.OnClickListener{
	protected MainActivity activity;
	
	public ZOnClickListener(MainActivity activity) {
		this.activity = activity;
	}

	@Override
	public abstract void onClick(View v);

}
