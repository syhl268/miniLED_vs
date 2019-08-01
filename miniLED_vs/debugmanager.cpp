#include "debugmanager.h"
#include <qdebug.h>

DebugMsg* genDefaultDebugMsgInstance() {
	DebugMsg *dm;
	dm->id = -1;
	dm->netproto = "-1";
	dm->ip = "-1";
	dm->port = -1;
	dm->screenW = -1;
	dm->screenH = -1;
	dm->boxW = -1;
	dm->boxH = -1;
	dm->moduleW = -1;
	dm->moduleH = -1;
	dm->departW = -1;
	dm->departH = -1;
	dm->depart_numW = -1;
	dm->depart_numH = -1;
	dm->sourcefile = "-1";
	dm->dstfile = "-1";
	dm->dateTime = "-1";
	dm->note = "-1";
	return dm;
}
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
	QString note)
{
	dm->id = id;
	dm->netproto = netproto;
	dm->ip = ip;
	dm->port = port;
	dm->screenW = screenW;
	dm->screenH = screenH;
	dm->boxW = boxW;
	dm->boxH = boxH;
	dm->moduleW = moduleW;
	dm->moduleH = moduleH;
	dm->departW = departW;
	dm->departH = departH;
	dm->depart_numW = depart_numW;
	dm->depart_numH = depart_numH;
	dm->sourcefile = sourcefile;
	dm->dstfile = dstfile;
	dm->dateTime = dateTime;
	dm->note = note;
}
DebugManager::DebugManager(QObject *parent)
	: QObject(parent)
{
	this->db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("miniLed_debug.db");
	db.setUserName("lwh");
	db.setPassword("root");
	if (!db.open())
	{
		errorCode = -1;
#ifdef _DEBUG
		qDebug() << "Failure to open database miniLed_debug.db";

#endif // _DEBUG
	}
	else
	{
		errorCode = 0;
#ifdef  _DEBUG
		qDebug() << "Success to open database";
#endif //  _DEBUG

	}
	
}

DebugManager::~DebugManager()
{

}

void DebugManager::addDebugMsg(DebugMsg dm)
{
	bool isSuc = false;
	QString cmd;
	QSqlQuery sq = execQueryCMD(cmd.sprintf("insert into connection_type( netproto, ip, port) values('%s','%s',%d)",dm.netproto,dm.ip,dm.port),isSuc);
	sq = execQueryCMD(cmd.sprintf("insert into screen_para(screenW, screenH, boxW, boxH, moduleW, moduleH) values(%d,%d,%d,%d,%d,%d",dm.screenW,dm.screenH,dm.boxW,dm.boxH,dm.moduleW,dm.moduleH), isSuc);
	sq = execQueryCMD(cmd.sprintf("insert into departSetting(departW, departH, depart_numW, depart_numH) values (%d,%d,%d,%d)",dm.departW,dm.departH,dm.depart_numW,dm.depart_numH), isSuc);
	sq = execQueryCMD(cmd.sprintf("insert into files( sourcefile, dstfile) values (&s,'%s')",dm.sourcefile,dm.dstfile), isSuc);
	sq = execQueryCMD(cmd.sprintf("insert into remark( time, note) values (datetime(now),'%s')",dm.note), isSuc);
	
}

QList<DebugMsg> DebugManager::getDebugMsgs(DebugMsg index)
{

	return QList<DebugMsg>();
}

QList<DebugMsg> DebugManager::getAllDebugMsgs()
{
	QList<DebugMsg> dmList;
	
	bool isSuc = false;
	QSqlQuery query = execQueryCMD("select "
		"connection_type.id,"
		"connection_type.netproto,"
		"connection_type.ip,"
		"connection_type.port,"
		"screen_para.screenW,"
		"screen_para.screenH,"
		"screen_para.boxW,"
		"screen_para.boxH,"
		"screen_para.moduleW,"
		"screen_para.moduleH,"
		"departSetting.departW,"
		"departSetting.departH,"
		"departSetting.depart_numW,"
		"departSetting.depart_numH,"
		"files.sourcefile,"
		"files.dstfile,"
		"remark.time,"
		"remark.note"
		"from connection_type,screen_para,departSetting,files,remark"
		"where connection_type.id=screen_para.id=departSetting.id=files.id=remark.id"
		,isSuc);
	while (query.next())
	{
		DebugMsg *dm = genDefaultDebugMsgInstance();
		setDebugMsgValue(dm, query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toInt(),
			query.value(4).toInt(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt(),
			query.value(9).toInt(), query.value(10).toInt(), query.value(11).toInt(), query.value(12).toInt(), query.value(13).toInt(),
			query.value(14).toString(), query.value(15).toString(), query.value(16).toString(), query.value(17).toString());
		dmList.push_back(*dm);
	}
	return dmList;
}

QSqlQuery DebugManager::execQueryCMD(QString cmdString,bool &isSuc)
{
	QSqlQuery query;
	if (query.exec(cmdString)) {
#ifdef _DEBUG
		qDebug() << cmdString<<"\tQuery to database success!";
#endif
		isSuc = true;
	}
#ifdef _DEBUG
	qDebug() <<cmdString<< "\tFailuer to Query";
#endif // _DEBUG

	isSuc = false;
	return query;
}


