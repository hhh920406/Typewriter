package com.zsys.view;

import java.text.DecimalFormat;

import com.zsys.R;
import com.zsys.main.MainActivity;

import android.text.InputType;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TableLayout;
import android.widget.TableRow;

public class EditMatrixView extends IView{
	private EditText[][] matrixEdit;
	private TableLayout matrixLayout;
	private Button confirmButton;
	private Button cancelButton;
	private ConfirmButtonListener confirmButtonListener;
	private CancelButtonListener cancelButtonListener;

	public void addButtonListener() {
		int height = this.activity.getTransferMatrix().getRow();
		int width = this.activity.getTransferMatrix().getColumn();
		this.matrixLayout = (TableLayout) this.activity.findViewById(R.id.matrixLayout);
        this.matrixLayout.setStretchAllColumns(true); 
		this.matrixEdit = new EditText[height][width];
		DecimalFormat df = new DecimalFormat("#0.00");
		for(int i=0;i<height;++i) {
			TableRow matrixRow = new TableRow(this.activity);
			for(int j=0;j<width;++j) {
				this.matrixEdit[i][j] = new EditText(this.activity);
				this.matrixEdit[i][j].setMinimumWidth(80);
				this.matrixEdit[i][j].setText(df.format(this.activity.getTransferMatrix().m[i][j]));
				this.matrixEdit[i][j].setInputType(InputType.TYPE_NUMBER_FLAG_DECIMAL);
				matrixRow.addView(this.matrixEdit[i][j]);
			}
			this.matrixLayout.addView(matrixRow);
		}
		this.confirmButton = (Button) this.activity.findViewById(R.id.confirmButton);
		this.confirmButtonListener = new ConfirmButtonListener(this.activity);
		this.confirmButtonListener.setMatrixText(this.matrixEdit);
		this.confirmButton.setOnClickListener(this.confirmButtonListener);
		this.cancelButton = (Button) this.activity.findViewById(R.id.cancelButton);
		this.cancelButtonListener = new CancelButtonListener(this.activity);
		this.cancelButton.setOnClickListener(this.cancelButtonListener);
	}
	
	private class ConfirmButtonListener extends ZOnClickListener {
		private EditText[][] matrixEdit;
		
		public ConfirmButtonListener(MainActivity activity) {
			super(activity);
		}
		
		public void setMatrixText(EditText[][] matrixEdit) {
			this.matrixEdit = matrixEdit;
		}

		@Override
		public void onClick(View v) {
			int height = this.activity.getTransferMatrix().getRow();
			int width = this.activity.getTransferMatrix().getColumn();
			for(int i=0;i<height;++i) {
				for(int j=0;j<width;++j) {
					this.activity.getTransferMatrix().m[i][j] = Double.parseDouble(this.matrixEdit[i][j].getText().toString());
				}
			}
			this.activity.setCurrentView(MainActivity.SCENE_EDIT_CONFIRM, MainActivity.SCENE_STAGE);
		}
	}
	
	private class CancelButtonListener extends ZOnClickListener {
		public CancelButtonListener(MainActivity activity) {
			super(activity);
		}

		@Override
		public void onClick(View v) {
			this.activity.setCurrentView(MainActivity.SCENE_EDIT, MainActivity.SCENE_STAGE);
		}
	}
}
