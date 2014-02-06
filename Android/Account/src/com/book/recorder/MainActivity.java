package com.book.recorder;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Locale;

import com.zhg.recorder.R;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.RadioButton;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class MainActivity extends FragmentActivity {

    SectionsPagerAdapter mSectionsPagerAdapter;

    ViewPager mViewPager;
    
    public static AccountDataSet data = new AccountDataSet();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        mSectionsPagerAdapter = new SectionsPagerAdapter(
                getSupportFragmentManager());
        mSectionsPagerAdapter.setMain(this);

        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mSectionsPagerAdapter);

        load();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    public void save() {
		SharedPreferences shared = this.getSharedPreferences("Data", Context.MODE_PRIVATE);
		Editor edit = shared.edit();
		edit.putInt("num", data.len());
		for (int i = 0; i < data.len(); ++i) {
			edit.putLong("id_" + i, data.get(i).id);
			edit.putInt("year_" + i, data.get(i).year);
			edit.putInt("month_" + i, data.get(i).month);
			edit.putInt("day_" + i, data.get(i).day);
			edit.putFloat("amount_" + i, data.get(i).amount);
			edit.putBoolean("income_" + i, data.get(i).isIncome);
			edit.putString("des_" + i, data.get(i).description);
		}
		edit.commit();
    }
    
    public void load() {
    	SharedPreferences shared = this.getSharedPreferences("Data", Context.MODE_PRIVATE);
    	int len = shared.getInt("num", 0);
    	for (int i = 0; i < len; ++i) {
    		AccountData node = new AccountData();
    		node.id = shared.getLong("id_" + i, 0);
    		node.year = shared.getInt("year_" + i, 0);
    		node.month = shared.getInt("month_" + i, 0);
    		node.day = shared.getInt("day_" + i, 0);
    		node.amount = shared.getFloat("amount_" + i, 0.0f);
    		node.isIncome = shared.getBoolean("income_" + i, false);
    		node.description = shared.getString("des_" + i, "");
    		data.add(node);
    	}
    }

    public class SectionsPagerAdapter extends FragmentPagerAdapter {

        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }
        
        public MainActivity act;
        
        public void setMain(MainActivity act) {
        	this.act = act;
        }

        @Override
        public Fragment getItem(int position) {
            Fragment fragment = new SectionFragment();
            ((SectionFragment)fragment).setMain(act);
            Bundle args = new Bundle();
            args.putInt(SectionFragment.ARG_SECTION_NUMBER, position + 1);
            fragment.setArguments(args);
            return fragment;
        }

        @Override
        public int getCount() {
            return 4;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            Locale l = Locale.getDefault();
            switch (position) {
            case 0:
                return getString(R.string.title_section2).toUpperCase(l);
            case 1:
                return getString(R.string.title_section1).toUpperCase(l);
            case 2:
                return getString(R.string.title_section3).toUpperCase(l);
            case 3:
                return getString(R.string.title_section4).toUpperCase(l);
            }
            return null;
        }
    }

    public static class SectionFragment extends Fragment {
        public static final String ARG_SECTION_NUMBER = "section_number";

        public SectionFragment() {
        }
        
        public MainActivity act;
        
        public void setMain(MainActivity act) {
        	this.act = act;
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
        	switch (getArguments().getInt(ARG_SECTION_NUMBER))
        	{
        	case 1:
        		return create2(inflater, container, savedInstanceState);
        	case 2:
        		return create1(inflater, container, savedInstanceState);
        	case 3:
        		return create3(inflater, container, savedInstanceState);
        	default:
        		return create4(inflater, container, savedInstanceState);
        	}
        }
        
        public View create1(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState)
        {
        	View rootView = inflater.inflate(R.layout.layout_1, container, false);
        	Button button = (Button)rootView.findViewById(R.id.buttonAdd);
        	AddListener listener = new AddListener();
        	listener.setMain(act);
        	listener.setRoot(rootView);
        	button.setOnClickListener(listener);
        	return rootView;
        }

        class AddListener implements OnClickListener {
            public MainActivity act;
            public View root;
            
            public void setMain(MainActivity act) {
            	this.act = act;
            }
            
            public void setRoot(View v) {
            	this.root = v;
            }
            
        	public void onClick(View v) {
        		DatePicker datePicker = (DatePicker)root.findViewById(R.id.datePicker);
        		AccountData node = new AccountData();
        		node.year = datePicker.getYear();
        		node.month = datePicker.getMonth();
        		node.day = datePicker.getDayOfMonth();
        		EditText editTextAmount = (EditText)root.findViewById(R.id.editTextAmount);
        		node.amount = Float.parseFloat(editTextAmount.getText().toString());
        		EditText editTextDes = (EditText)root.findViewById(R.id.editTextDes);
        		node.description = editTextDes.getText().toString();
        		RadioButton radioIncome = (RadioButton)root.findViewById(R.id.radioIncome);
        		if (radioIncome.isChecked()) {
        			node.isIncome = true;
        		} else {
        			node.isIncome = false;
        		}
        		MainActivity.data.add(node);
        		act.save();
        		editTextAmount.setText("");
        		editTextDes.setText("");
        	}
        }
        
        public View create2(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState)
        {
        	View rootView = inflater.inflate(R.layout.layout_2, container, false);
        	ListView resultListView = (ListView) rootView.findViewById(R.id.listView1);
            ArrayList<HashMap<String, Object>> listItem = new ArrayList<HashMap<String, Object>>();  
            for (int i = 0; i < MainActivity.data.len(); ++i)  
            {
    	            HashMap<String, Object> map = new HashMap<String, Object>();  
    	            map.put("Date", MainActivity.data.get(i).year + "/" + 
    	            		MainActivity.data.get(i).month + "/" + 
    	            		MainActivity.data.get(i).day + " ");
    	            map.put("Body", MainActivity.data.get(i).description);
    	            if (data.get(i).isIncome) {
        	            map.put("Income", "гд" + MainActivity.data.get(i).amount);  
        	            map.put("Outcome", "");  
    	            } else {
        	            map.put("Income", "");  
        	            map.put("Outcome", "гд" + MainActivity.data.get(i).amount);  
    	            }
    	            listItem.add(map);
            }   
            SimpleAdapter listItemAdapter = new SimpleAdapter(this.act, listItem,  
                    R.layout.layout_item,
                    new String[] {"Date","Body","Income", "Outcome"},   
                    new int[] {R.id.textViewDate, R.id.textViewDes, R.id.textViewIncome, R.id.textViewOutcome}  
                );
            resultListView.setAdapter(listItemAdapter);
        	return rootView;
        }
        
        public View create3(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState)
        {
        	View rootView = inflater.inflate(R.layout.layout_3, container, false);
        	TextView text = (TextView)rootView.findViewById(R.id.textView4);
        	text.setText("" + MainActivity.data.totalIncome());
        	text = (TextView)rootView.findViewById(R.id.textView5);
        	text.setText("" + MainActivity.data.totalOutcome());
        	text = (TextView)rootView.findViewById(R.id.textView6);
        	text.setText("" + MainActivity.data.total());
        	return rootView;
        }
        
        public View create4(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState)
        {
        	View rootView = inflater.inflate(R.layout.layout_4, container, false);
        	return rootView;
        }
    }
}