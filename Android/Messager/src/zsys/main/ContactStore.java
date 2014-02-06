package zsys.main;

import android.content.Context;
import android.database.Cursor;
import android.net.Uri;

public class ContactStore 
{
	private static ContactStore instance;
	private String[] contactList;
	private Context context;
	
	private ContactStore()
	{
	}
	
	public static ContactStore getInstance()
	{
		if(instance == null)
		{
			instance = new ContactStore();
		}
		return instance;
	}
	
	public void bindContext(Context context)
	{
		this.context = context;
	}
	
	public boolean initialContact()
	{
		Uri uri = Uri.parse("content://contacts/people");
		Cursor cursor = context.getContentResolver().query(uri, null, null, null, null);
		if(cursor.moveToFirst())
		{
			int displayNameColumn = cursor.getColumnIndex("display_name");
			int contactNumber = 0;
			do
			{
				++contactNumber;
			}while(cursor.moveToNext());
			this.contactList = new String[contactNumber];
			cursor.moveToFirst();
			int i = 0;
			do
			{
				this.contactList[i] = cursor.getString(displayNameColumn);
				++i;
			}while(cursor.moveToNext());
		}
		return true;
	}
	
	public String findPersonByIndex(String index)
	{
		if(index == null)
		{
			return null;
		}
		int id = Integer.parseInt(index) - 1;
		return this.contactList[id];
	}
	
	public String findPersionByIndex(int index)
	{
		if(index < 0 || index >= this.contactList.length)
		{
			return null;
		}
		return this.contactList[index];
	}
}
