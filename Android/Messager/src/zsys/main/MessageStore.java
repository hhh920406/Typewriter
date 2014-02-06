package zsys.main;


import java.util.Date;

import android.content.Context;
import android.database.Cursor;
import android.net.Uri;

public class MessageStore
{
	private static MessageStore instance;
	private MessageStructure[] messageList;
	private Context context;
	
	private MessageStore()
	{
	}
	
	public void bindContext(Context context)
	{
		this.context = context;
	}
	
	public static MessageStore getInstance()
	{
		if(instance == null)
		{
			instance = new MessageStore();
		}
		return instance;
	}
	
	public boolean initialMessage()
	{
		Uri uri = Uri.parse("content://sms/");
		Cursor cursor = context.getContentResolver().query(uri, null, null, null, null);
		if(cursor.moveToFirst())
		{
			int addressColumn = cursor.getColumnIndex("address");
			int personColumn = cursor.getColumnIndex("person");
			int dateColumn = cursor.getColumnIndex("date");
			int typeColumn = cursor.getColumnIndex("type");
			int bodyColumn = cursor.getColumnIndex("body");
			int messageNumber = 0;
			do
			{
				++messageNumber;
			}while(cursor.moveToNext());
			System.out.println(messageNumber);
			this.messageList = new MessageStructure[messageNumber];
			cursor.moveToFirst();
			int i = 0;
			do
			{
				this.messageList[i] = new MessageStructure();
				this.messageList[i].setAddress(cursor.getString(addressColumn));
				this.messageList[i].setPerson(cursor.getString(personColumn));
				this.messageList[i].setDate(cursor.getString(dateColumn));
				this.messageList[i].setType(cursor.getString(typeColumn));
				this.messageList[i].setBody(cursor.getString(bodyColumn));
				++i;
			}while(cursor.moveToNext());
		}
		return true;
	}

	public int getLength()
	{
		return this.messageList.length;
	}
	
	public Date getDate(int index)
	{
		return this.messageList[index].getTrueDate();
	}
	
	public String getName(int index)
	{
		if(this.messageList[index].getTrueName() == null)
		{
			return messageList[index].getAddress();
		}
		return this.messageList[index].getTrueName();
	}
	
	public String getBody(int index)
	{
		return this.messageList[index].getBody();
	}
}
