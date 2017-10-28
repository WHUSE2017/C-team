#include"stdafx.h"
#include"Operate.h"


Operate::Operate() {

	//初始化数据库  
	mysql_library_init(0, NULL, NULL);

	//初始化数据结构  
	mysql_init(&mydata);

	//在连接数据库之前，设置额外的连接选项  
	//可以设置的选项很多，这里设置字符集，否则无法处理中文  
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");

	//连接数据库  
	mysql_real_connect(&mydata, "localhost", "root", "root", "root", 3306, NULL, 0);
}

string Operate::IntToString(int variable)
{
	stringstream ss;
	string str;
	ss << variable;
	ss >> str;
	return str;
}

int Operate::StringToInt(string variable)
{
	return atoi(variable.c_str());
}


bool Operate::InsertIntoUserTable(userStruct User) {
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO user VALUES(null,'"+User.UserName+"','"+IntToString(User.StudentId)+"','"+User.Gender+"','"+User.PassWord+"','"+User.Image+"','"+User.UserQQ+"', '"+IntToString(User.Phone)+"','"+User.Email+"','"+User.University+"','"+User.LocateArea+"','"+User.SelfTag+"','"+IntToString(User.PlayTime)+"');";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::InsertIntoEventTable(EventStruct Event)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO event VALUES(null,'" + IntToString(Event.UserId) + "','" + Event.EventType + "','" + Event.PlaySite + "','" + Event.Arrival + "','" + Event.Publisher + "','" + Event.StartSite + "','" + Event.EndSite + "','" + Event.StartTime + "','" + IntToString(Event.PeersNumber) + "', '" + IntToString(Event.State) + "');";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::InsertIntoStationMessageable(StationMessageStruct StationMessage)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO StationMessage VALUES(null,'" + StationMessage.SenderName + "','" + StationMessage.ReceiverName + "','" + StationMessage.Message + "','" + StationMessage.Time + "');";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

string Operate::GetPasswordFromUserTable(string username)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr; 
	sqlstr =
		"select PassWord from user where UserName ='" + username + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		if (sql_row != NULL)
		{
			return sql_row[0];
		}
		else
		{
			return 0;
		}
		
	}
	else {
		return "NULL";
	}
}


userStruct Operate::GetUserDetails(string username)
{
	userStruct us;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from user where UserName ='" + username + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		us.UserID = StringToInt(sql_row[0]);
		us.UserName = sql_row[1];
		us.StudentId = StringToInt(sql_row[2]);
		us.Gender = sql_row[3];
		us.PassWord = sql_row[4];
		us.Image = sql_row[5];
		us.UserQQ = sql_row[6];
		us.Phone = StringToInt(sql_row[7]);
		us.Email = sql_row[8];
		us.University = sql_row[9];
		us.LocateArea = sql_row[10];
		us.SelfTag = sql_row[11];
		us.PlayTime = StringToInt(sql_row[12]);
	}
	return us;
}

vector<EventStruct> Operate::GetEvent(string StartSite, string EndSite, string StartTime,int UserId)
{
	if (StartSite != "NULL" && EndSite !="NULL" && StartTime !="NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "' and EndSite ='" + EndSite + "' and StartTime='" + StartTime + "' ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite != "NULL" && EndSite == "NULL" && StartTime == "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "'";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite == "NULL" && EndSite != "NULL" && StartTime == "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where EndSite ='" + EndSite + "'";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite == "NULL" && EndSite == "NULL" && StartTime != "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartTime ='" + StartTime + "'";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite != "NULL" && EndSite != "NULL" && StartTime == "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "' and EndSite='"+ EndSite +"' ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite != "NULL" && EndSite == "NULL" && StartTime != "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "' and StartTime='" + StartTime + "' ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite == "NULL" && EndSite != "NULL" && StartTime != "NULL" && UserId == 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where EndSite ='" + EndSite + "' and StartTime='" + StartTime + "' ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}

	if (StartSite == "NULL" && EndSite == "NULL" && StartTime == "NULL" && UserId != 0)
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where UserId ='" +IntToString (UserId) + "'";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				EventStruct es;
				es.EventID = StringToInt(sql_row[0]);
				es.UserId = StringToInt(sql_row[1]);
				es.EventType = sql_row[2];
				es.PlaySite = sql_row[3];
				es.Arrival = sql_row[4];
				es.Publisher = sql_row[5];
				es.StartSite = sql_row[6];
				es.EndSite = sql_row[7];
				es.StartTime = sql_row[8];
				es.PeersNumber = StringToInt(sql_row[9]);
				es.State = StringToInt(sql_row[10]);
				Event.push_back(es);
				sql_row = mysql_fetch_row(result);
			}
			return Event;
		}
	}


}

vector<EventStruct> Operate::GetEventByState(int State)
{
	vector<EventStruct> Event;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from Event where State ='" +IntToString(State) + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		while (sql_row != NULL)
		{
			EventStruct es;
			es.EventID = StringToInt(sql_row[0]);
			es.UserId = StringToInt(sql_row[1]);
			es.EventType = sql_row[2];
			es.PlaySite = sql_row[3];
			es.Arrival = sql_row[4];
			es.Publisher = sql_row[5];
			es.StartSite = sql_row[6];
			es.EndSite = sql_row[7];
			es.StartTime = sql_row[8];
			es.PeersNumber = StringToInt(sql_row[9]);
			es.State = StringToInt(sql_row[10]);
			Event.push_back(es);
			sql_row = mysql_fetch_row(result);
		}
		return Event;
	}
}

bool Operate::setEventState(int Eventid,int State)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"update Event set State='"+IntToString(State)+"' where EventID='"+IntToString(State)+"';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

vector<StationMessageStruct> Operate::GetMessageBySender(string SenderName)
{
	vector<StationMessageStruct> Message;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from StationMessage where SenderName ='" + SenderName + "'";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		while (sql_row != NULL)
		{
			StationMessageStruct sms;
			sms.MessageID = StringToInt(sql_row[0]);
			sms.SenderName = sql_row[1];
			sms.ReceiverName = sql_row[2];
			sms.Message = sql_row[3];
			sms.Time = sql_row[4];
			Message.push_back(sms);
			sql_row = mysql_fetch_row(result);
		}
		return Message;
	}
}
vector<StationMessageStruct> Operate::GetMessageByReceiver(string ReceiverName)
{
	vector<StationMessageStruct> Message;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from StationMessage where ReceiverName ='" + ReceiverName + "'";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		while (sql_row != NULL)
		{
			StationMessageStruct sms;
			sms.MessageID = StringToInt(sql_row[0]);
			sms.SenderName = sql_row[1];
			sms.ReceiverName = sql_row[2];
			sms.Message = sql_row[3];
			sms.Time = sql_row[4];
			Message.push_back(sms);
			sql_row = mysql_fetch_row(result);
		}
		return Message;
	}
}

