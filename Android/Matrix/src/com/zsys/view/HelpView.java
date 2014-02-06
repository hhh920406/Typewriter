package com.zsys.view;

import com.zsys.R;
import com.zsys.main.MainActivity;

import android.view.View;
import android.widget.Button;

public class HelpView extends IView {
	private Button backButton;
	private BackButtonListener backButtonListener;
	
	public void addButtonListener() {
		this.backButton = (Button) this.activity.findViewById(R.id.backButton);
		this.backButtonListener = new BackButtonListener(this.activity);
		this.backButton.setOnClickListener(this.backButtonListener);
	}
	
	private class BackButtonListener extends ZOnClickListener {
		public BackButtonListener(MainActivity activity) {
			super(activity);
		}

		@Override
		public void onClick(View v) {
			this.activity.setCurrentView(MainActivity.SCENE_HELP, MainActivity.SCENE_STAGE);
		}
	}
}
