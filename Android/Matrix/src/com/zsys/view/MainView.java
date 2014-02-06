package com.zsys.view;

import java.text.DecimalFormat;
import java.util.ArrayList;

import com.zsys.R;
import com.zsys.display.ButtonDisplay;
import com.zsys.display.MatrixDisplay;
import com.zsys.display.RelationDisplay;
import com.zsys.main.BitmapSource;
import com.zsys.main.MainActivity;
import com.zsys.main.Matrix;

import android.R.drawable;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Cap;
import android.graphics.Paint.Join;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

public class MainView extends ZView {
	private ArrayList<MatrixDisplay> matrixDisplay;
	private ArrayList<ButtonDisplay> buttonDisplay;
	private ArrayList<RelationDisplay> relationDisplay;
	private int matrixIndex;
	private int buttonIndex;
	private float leaveX;
	private float leaveY;
	private float watchX;
	private float watchY;
	private float zoom;
	private boolean createSelected1;
	private boolean createSelected2;
	private MatrixDisplay tempMatrixDisplay;
	private RelationDisplay tempRelationDisplay;
	private View splitDialogLayout;
	
	private DeleteListener deleteListener;
	private CreateOneListener createOneListener;
	private CreateTwoListener createTwoListener;
	
	public MainView(Context context) {
		super(context);
		this.deleteListener = new DeleteListener(this);
		this.createOneListener = new CreateOneListener(this);
		this.createTwoListener = new CreateTwoListener(this);
		this.matrixDisplay = new ArrayList<MatrixDisplay>();
		this.relationDisplay = new ArrayList<RelationDisplay>();
		this.initialButton();
		this.matrixIndex = 0;
		this.buttonIndex = 0;
		this.watchX = 0.0f;
		this.watchY = 0.0f;
		this.zoom = 1.0f;
		this.createSelected1 = false;
		this.createSelected2 = false;
	}
	
