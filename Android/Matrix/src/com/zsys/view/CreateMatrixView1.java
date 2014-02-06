package com.zsys.view;

import com.zsys.R;
import com.zsys.main.MainActivity;
import com.zsys.main.Matrix;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class CreateMatrixView1 extends IView{
	private Button nextButton;
	private Button cancelButton;
	private NextButtonListener nextButtonListener;
	private CancelButtonListener cancelButtonListener;
	
	public void addButtonListener() {
		this.nextButton = (Button) this.activity.findViewById(R.id.nextButton);
		this.nextButtonListener = new NextButtonListener(this.activity);
		this.nextButton.setOnClickListener(this.nextButtonListener);
		this.cancelButton = (Button) this.activity.findViewById(R.id.cancelButton);
		this.cancelButtonListener = new CancelButtonListener(this.activity);
		this.cancelButton.setOnClickListener(this.cancelButtonListener);
	}
	
	private class NextButtonListener extends ZOnClickListener {


		private RadioButton radioZero;
		private RadioButton radioOne;
		private RadioButton radioUnit;
		private EditText widthEdit;
		private EditText heightEdit;
		private RadioGroup matrixStatus;
		
		public NextButtonListener(MainActivity activity) {
			super(activity);
			this.widthEdit = (EditText) this.activity.findViewById(R.id.widthEdit);
			this.heightEdit = (EditText) this.activity.findViewById(R.id.heightEdit);
			this.radioZero = (RadioButton) this.activity.findViewById(R.id.radioZero);
			this.radioOne = (RadioButton) this.activity.findViewById(R.id.radioOne);
			this.radioUnit = (RadioButton) this.activity.findViewById(R.id.radioUnit);
			this.matrixStatus = (RadioGroup) this.activity.findViewById(R.id.radioGroup1);
		}
		
		
		@Override
		public void onClick(View v) {
			int column = Integer.parseInt(this.widthEdit.getText().toString());
			int row = Integer.parseInt(this.heightEdit.getText().toString());
			if(this.matrixStatus.getCheckedRadioButtonId() == this.radioZero.getId()) {
				this.activity.getTransferMatrix().clone(Matrix.zeroMatrix(row, column));
			} else if(this.matrixStatus.getCheckedRadioButtonId() == this.radioOne.getId()) {
				this.activity.getTransferMatrix().clone(Matrix.oneMatrix(row, column));
			} else if(this.matrixStatus.getCheckedRadioButtonId() == this.radioUnit.getId()) {
				this.activity.getTransferMatrix().clone(Matrix.unitMatrix(row, column));
			}
			this.activity.setCurrentView(MainActivity.SCENE_CREATE1, MainActivity.SCENE_CREATE2);
		}
		
	}
	
	private class CancelButtonListener extends ZOnClickListener {
		
		public CancelButtonListener(MainActivity activity) {
			super(activity);
		}
		
		@Override
		public void onClick(View v) {
			this.activity.setCurrentView(MainActivity.SCENE_CREATE1, MainActivity.SCENE_STAGE);
		}
		
	}
}
