#pragma once

#include <QObject>
#include <qsql.h>
#include <qsqlquery.h>

/*
sqlite database db:
structure:

CREATE TABLE connection_type(id integer primary key autoincrement,netproto varchar(4),ip varchar,port int);
CREATE TABLE screen_para(id integer primary key autoincrement,screenW int,screenH int,boxW int,boxH int,moduleW int,moduleH int);
CREATE TABLE departSetting(id integer primary key autoincrement,departW int,departH int,depart_numW int,depart_numH int);
CREATE TABLE files(id integer primary key autoincrement,sourcefile varchar,dstfile varchar);
CREATE TABLE remark(id integer primary key autoincrement,time varchar,note varchar);

connection_type(id,netproto,ip,port);
screen_para(id,screenW,screenH,boxW,boxH,moduleW,moduleH);
departSetting(id,departW ,departH ,depart_numW,depart_numH);
files(id,sourcefile,dstfile);
remark(id,time,note);

CREATE TABLE sqlite_sequence(name,seq);
*/

struct DebugMsg {
	//connection_type,网络连接参数
	int id;
	QString netproto;
	QString	ip;
	int port;
	//screen_para,屏幕参数
	int screenW;
	int screenH;
	int boxW;
	int boxH;
	int moduleW;
	int moduleH;
	//departSetting
	int departW;
	int departH;
	int depart_numW;
	int depart_numH;
	//files,保存文件包含图片文件和结果文件
	QString sourcefile;
	QString dstfile;
	//remark,一些备注信息，时间备注
	QString dateTime;
	QString note;
};
DebugMsg* genDefaultDebugMsgInstance();
void setDebugMsgValue(
	DebugMsg *dm,
	int id,
QString netproto,
QString	ip,
int port,
//screen_para,屏幕参数
int screenW,
int screenH,
int boxW,
int boxH,
int moduleW,
int moduleH,
//departSetting
int departW,
int departH,
int depart_numW,
int depart_numH,
//files,保存文件包含图片文件和结果文件
QString sourcefile,
QString dstfile,
//remark,一些备注信息，时间备注
QString dateTime,
QString note
);

class DebugManager : public QObject
{
	Q_OBJECT

public:
	//int默认值 -> -1, QString默认值 ->"-1";

public:
	DebugManager(QObject *parent);
	~DebugManager();

	void addDebugMsg(DebugMsg dm);
	//index中是不完全信息，不是默认值的项作为索引在数据库中查找。
	QList<DebugMsg> getDebugMsgs(DebugMsg index);
	QList<DebugMsg> getAllDebugMsgs();
	int getErrorCode() {
		return errorCode;
	}

private:
	QSqlDatabase db;
	int errorCode;//0为正常，负数为失败
private:
	QSqlQuery DebugManager::execQueryCMD(QString cmdString, bool &isSuc);
};