	private void initialButton() {
		this.buttonDisplay = new ArrayList<ButtonDisplay>();
		ButtonDisplay display;
		for(int i=0;i<6;++i) {
			display = new ButtonDisplay();
			display.setPosition(10.0f, i * 45.0f + 10.0f);
			display.setSize(34.0f, 34.0f);
			display.setBitmapIndex(i);
			this.buttonDisplay.add(display);
		}
		this.buttonDisplay.get(0).setSelected(true);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		boolean flag = false;
		switch(event.getAction()) {
		case MotionEvent.ACTION_DOWN:
			for(int i=this.buttonDisplay.size()-1;i>=0 && !this.createSelected1;--i) {
				if(this.buttonDisplay.get(i).onTouchDown(event.getX(), event.getY())) {
					this.buttonIndex = i;
					flag = true;
					break;
				}
			}
			if(flag) {
				for(ButtonDisplay display : this.buttonDisplay) {
					display.setSelected(false);
				}
				this.buttonDisplay.get(this.buttonIndex).setSelected(true);
			} else {
				this.matrixIndex = -1;
				for(int i=this.matrixDisplay.size()-1;i>=0;--i) {
					if(this.matrixDisplay.get(i).onTouchDown(event.getX(), event.getY())) {
						this.matrixIndex = i;
						break;
					}
				}
				switch(this.buttonIndex) {
				case BitmapSource.BUTTON_DELETE:
					if(this.matrixIndex != -1) {
						AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
						builder.setIcon(drawable.ic_dialog_alert);
						builder.setTitle("Delete");
						builder.setMessage("Are you sure to delete the selected matrix? ");
						builder.setPositiveButton("Confirm", this.deleteListener);
						builder.setNegativeButton("Cancel", null);
						builder.show();
					}
					break;
				case BitmapSource.BUTTON_EDIT:
					if(this.matrixIndex != -1) {
						int row = this.matrixDisplay.get(this.matrixIndex).matrix.getRow();
						int column = this.matrixDisplay.get(this.matrixIndex).matrix.getColumn();
						this.activity.getTransferMatrix().setSize(row, column);
						for(int i=0;i<row;++i) {
							for(int j=0;j<column;++j) {
								this.activity.getTransferMatrix().m[i][j] = this.matrixDisplay.get(this.matrixIndex).matrix.m[i][j];
							}
						}
						this.activity.setCurrentView(MainActivity.SCENE_STAGE, MainActivity.SCENE_EDIT);
					}
					break;
				case BitmapSource.BUTTON_CREATE:
					if(this.createSelected1) {
						if(this.createSelected2) {
							AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
							builder.setIcon(drawable.ic_dialog_info);
							builder.setTitle("Select Relation");
							builder.setItems(R.array.relationtwo, this.createTwoListener);
							builder.create();
							builder.show();
							this.tempMatrixDisplay.setPosition(event.getX() / this.zoom + this.watchX, event.getY() / this.zoom + this.watchY);
							this.tempMatrixDisplay.setWatchPoint(this.watchX, this.watchY);
							this.tempMatrixDisplay.setZoom(this.zoom);
							this.tempRelationDisplay.setMatrixDisplay3(this.tempMatrixDisplay);
							this.createSelected1 = false;
							this.createSelected2 = false;
						} else {
							if(this.matrixIndex == -1) {
								AlertDialog.Builder builder = new AlertDialog.Builder(this.activity);
								builder.setIcon(drawable.ic_dialog_info);
								builder.setTitle("Select Relation");
								builder.setItems(R.array.relationone, this.createOneListener);
								builder.create();
								builder.show();
								this.tempMatrixDisplay.setPosition(event.getX() / this.zoom + this.watchX, event.getY() / this.zoom + this.watchY);
								this.tempMatrixDisplay.setWatchPoint(this.watchX, this.watchY);
								this.tempMatrixDisplay.setZoom(this.zoom);
								this.tempRelationDisplay.setMatrixDisplay2(this.tempMatrixDisplay);
								this.createSelected1 = false;
							} else {
								this.tempRelationDisplay.setMatrixDisplay2(this.matrixDisplay.get(this.matrixIndex));
								this.createSelected2 = true;
							}
						}
					} else {
						if(this.matrixIndex == -1) {
							this.leaveX = event.getX();
							this.leaveY = event.getY();
							this.activity.setCurrentView(MainActivity.SCENE_STAGE, MainActivity.SCENE_CREATE1);
						} else {
							this.tempMatrixDisplay = new MatrixDisplay();
							this.tempMatrixDisplay.setPosition(event.getX() + this.watchX, event.getY() + this.watchY);
							this.tempMatrixDisplay.setWatchPoint(this.watchX, this.watchY);
							this.tempMatrixDisplay.setZoom(this.zoom);
							this.tempMatrixDisplay.matrix = Matrix.unitMatrix(1);
							this.tempRelationDisplay = new RelationDisplay();
							this.tempRelationDisplay.setZoom(this.zoom);
							this.tempRelationDisplay.setMatrixDisplay1(this.matrixDisplay.get(this.matrixIndex));
							this.createSelected1 = true;
						}
					}
					break;
				case BitmapSource.BUTTON_MOVE:
					this.leaveX = event.getX();
					this.leaveY = event.getY();
					break;
				case BitmapSource.BUTTON_ZOOMIN:
					this.zoom += 0.1f;
					if(this.zoom > 10.0f) {
						this.zoom = 10.0f;
					}
					for(MatrixDisplay display : this.matrixDisplay) {
						display.setZoom(this.zoom);
					}
					for(RelationDisplay display : this.relationDisplay) {
						display.setZoom(this.zoom);
					}
					if(this.tempMatrixDisplay != null) {
						this.tempMatrixDisplay.setZoom(this.zoom);
					}
					if(this.tempRelationDisplay != null) {
						this.tempRelationDisplay.setZoom(this.zoom);
					}
					break;
				case BitmapSource.BUTTON_ZOOMOUT:
					this.zoom -= 0.1f;
					if(this.zoom < 0.1f) {
						this.zoom = 0.1f;
					}
					for(MatrixDisplay display : this.matrixDisplay) {
						display.setZoom(this.zoom);
					}
					for(RelationDisplay display : this.relationDisplay) {
						display.setZoom(this.zoom);
					}
					if(this.tempMatrixDisplay != null) {
						this.tempMatrixDisplay.setZoom(this.zoom);
					}
					if(this.tempRelationDisplay != null) {
						this.tempRelationDisplay.setZoom(this.zoom);
					}
					break;
				}
			}
			break;
		case MotionEvent.ACTION_MOVE:
			for(int i=this.buttonDisplay.size()-1;i>=0;--i) {
				if(this.buttonDisplay.get(i).onTouchDown(event.getX(), event.getY())) {
					this.buttonIndex = i;
					flag = true;
					break;
				}
			}
			if(flag) {
				for(ButtonDisplay display : this.buttonDisplay) {
					display.setSelected(false);
				}
				this.buttonDisplay.get(this.buttonIndex).setSelected(true);
			} else {
				switch(this.buttonIndex) {
				case BitmapSource.BUTTON_MOVE:
					if(this.matrixIndex != -1) {
						float oldX = this.matrixDisplay.get(this.matrixIndex).getX();
						float oldY = this.matrixDisplay.get(this.matrixIndex).getY();
						oldX += (event.getX() - this.leaveX) / this.zoom;
						oldY += (event.getY() - this.leaveY) / this.zoom;
						this.matrixDisplay.get(this.matrixIndex).setPosition(oldX, oldY);
					} else {
						this.watchX += event.getX() - this.leaveX;
						this.watchY += event.getY() - this.leaveY;
						for(MatrixDisplay display : this.matrixDisplay) {
							display.setWatchPoint(this.watchX, this.watchY);
						}
						if(this.tempMatrixDisplay != null) {
							this.tempMatrixDisplay.setWatchPoint(this.watchX, this.watchY);
						}
						if(this.tempRelationDisplay != null) {
							this.tempRelationDisplay.setWatchPoint(this.watchX, this.watchY);
						}
					}
					this.leaveX = event.getX();
					this.leaveY = event.getY();
					break;
				}
			}
			break;
		case MotionEvent.ACTION_UP:
			for(int i=this.buttonDisplay.size()-1;i>=0;--i) {
				if(this.buttonDisplay.get(i).onTouchDown(event.getX(), event.getY())) {
					this.buttonIndex = i;
					flag = true;
					break;
				}
			}
			if(flag) {
				for(ButtonDisplay display : this.buttonDisplay) {
					display.setSelected(false);
				}
				this.buttonDisplay.get(this.buttonIndex).setSelected(true);
			} else {
				for(MatrixDisplay display : this.matrixDisplay) {
					display.onTouchUp(event.getX(), event.getY());
				}
			}
			break;
		}
		this.postInvalidate();
		return true;
	}
	
