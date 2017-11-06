#include"stdafx.h"
#include"Operate.h"
#include <iostream>
using namespace std;

Operate::Operate() {

	//初始化数据库  
	mysql_library_init(0, NULL, NULL);

	//初始化数据结构  
	mysql_init(&mydata);

	//在连接数据库之前，设置额外的连接选项  
	//可以设置的选项很多，这里设置字符集，否则无法处理中文  
	mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk");/*
	char host[128];
	char username[128];
	char password[128];
	char database[128];
	FILE *fp=fopen("config.txt","r");
	if (fp==NULL)
	{
		cout<<"config.txt not exist!"<<endl;
	}else
	{
		fscanf(fp,"%s",host);
		fscanf(fp,"%s",username);
		fscanf(fp,"%s",password);
		fscanf(fp,"%s",database);
		//cout<<username<<password<<database<<endl;
	}
	fclose(fp);*/
	//连接数据库  
	if(mysql_real_connect(&mydata, "119.29.15.91", "root", "root", "root", 3306, NULL, 0)==NULL)
	{
		cout<<"mysql_real_connect error!\n"<<endl;
	}
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
		"INSERT INTO User VALUES(null,'"+User.UserName+"','"+User.StudentId+"','"+User.Gender+"','"+User.PassWord+"','"+User.Image+"','"+User.UserQQ+"', '"+User.Phone+"','"+User.Email+"','"+User.University+"','"+User.LocateArea+"','"+User.SelfTag+"','"+IntToString(User.PlayTime)+"');";
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
		"INSERT INTO Event VALUES(null,'" + IntToString(Event.UserId) + "','" + Event.EventType + "','" + Event.PlaySite + "','" + Event.Arrival + "','" + Event.Publisher + "','" + Event.StartSite + "','" + Event.EndSite + "','" + Event.StartTime + "','" + IntToString(Event.PeersNumber) + "', '" + IntToString(Event.State) + "');";
	cout<<endl<<sqlstr<<endl<<endl;
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


bool Operate::UpdateUserTable(userStruct User)
{
	string sqlstr;
	sqlstr =
		"UPDATE User SET StudentId = '" + User.StudentId + "',Gender ='" + User.Gender + "',Image ='" + User.Image + "',UserQQ ='" + User.UserQQ + "',Phone ='" + User.Phone + "',Email ='" + User.Email + "',Univercity ='" + User.University + "',LocateArea ='" + User.LocateArea + "',SelfTag ='" + User.SelfTag + "' where UserName ='" + User.UserName + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::UpdatePassword(string UserName, string PassWord)
{
	string sqlstr;
	sqlstr =
		"UPDATE User SET PassWord ='" + PassWord + "' where UserName ='" + UserName + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::InsertIntoSecretSecurity(SecretSecurityStruct Security)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO SecretSecurity VALUES(null,'" + Security.UserName + "','" + Security.Security + "','"+ Security.Answer+"');";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

vector<ParticipantsStrcut> Operate::GetParticipantsByUsername(string Username)
{
	if (Username != "NULL")
	{
		vector<ParticipantsStrcut> Parti;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Participants where UserName =='" + Username + "'; ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				ParticipantsStrcut ps;
				ps.EventID = StringToInt(sql_row[0]);
				ps.UserName = sql_row[1];
				Parti.push_back(ps);
				sql_row = mysql_fetch_row(result);
			}
			return Parti;
		}
	}
}

vector<EventStruct> Operate::getEventByCondition(string publisher, string participant, int state)
{
	if (publisher != "NULL" && participant == "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where publisher ='" + publisher + "' and state = '" + IntToString(state) + "';";
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

	if (publisher == "NULL" && participant != "NULL")
	{
		vector<ParticipantsStrcut> Partis = GetParticipantsByUsername(participant);
		vector<EventStruct> Event;
		while (!Partis.empty())
		{
			ParticipantsStrcut ps = Partis.front();
			
			MYSQL_RES *result;
			MYSQL_ROW sql_row;
			string sqlstr;
			sqlstr =
				"select * from Event where EventID   ='" + IntToString(ps.EventID) + "' and State ='" +IntToString(state) + "';";
			
			if (0 == mysql_query(&mydata, sqlstr.c_str()))
			{
				result = mysql_store_result(&mydata);
				sql_row = mysql_fetch_row(result);
				if (sql_row != NULL)
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
				}
				
			}
			vector<ParticipantsStrcut>::iterator k = Partis.begin();
			Partis.erase(k);
		}
		return Event;
	}
}


SecretSecurityStruct Operate::GetSecretSecurity(string UserName)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from SecretSecurity where UserName ='" + UserName + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		SecretSecurityStruct Secret;
		Secret.SecretSecurityID = StringToInt( sql_row[0]);
		Secret.UserName = sql_row[1];
		Secret.Security = sql_row[2];
		Secret.Answer = sql_row[3];
		return Secret;
	}
	
}

string Operate::GetPasswordFromUserTable(string username)
{
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr; 
	sqlstr =
		"select PassWord from User where UserName ='" + username + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		if (sql_row != NULL)
		{
			//cout<<username<<" "<<sql_row[0]<<endl;
			return sql_row[0];
		}
		else
		{
			string s="";
			return s;
		}
		
	}
	else {
		string s="";
		return s;
	}
}

