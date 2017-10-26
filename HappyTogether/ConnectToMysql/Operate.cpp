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
		"INSERT INTO user VALUES(null,"+User.UserName+","+IntToString(User.StudentId)+","+User.Gender+","+User.PassWord+","+User.Image+","+User.UserQQ+", "+IntToString(User.Phone)+","+User.Email+","+User.University+","+User.LocateArea+","+User.SelfTag+","+IntToString(User.PlayTime)+");";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::InsertIntoEventNameTable(EventNameStruct Event)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO EventName VALUES(null," + Event.EventType + "," + Event.PlaySite + "," + Event.Arrival + ");";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		return true;
	}
	else {
		return false;
	}
}

bool Operate::InsertIntoEventDetailsTable(EventDetailsStruct Event)
{
	string sqlstr;
	//向表中插入数据  
	sqlstr =
		"INSERT INTO EventDetails VALUES(null," + IntToString (Event.UserId) + "," + Event.Publisher + "," + Event.StartSite + "," + Event.EndSite + "," + Event.StartTime + "," +IntToString( Event.PeersNumber) + ", " +IntToString (Event.Success)+ ");";
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
		"INSERT INTO StationMessage VALUES(null," + StationMessage.SenderName + "," + StationMessage.ReceiverName + "," + StationMessage.Message + "," + StationMessage.Time + ");";
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
		"select PassWord from user where UserName =" + username + "";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		return sql_row[0];
	}
	else {
		return NULL;
	}
}


userStruct Operate::GetUserDetails(string username)
{
	userStruct us;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	string sqlstr;
	sqlstr =
		"select UserName,StudentId,Gender,PassWord,Image,UserQQ,Phone,Email,Univercity,LocateArea,SelfTag,PlayTime from user where UserName =" + username + "";
	if (0 == mysql_query(&mydata, sqlstr.c_str())) {
		result = mysql_store_result(&mydata);
		sql_row = mysql_fetch_row(result);
		us.UserName = sql_row[0];
		us.StudentId = StringToInt(sql_row[1]);
		us.Gender = sql_row[2];
		us.PassWord = sql_row[3];
		us.Image = sql_row[4];
		us.UserQQ = sql_row[5];
		us.Phone = StringToInt(sql_row[6]);
		us.Email = sql_row[7];
		us.University = sql_row[8];
		us.LocateArea = sql_row[9];
		us.SelfTag = sql_row[10];
		us.PlayTime = StringToInt(sql_row[11]);
	}
	return us;
}
/*
vector<EventDetailsStruct> Operate::GetEvent(string StartSite, string EndSite, string StartTime)
{

}

vector<StationMessageStruct> Operate::GetMessageBySender(string SenderName)
{

}
vector<StationMessageStruct> Operate::GetMessageByReceiver(string ReceiverName)
{

}
*/