	@Override
	public void onDraw(Canvas canvas) {
		for(RelationDisplay display : this.relationDisplay) {
			display.onDraw(canvas);
		}
		for(MatrixDisplay display : this.matrixDisplay) {
			display.onDraw(canvas);
		}
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setARGB(100, 255, 255, 255);
		paint.setStrokeWidth(2.0f);
		paint.setStrokeJoin(Join.ROUND);
		paint.setStrokeCap(Cap.ROUND);
		if(this.buttonDisplay.get(0).isSelected()) {
			canvas.drawLine(this.buttonDisplay.get(0).midX(), 0.0f, 
					this.buttonDisplay.get(0).midX() + 15.0f, 
					this.buttonDisplay.get(0).midY(), paint);
		} else {
			canvas.drawLine(this.buttonDisplay.get(0).midX(), 0.0f, 
					this.buttonDisplay.get(0).midX(), 
					this.buttonDisplay.get(0).midY(), paint);
		}
		for(int i=0;i<this.buttonDisplay.size()-1;++i) {
			if(this.buttonDisplay.get(i+1).isSelected()) {
				canvas.drawLine(this.buttonDisplay.get(i).midX(), 
						this.buttonDisplay.get(i).midY(), 
						this.buttonDisplay.get(i+1).midX() + 15.0f, 
						this.buttonDisplay.get(i+1).midY(), paint);
			} else if(this.buttonDisplay.get(i).isSelected()) {
				canvas.drawLine(this.buttonDisplay.get(i).midX() + 15.0f, 
						this.buttonDisplay.get(i).midY(), 
						this.buttonDisplay.get(i+1).midX(), 
						this.buttonDisplay.get(i+1).midY(), paint);
			} else {
				canvas.drawLine(this.buttonDisplay.get(i).midX(), 
						this.buttonDisplay.get(i).midY(), 
						this.buttonDisplay.get(i+1).midX(), 
						this.buttonDisplay.get(i+1).midY(), paint);
			}
		}
		for(ButtonDisplay display : this.buttonDisplay) {
			display.onDraw(canvas);
		}
		paint.setColor(Color.WHITE);
		paint.setTextSize(20.0f);
		String show = "";
		switch(this.buttonIndex) {
		case BitmapSource.BUTTON_CREATE:
			show = "Create Mode";
			if(this.createSelected1) {
				if(this.createSelected2) {
					show = "Add relation, two selected.";
				} else {
					show = "Add Relation, one selected.";
				}
			}
			canvas.drawText(show, 70.0f, 20.0f, paint);
			break;
		case BitmapSource.BUTTON_DELETE:
			canvas.drawText("Delete Mode", 70.0f, 20.0f, paint);
			break;
		case BitmapSource.BUTTON_EDIT:
			canvas.drawText("Edit Mode", 70.0f, 20.0f, paint);
			break;
		case BitmapSource.BUTTON_MOVE:
			show = "Move Mode";
			if(this.matrixIndex != -1) {
				show += " : Matrix";
			} else {
				show += " : Stage";
			}
			canvas.drawText(show, 70.0f, 20.0f, paint);
			break;
		case BitmapSource.BUTTON_ZOOMIN:
			canvas.drawText("Zoom In", 70.0f, 20.0f, paint);
			break;
		case BitmapSource.BUTTON_ZOOMOUT:
			canvas.drawText("Zoom Out", 70.0f, 20.0f, paint);
			break;
		}
		DecimalFormat df = new DecimalFormat("#0.00");
		canvas.drawText("Position: (" + df.format(this.watchX) + ", " + df.format(this.watchY) + ")", 70.0f, 45.0f, paint);
		df = new DecimalFormat("#0");
		canvas.drawText("Zoom: " + df.format(this.zoom * 100) + "%", 70.0f, 70.0f, paint);
	}
	
