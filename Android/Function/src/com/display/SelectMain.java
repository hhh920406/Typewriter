package com.display;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.SimpleAdapter;
import android.widget.AdapterView.OnItemClickListener;

public class SelectMain extends Activity 
{
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        GridView gridView = (GridView) findViewById(R.id.gridView);
        
        ArrayList<HashMap<String, Object>> imageItems = new ArrayList<HashMap<String, Object>>();
        HashMap<String, Object> map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.help);
        map.put("ItemText", getText(R.string.help));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.function1);
        map.put("ItemText", getText(R.string.function1));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.function2);
        map.put("ItemText", getText(R.string.function2));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.function3);
        map.put("ItemText", getText(R.string.function3));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.function4);
        map.put("ItemText", getText(R.string.function4));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.function5);
        map.put("ItemText", getText(R.string.function5));
        imageItems.add(map);
        map = new HashMap<String, Object>();
        map.put("ItemImage", R.drawable.about);
        map.put("ItemText", getText(R.string.about));
        imageItems.add(map);
        
        SimpleAdapter imageAdapter = new SimpleAdapter(this, imageItems, R.layout.selection,
        		new String[]{"ItemImage", "ItemText"}, new int[]{R.id.ItemImage, R.id.ItemText});
        gridView.setAdapter(imageAdapter);
        OnItemClickListener itemClick = new OnItemClickListener()
        {
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) 
			{
				Intent intent = new Intent();
				switch (arg2)
				{
				case 0:
					intent.setClass(SelectMain.this, Help.class);
					break;
				case 1:
					intent.setClass(SelectMain.this, Function1.class);
					break;
				case 2:
					intent.setClass(SelectMain.this, Function2.class);
					break;
				case 3:
					intent.setClass(SelectMain.this, Function3.class);
					break;
				case 4:
					intent.setClass(SelectMain.this, Function4.class);
					break;
				case 5:
					intent.setClass(SelectMain.this, Function5.class);
					break;
				case 6:
					intent.setClass(SelectMain.this, AboutUs.class);
					break;
				}
				startActivity(intent);
				SelectMain.this.finish();
			}
        	
        };
        gridView.setOnItemClickListener(itemClick);
    }
}