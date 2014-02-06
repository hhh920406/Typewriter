package com.zsys.main;

import com.zsys.R;
import com.zsys.view.CreateMatrixView1;
import com.zsys.view.CreateMatrixView2;
import com.zsys.view.EditMatrixView;
import com.zsys.view.HelpView;
import com.zsys.view.MainView;

import android.app.Activity;
import android.app.AlertDialog;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends Activity {
	public static final int SCENE_NULL			= 0;
	public static final int SCENE_STAGE 			= 1;
	public static final int SCENE_CREATE1 		= 2;
	public static final int SCENE_CREATE2 		= 3;
	public static final int SCENE_CREATE_CONFIRM = 4;
	public static final int SCENE_EDIT 			= 5;
	public static final int SCENE_EDIT_CONFIRM 	= 6;
	public static final int SCENE_HELP		    = 7;
	
	private static final int MENU_QUIT = Menu.FIRST;
	private static final int MENU_HELP = Menu.FIRST + 1;
	private static final int MENU_ABOUT = Menu.FIRST + 2;
	public static final int MENU_NUMBER = 1;
	
	private MainView mainView;
	private CreateMatrixView1 createMatrixView1;
	private CreateMatrixView2 createMatrixView2;
	private EditMatrixView editMatrixView;
	private HelpView helpView;
	private Matrix transferMatrix;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.transferMatrix = new Matrix();
        this.initialViews();
        this.loadResource();
        this.setCurrentView(SCENE_NULL, SCENE_STAGE);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu)
    {
    	menu.add(0, MENU_QUIT, 2, "Exit");
    	menu.add(0, MENU_HELP, 1, "Help");
    	menu.add(0, MENU_ABOUT, 0, "About");
    	return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem menuItem)
    {
    	switch(menuItem.getItemId())
    	{
    	case MENU_QUIT:
    		this.finish();
    		break;
    	case MENU_HELP:
    		this.setCurrentView(SCENE_NULL, SCENE_HELP);
    		break;
    	case MENU_ABOUT:
    		new AlertDialog.Builder(this).setTitle("About Us").setMessage("Version 1.0.0\nZsys Studio 2012").show();
    		break;
    	}
    	return super.onOptionsItemSelected(menuItem);
    }
    
    private void initialViews() {
        this.mainView = new MainView(this);
        this.createMatrixView1 = new CreateMatrixView1();
        this.createMatrixView2 = new CreateMatrixView2();
        this.editMatrixView = new EditMatrixView();
        this.helpView = new HelpView();
        this.mainView.setActivity(this);
        this.createMatrixView1.setActivity(this);
        this.createMatrixView2.setActivity(this);
        this.editMatrixView.setActivity(this);
        this.helpView.setActivity(this);
    }
    
    private void loadResource() {
    	BitmapSource.button[BitmapSource.BUTTON_CREATE] = BitmapFactory.decodeResource(this.getResources(), R.drawable.create);
    	BitmapSource.button[BitmapSource.BUTTON_DELETE] = BitmapFactory.decodeResource(this.getResources(), R.drawable.delete);
    	BitmapSource.button[BitmapSource.BUTTON_EDIT] = BitmapFactory.decodeResource(this.getResources(), R.drawable.edit);
    	BitmapSource.button[BitmapSource.BUTTON_MOVE] = BitmapFactory.decodeResource(this.getResources(), R.drawable.move);
    	BitmapSource.button[BitmapSource.BUTTON_ZOOMIN] = BitmapFactory.decodeResource(this.getResources(), R.drawable.zoomin);
    	BitmapSource.button[BitmapSource.BUTTON_ZOOMOUT] = BitmapFactory.decodeResource(this.getResources(), R.drawable.zoomout);
    }

	public Matrix getTransferMatrix() {
		return transferMatrix;
	}

	public void setCurrentView(int fromView, int targetView) {
		switch(targetView) {
		case SCENE_STAGE:
			switch(fromView) {
			case SCENE_CREATE_CONFIRM:
				this.mainView.addMatrix(this.transferMatrix);
				break;
			case SCENE_EDIT_CONFIRM:
				this.mainView.editMatrix(this.transferMatrix);
				break;
			}
			this.setContentView(this.mainView);
			break;
		case SCENE_CREATE1:
			this.setContentView(R.layout.creatematrix1);
	        this.createMatrixView1.addButtonListener();
			break;
		case SCENE_CREATE2:
			this.setContentView(R.layout.creatematrix2);
			this.createMatrixView2.addButtonListener();
			break;
		case SCENE_EDIT:
			this.setContentView(R.layout.editmatrix);
			this.editMatrixView.addButtonListener();
			break;
		case SCENE_HELP:
			this.setContentView(R.layout.help);
			this.helpView.addButtonListener();
			break;
		}
	}
}