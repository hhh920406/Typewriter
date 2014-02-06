package zsys.main;

import java.text.SimpleDateFormat;
import java.util.Date;


public class MessageStructure 
{
	private String address;
	private String date;
	private String person;
	private String type;
	private String body;
	private Date trueDate;
	private String trueName;
	
	public String getAddress()
	{
		return this.address;
	}
	
	public String getDate()
	{
		return this.date;
	}
	
	public String getPerson()
	{
		return this.person;
	}
	
	public String getType()
	{
		return this.type;
	}
	
	public String getBody()
	{
		return this.body;
	}
	
	public Date getTrueDate()
	{
		return this.trueDate;
	}
	
	public String getTrueName()
	{
		return this.trueName;
	}
	
	public void setAddress(String address)
	{
		this.address = address;
	}
	
	public void setDate(String date)
	{
		this.date = date;
		this.parseDate();
	}
	
	public void setPerson(String person)
	{
		this.person = person;
		this.parsePerson();
	}
	
	public void setType(String type)
	{
		this.type = type;
	}
	
	public void setBody(String body)
	{
		this.body = body;
	}
	
	private void parseDate()
	{
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
	    this.trueDate = new Date(Long.parseLong(this.date));
		this.date = dateFormat.format(this.trueDate);
	}
	
	private void parsePerson()
	{
		ContactStore contactStore = ContactStore.getInstance();
		this.trueName = contactStore.findPersonByIndex(this.person);
	}
}