	public void addMatrix(Matrix matrix) {
		MatrixDisplay display = new MatrixDisplay();
		display.matrix = matrix.copy();
		display.setPosition(this.leaveX / this.zoom + this.watchX, this.leaveY / this.zoom + this.watchY);
		display.setWatchPoint(this.watchX, this.watchY);
		display.setZoom(this.zoom);
		this.matrixDisplay.add(display);
	}
	
	public void editMatrix(Matrix matrix) {
		this.matrixDisplay.get(this.matrixIndex).matrix.clone(matrix);
	}
	
	private class DeleteListener implements DialogInterface.OnClickListener {
		private MainView mainView;
		
		public DeleteListener(MainView mainView) {
			this.mainView = mainView;
		}
		
		@Override
		public void onClick(DialogInterface dialog, int which) {
			if(this.mainView.matrixIndex != -1) {
				for(int i=this.mainView.relationDisplay.size()-1;i>=0;--i) {
					if(this.mainView.relationDisplay.get(i).getMatrixDisplay1().matrix == this.mainView.matrixDisplay.get(this.mainView.matrixIndex).matrix) {
						this.mainView.relationDisplay.remove(i);
					} else if(this.mainView.relationDisplay.get(i).getMatrixDisplay2().matrix == this.mainView.matrixDisplay.get(this.mainView.matrixIndex).matrix) {
						this.mainView.relationDisplay.remove(i);
					} else if(this.mainView.relationDisplay.get(i).isRealtionTwo()) {
						if(this.mainView.relationDisplay.get(i).getMatrixDisplay3().matrix == this.mainView.matrixDisplay.get(this.mainView.matrixIndex).matrix) {
							this.mainView.relationDisplay.remove(i);
						}
					}
				}
				this.mainView.matrixDisplay.remove(this.mainView.matrixIndex);
				this.mainView.postInvalidate();
			}
			
		}
	}
	
	private class CreateOneListener implements DialogInterface.OnClickListener {
		private MainView mainView;
		
		public CreateOneListener(MainView mainView) {
			this.mainView = mainView;
		}

