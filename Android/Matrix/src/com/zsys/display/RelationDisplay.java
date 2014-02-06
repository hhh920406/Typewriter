package com.zsys.display;

import android.graphics.Canvas;
import android.graphics.DashPathEffect;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.graphics.Paint.Cap;
import android.graphics.Paint.Join;
import android.graphics.PathEffect;

public class RelationDisplay extends ZDisplay {
	public static final int RELATION_ONE_MIN 					= 1000;
	public static final int RELATION_ONE_TRANSPOSE 			= 1000;
	public static final int RELATION_ONE_UPPER_TRIANGULAR 	= 1001;
	public static final int RELATION_ONE_LOWER_TRIANGULAR 	= 1002;
	public static final int RELATION_ONE_ADJONT 				= 1003;
	public static final int RELATION_ONE_DETERMINANT			= 1004;
	public static final int RELATION_ONE_SPLIT				= 1005;
	public static final int RELATION_ONE_EIGENVALUE 			= 1006;
	public static final int RELATION_INVERSE					= 1007;
	public static final int RELATION_ONE_MAX					= 1999;
	
	public static final int RELATION_TWO_MIN					= 2000;
	public static final int RELATION_TWO_ADD 					= 2000;
	public static final int RELATION_TWO_SUBSTRACT 			= 2001;
	public static final int RELATION_TWO_MULTIPLY 			= 2002;
	public static final int RELATION_TWO_MERGER_HORIZON		= 2003;
	public static final int RELATION_TWO_MERGER_VERTICAL		= 2004;
	public static final int RELATION_TWO_MAX					= 2999;
	
	private int relation;
	private MatrixDisplay matrixDisplay1;
	private MatrixDisplay matrixDisplay2;
	private MatrixDisplay matrixDisplay3;

	@Override
	public void onDraw(Canvas canvas) {
		float midX = 0.0f;
		float midY = 0.0f;
		Paint paint = new Paint();
		paint.setAntiAlias(true);
		paint.setStrokeWidth(3.0f);
		paint.setStrokeCap(Cap.ROUND);
		paint.setStrokeJoin(Join.ROUND);
		paint.setARGB(50, 255, 255, 255);
		if(this.isRelationOne()) {
			midX = (this.matrixDisplay1.midX() + this.matrixDisplay2.midX()) * 0.5f;
			midY = (this.matrixDisplay1.midY() + this.matrixDisplay2.midY()) * 0.5f;
			canvas.drawLine(midX, midY, this.matrixDisplay2.midX(), this.matrixDisplay2.midY(), paint);
			PathEffect effects = new DashPathEffect(new float[]{2,2,5,5}, 1);
			paint.setPathEffect(effects);
			canvas.drawLine(midX, midY, this.matrixDisplay1.midX(), this.matrixDisplay1.midY(), paint);
		} else if(this.isRealtionTwo()) {
			midX = (this.matrixDisplay1.midX() + this.matrixDisplay3.midX()) * 0.5f;
			midY = (this.matrixDisplay1.midY() + this.matrixDisplay3.midY()) * 0.5f;
			canvas.drawLine(midX, midY, this.matrixDisplay3.midX(), this.matrixDisplay3.midY(), paint);
			PathEffect effects = new DashPathEffect(new float[]{2,2,5,5}, 1);
			paint.setPathEffect(effects);
			canvas.drawLine(midX, midY, this.matrixDisplay1.midX(), this.matrixDisplay1.midY(), paint);
			effects = new DashPathEffect(new float[]{5,5,5,5}, 1);
			paint.setPathEffect(effects);
			canvas.drawLine(midX, midY, this.matrixDisplay2.midX(), this.matrixDisplay2.midY(), paint);
		}
		paint.setPathEffect(null);
		paint.setARGB(150, 255, 255, 255);
		paint.setTextSize(18.0f * this.zoom);
		paint.setTextAlign(Align.CENTER);
		switch(this.relation) {
		case RELATION_ONE_TRANSPOSE:
			canvas.drawText("Transpose", midX, midY, paint);
			break;
		case RELATION_ONE_UPPER_TRIANGULAR:
			canvas.drawText("Upper Triangular", midX, midY, paint);
			break;
		case RELATION_ONE_LOWER_TRIANGULAR:
			canvas.drawText("Lower Triangular", midX, midY, paint);
			break;
		case RELATION_ONE_ADJONT:
			canvas.drawText("Adjont", midX, midY, paint);
			break;
		case RELATION_ONE_DETERMINANT:
			canvas.drawText("Determinant", midX, midY, paint);
			break;
		case RELATION_ONE_EIGENVALUE:
			canvas.drawText("Eigen Value", midX, midY, paint);
			break;
		case RELATION_TWO_ADD:
			canvas.drawText("Add", midX, midY, paint);
			break;
		case RELATION_TWO_SUBSTRACT:
			canvas.drawText("Substract", midX, midY, paint);
			break;
		case RELATION_TWO_MULTIPLY:
			canvas.drawText("Multiply", midX, midY, paint);
			break;
		case RELATION_TWO_MERGER_HORIZON:
			canvas.drawText("Horizon Merger", midX, midY, paint);
			break;
		case RELATION_TWO_MERGER_VERTICAL:
			canvas.drawText("Vertical Merger", midX, midY, paint);
			break;
		default:
			canvas.drawText("Undefined Relation", midX, midY, paint);
			break;
		}
	}
	
	public boolean isRelationOne() {
		return this.relation >= RELATION_ONE_MIN && this.relation <= RELATION_ONE_MAX;
	}
	
	public boolean isRealtionTwo() {
		return this.relation >= RELATION_TWO_MIN && this.relation <= RELATION_TWO_MAX;
	}

	public int getRelation() {
		return relation;
	}

	public void setRelation(int relation) {
		this.relation = relation;
	}

	public MatrixDisplay getMatrixDisplay1() {
		return matrixDisplay1;
	}

	public void setMatrixDisplay1(MatrixDisplay matrixDisplay1) {
		this.matrixDisplay1 = matrixDisplay1;
	}

	public MatrixDisplay getMatrixDisplay2() {
		return matrixDisplay2;
	}

	public void setMatrixDisplay2(MatrixDisplay matrixDisplay2) {
		this.matrixDisplay2 = matrixDisplay2;
	}

	public MatrixDisplay getMatrixDisplay3() {
		return matrixDisplay3;
	}

	public void setMatrixDisplay3(MatrixDisplay matrixDisplay3) {
		this.matrixDisplay3 = matrixDisplay3;
	}

}