vector<userStruct> Operate::LikeUserName(string username)//模糊查找用户名
{
	if (username != "NULL")
	{
		vector<userStruct> User;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where UserName  like '" + username + "'; ";
		if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				userStruct us;
				us.UserID = StringToInt(sql_row[0]);
				us.UserName = sql_row[1];
				us.StudentId = (sql_row[2]);
				us.Gender = sql_row[3];
				us.PassWord = sql_row[4];
				us.Image = sql_row[5];
				us.UserQQ = sql_row[6];
				us.Phone = (sql_row[7]);
				us.Email = sql_row[8];
				us.University = sql_row[9];
				us.LocateArea = sql_row[10];
				us.SelfTag = sql_row[11];
				us.PlayTime = StringToInt(sql_row[12]);
				User.push_back(us);
				sql_row = mysql_fetch_row(result);
			}
			return User;
		}
	}

}

userStruct Operate::GetUserDetails(string username)
{
	userStruct us;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from User where UserName ='" + username + "';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		us.UserID = StringToInt(sql_row[0]);
		us.UserName = sql_row[1];
		us.StudentId = (sql_row[2]);
		us.Gender = sql_row[3];
		us.PassWord = sql_row[4];
		us.Image = sql_row[5];
		us.UserQQ = sql_row[6];
		us.Phone = (sql_row[7]);
		us.Email = sql_row[8];
		us.University = sql_row[9];
		us.LocateArea = sql_row[10];
		us.SelfTag = sql_row[11];
		us.PlayTime = StringToInt(sql_row[12]);
	}
	return us;
}

vector<EventStruct> Operate::GetEvent(string StartSite, string EndSite, string StartTime, string EventType)
{
	int flag =0;
	if (!(StartSite == "NULL" && EndSite == "NULL" && StartTime == "NULL" && EventType == "NULL"))
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where ";
		if (StartSite!="NULL")
		{
			sqlstr=sqlstr+"StartSite ='" + StartSite + "'";
			flag ++;
		}

		if (EndSite!="NULL")
		{
			if (flag)sqlstr = sqlstr +" and ";
			sqlstr=sqlstr+"EndSite ='" + EndSite + "'";
			flag ++;
		}

		if (StartTime!="NULL")
		{
			if (flag)sqlstr = sqlstr +" and ";
			sqlstr=sqlstr+"StartTime ='" + StartTime + "'";
			flag ++;
		}

		if (EventType!="NULL")
		{
			if (flag)sqlstr = sqlstr +" and ";
			sqlstr=sqlstr+"EventType ='" + EventType + "'";
			flag ++;
		}

	cout<<sqlstr<<endl;
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
	else	if (StartSite == "NULL" && EndSite == "NULL" && StartTime == "NULL" && EventType == "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event ;";
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

	if (StartSite != "NULL" && EndSite != "NULL" && StartTime != "NULL" && EventType == "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "' and EndSite ='" + EndSite + "' and StartTime='" + StartTime + "'";
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

	if (StartSite != "NULL" && EndSite != "NULL" && StartTime == "NULL" && EventType != "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "' and EndSite ='" + EndSite + "' and EventType='" + EventType + "' ";
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

	if (StartSite != "NULL" && EndSite == "NULL" && StartTime != "NULL" && EventType != "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite ='" + StartSite + "'and StartTime='" + StartTime + "'and EventType='" + EventType + "' ";
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

	if (StartSite == "NULL" && EndSite != "NULL" && StartTime != "NULL" && EventType != "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where  EndSite ='" + EndSite + "' and StartTime='" + StartTime + "'and EventType='" + EventType + "' ";
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

vector<EventStruct> Operate::GetEventByLike(string StartSite, string EndSite)
{
	if (StartSite != "NULL" && EndSite != "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite like '" + StartSite + "' and EndSite like '" + EndSite + "'; ";
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

	if (StartSite != "NULL" && EndSite == "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where StartSite like '" + StartSite + "'; ";
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

	if (StartSite == "NULL" && EndSite != "NULL")
	{
		vector<EventStruct> Event;
		MYSQL_RES *result;
		MYSQL_ROW sql_row;
		string sqlstr;
		sqlstr =
			"select * from Event where EndSite like '" + EndSite + "'; ";
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
		"update Event set State='"+IntToString(State)+"' where EventID='"+IntToString(Eventid)+"';";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

vector<string> Operate::GetParticipants(int EventID)
{
	vector<string> ps;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from Participants where EventID   =" +IntToString(EventID) + ";";
	cout<<sqlstr<<endl;
	if (0 == mysql_query(&mydata, sqlstr.c_str()))
		{
			result = mysql_store_result(&mydata);
			sql_row = mysql_fetch_row(result);
			while (sql_row != NULL)
			{
				ps.push_back(sql_row[1]);
				sql_row = mysql_fetch_row(result);
			}
		}
			return ps;
}

bool Operate::joinEvent(int EventID,string username)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO Participants VALUES('"+IntToString(EventID)+"','"+username+"');";
	//cout<<sqlstr<<endl;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		sqlstr =
		"update Event set PeersNumber = PeersNumber+1 where EventID='"+IntToString(EventID)+"';";
		mysql_query(&mydata, sqlstr.c_str());
		return true;
	}
	else {
		return false;
	}
}


EventStruct Operate::GetEventDetailById(int EventId)
{
	EventStruct Event;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select * from Event where EventID  ='" +IntToString(EventId) + "';";
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
			Event = es;
			sql_row = mysql_fetch_row(result);
		}
		return Event;
	}
}

bool Operate::DeleteDataParticipants(int EventID, string UserName)
{
	string sqlstr,sqlstr2;
	//向表中插入数据  
	sqlstr =
		"DELETE FROM Participants WHERE EventID = '"+IntToString(EventID)+"' and UserName = '"+ UserName +"';";
	//cout<<sqlstr<<endl;
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		sqlstr2 =
			"update Event set PeersNumber = PeersNumber-1 where EventID='" + IntToString(EventID) + "';";
		if (0 == mysql_query(&mydata, sqlstr2.c_str()))
		{
			return true;
		}
		
	}
	else {
		return false;
	}
}