		@Override
		public void onClick(DialogInterface dialog, int which) {
			switch(which + RelationDisplay.RELATION_ONE_MIN) {
			case RelationDisplay.RELATION_ONE_TRANSPOSE:
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.transpose();
				break;
			case RelationDisplay.RELATION_ONE_UPPER_TRIANGULAR:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isSquareMatrix()) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must be square. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.upperTriangular();
				break;
			case RelationDisplay.RELATION_ONE_LOWER_TRIANGULAR:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isSquareMatrix()) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must be square. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.lowerTriangular();
				break;
			case RelationDisplay.RELATION_ONE_ADJONT:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isSquareMatrix()) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must be square. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.adjont();
				break;
			case RelationDisplay.RELATION_ONE_DETERMINANT:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isSquareMatrix()) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must be square. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.determinant();
				break;
			case RelationDisplay.RELATION_ONE_SPLIT:
				LayoutInflater inflater = this.mainView.activity.getLayoutInflater();
				View splitDialogLayout = inflater.inflate(R.layout.splitdialog, (ViewGroup)findViewById(R.id.splitdialog));
				SplitConfirmListener listener = new SplitConfirmListener(this.mainView);
				AlertDialog.Builder builder = new AlertDialog.Builder(this.mainView.activity);
				builder.setTitle("Set Parameters");
				builder.setView(splitDialogLayout);
				builder.setPositiveButton("Confirm", listener);
				builder.setNegativeButton("Cancel", null);
				builder.show();
				return;
			}
			this.mainView.tempRelationDisplay.setRelation(which + RelationDisplay.RELATION_ONE_MIN);
			this.mainView.matrixDisplay.add(this.mainView.tempMatrixDisplay);
			this.mainView.relationDisplay.add(this.mainView.tempRelationDisplay);
			this.mainView.postInvalidate();
		}
	}
	
	private class SplitConfirmListener implements DialogInterface.OnClickListener {
		private MainView mainView;
		private EditText editTop;
		private EditText editLeft;
		private EditText editBottom;
		private EditText editRight;
		
		public SplitConfirmListener(MainView mainView) {
			this.mainView = mainView;
			this.editTop = (EditText) this.mainView.splitDialogLayout.findViewById(R.id.editTop);
			this.editLeft = (EditText) this.mainView.splitDialogLayout.findViewById(R.id.editLeft);
			this.editBottom = (EditText) this.mainView.splitDialogLayout.findViewById(R.id.editBottom);
			this.editRight = (EditText) this.mainView.splitDialogLayout.findViewById(R.id.editRight);
		}
		
		private void autoZero(EditText edit) {
			if(edit.getText().toString().equals("")) {
				edit.setText("0");
			}
		}

		@Override
		public void onClick(DialogInterface dialog, int which) {
			this.autoZero(this.editTop);
			this.autoZero(this.editLeft);
			this.autoZero(this.editBottom);
			this.autoZero(this.editRight);
			int top = Integer.parseInt(this.editTop.getText().toString());
			int left = Integer.parseInt(this.editLeft.getText().toString());
			int bottom = Integer.parseInt(this.editBottom.getText().toString());
			int right = Integer.parseInt(this.editRight.getText().toString());
			if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isInside(top, left) || 
					!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isInside(bottom, right)) {
				new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Index out of bounds. ").show();
				return;
			}
			if(bottom < top || right < left) {
				new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Range error. ").show();
				return;
			}
			this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.subMatrix(top, left, right, bottom);
			this.mainView.tempRelationDisplay.setRelation(RelationDisplay.RELATION_ONE_SPLIT);
			this.mainView.matrixDisplay.add(this.mainView.tempMatrixDisplay);
			this.mainView.relationDisplay.add(this.mainView.tempRelationDisplay);
			this.mainView.postInvalidate();
		}
	}
	
	private class CreateTwoListener implements DialogInterface.OnClickListener {
		private MainView mainView;
		
		public CreateTwoListener(MainView mainView) {
			this.mainView = mainView;
		}

		@Override
		public void onClick(DialogInterface dialog, int which) {
			switch(which + RelationDisplay.RELATION_TWO_MIN) {
			case RelationDisplay.RELATION_TWO_ADD:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isDimentionAgree(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix)) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix dimensions must agree. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.add(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix);
				break;
			case RelationDisplay.RELATION_TWO_SUBSTRACT:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isDimentionAgree(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix)) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix dimensions must agree. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.substract(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix);
				break;
			case RelationDisplay.RELATION_TWO_MULTIPLY:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isInnerDimentionAgree(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix)) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Inner matrix dimensions must agree. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.multiply(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix);
				break;
			case RelationDisplay.RELATION_TWO_MERGER_HORIZON:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isRowAgree(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix)) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must have the same height. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.horizonMerger(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix);
				break;
			case RelationDisplay.RELATION_TWO_MERGER_VERTICAL:
				if(!this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.isColumnAgree(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix)) {
					new AlertDialog.Builder(this.mainView.activity).setTitle("Illegal Operation").setMessage("Matrix must have the same width. ").show();
					return;
				}
				this.mainView.tempMatrixDisplay.matrix = this.mainView.tempRelationDisplay.getMatrixDisplay1().matrix.verticalMerger(this.mainView.tempRelationDisplay.getMatrixDisplay2().matrix);
				break;
			}
			this.mainView.tempRelationDisplay.setRelation(which + RelationDisplay.RELATION_TWO_MIN);
			this.mainView.matrixDisplay.add(this.mainView.tempMatrixDisplay);
			this.mainView.relationDisplay.add(this.mainView.tempRelationDisplay);
			this.mainView.postInvalidate();
		}
	}

	public boolean isCreateSelected1() {
		return createSelected1;
	}

	public void setCreateSelected1(boolean createSelected1) {
		this.createSelected1 = createSelected1;
	}

	public boolean isCreateSelected2() {
		return createSelected2;
	}

	public void setCreateSelected2(boolean createSelected2) {
		this.createSelected2 = createSelected2;
	}
}
