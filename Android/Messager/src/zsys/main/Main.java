package zsys.main;

import java.util.ArrayList;
import java.util.HashMap;

import com.zsys.R;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class Main extends Activity 
{
	private CheckBox dateCheckBox;
	private CheckBox nameCheckBox;
	private CheckBox bodyCheckBox;
	private DatePicker startDatePicker;
	private DatePicker endDatePicker;
	private EditText nameEditText;
	private EditText bodyEditText;
	private Button searchButton;
	
	private boolean[] suitable;
	private int suitableNumber;
	
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        ContactStore contact = ContactStore.getInstance();
        contact.bindContext(this.getApplicationContext());
        contact.initialContact();
        MessageStore message = MessageStore.getInstance();
        message.bindContext(this.getApplicationContext());
        message.initialMessage();
        this.initialOptionView();
    }
    
    private void initialOptionView()
    {
        this.setContentView(R.layout.main);
    	this.dateCheckBox = (CheckBox) this.findViewById(R.id.dateCheckBox);
    	this.nameCheckBox = (CheckBox) this.findViewById(R.id.nameCheckBox);
    	this.bodyCheckBox = (CheckBox) this.findViewById(R.id.bodyCheckBox);
    	this.startDatePicker = (DatePicker) this.findViewById(R.id.startDatePicker);
    	this.endDatePicker = (DatePicker) this.findViewById(R.id.endDatePicker);
    	this.nameEditText = (EditText) this.findViewById(R.id.nameEditText);
    	this.bodyEditText = (EditText) this.findViewById(R.id.bodyEditText);
    	this.searchButton = (Button) this.findViewById(R.id.searchButton);
    	MessageStore message = MessageStore.getInstance();
    	this.suitable = new boolean[message.getLength()];
    	this.searchButton.setOnClickListener(new Button.OnClickListener()
        {
			@Override
			public void onClick(View v) 
			{
				search();
				initialResultView();
			}
        });
    }
    
    private void initialResultView()
    {
    	this.setContentView(R.layout.result);
    	TextView resultTextEdit = (TextView) this.findViewById(R.id.resultTextView);
    	if(this.suitableNumber == 0)
    	{
    		resultTextEdit.setText("没有搜索到符合条件的结果");
    	}
    	else
    	{
    		resultTextEdit.setText("共有" + this.suitableNumber + "个符合条件的结果");
    	}
    	MessageStore message = MessageStore.getInstance();
    	ListView resultListView = (ListView) findViewById(R.id.resultListView);
        ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();  
        for(int i=0;i<this.suitable.length;i++)  
        {
        	if(this.suitable[i])
        	{
	            HashMap<String, Object> map = new HashMap<String, Object>();  
	            map.put("Name", "联系人：" + message.getName(i));
	            map.put("Body", "内容：" + message.getBody(i));  
	            map.put("Date", "发送日期：" + message.getDate(i).toLocaleString());  
	            listItem.add(map);
        	}
        }   
        SimpleAdapter listItemAdapter = new SimpleAdapter(this,listItem,  
                R.layout.item,
                new String[] {"Name","Body","Date"},   
                new int[] {R.id.listNameTextView,R.id.listBodyTextView,R.id.listDateTextView}  
            );
        resultListView.setAdapter(listItemAdapter);
    	
    	Button backButton = (Button) this.findViewById(R.id.backButton);
    	backButton.setOnClickListener(new Button.OnClickListener()
        {
			@Override
			public void onClick(View v) 
			{
				initialOptionView();
			}
        });
    }
    
    private void search()
    {
    	for(int i=0;i<this.suitable.length;++i)
    	{
    		this.suitable[i] = true;
    	}
    	if(this.dateCheckBox.isChecked())
    	{
    		this.searchDate();
    	}
    	if(this.nameCheckBox.isChecked())
    	{
    		this.searchName();
    	}
    	if(this.bodyCheckBox.isChecked())
    	{
    		this.searchBody();
    	}
    	this.suitableNumber = 0;
    	for(int i=0;i<this.suitable.length;++i)
    	{
    		if(this.suitable[i])
    		{
    			this.suitableNumber++;
    		}
    	}
    }
    
    private long convertDate(int year, int month, int day)
    {
    	return (long)year * 1000000 + month * 100 + day;
    }
    
    private void searchDate()
    {
    	long startDate = this.convertDate(this.startDatePicker.getYear(),
    			this.startDatePicker.getMonth(),
    			this.startDatePicker.getDayOfMonth());
    	long endDate = this.convertDate(this.endDatePicker.getYear(),
    			this.endDatePicker.getMonth(),
    			this.endDatePicker.getDayOfMonth());
    	MessageStore message = MessageStore.getInstance();
    	for(int i=0;i<this.suitable.length;++i)
    	{
    		if(this.suitable[i])
    		{
    			long tempDate = this.convertDate(message.getDate(i).getYear(),
    					message.getDate(i).getMonth(),
    					message.getDate(i).getDay());
    			if(tempDate<startDate || tempDate>endDate)
    			{
    				this.suitable[i] = false;
    			}
    		}
    	}
    }
    
    private void searchName()
    {
    	MessageStore message = MessageStore.getInstance();
    	for(int i=0;i<this.suitable.length;++i)
    	{
    		if(this.suitable[i])
    		{
    			if(!message.getName(i).contains(this.nameEditText.getText()))
    			{
    				this.suitable[i] = false;
    			}
    		}
    	}
    }
    
    private void searchBody()
    {
    	MessageStore message = MessageStore.getInstance();
    	for(int i=0;i<this.suitable.length;++i)
    	{
    		if(this.suitable[i])
    		{
    			if(!message.getBody(i).contains(this.bodyEditText.getText()))
    			{
    				this.suitable[i] = false;
    			}
    		}
    	}
    }
    
}