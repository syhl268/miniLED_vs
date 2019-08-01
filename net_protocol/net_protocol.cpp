#include "net_protocol.h"
#include <QMutex>
#include <QException>

net_protocol::net_protocol()
{
}


TransMessage::TransMessage(QObject *parent)
	: QObject(parent)
{
	isValid = false;
}

TransMessage::~TransMessage()
{

}
//DRAW_IMG: Head0->0 Head1->1 func->2 width->3,4,5,6 height->7,8,9,10  data->11~
//DRAW_COLOR: Head0->0 Head1->1 func->2 R->3 G->4 B->5 A->6;
TransMessage::TransMessage(uchar * allData)
{
	if (allData == nullptr) {
		isValid = false;
		return;
	}
	else {

		if (allData[0] != this->Head0 || allData[1] != this->Head1) {
			isValid = false;
			return;
		}
		else {
			try {
				this->func = (Func)allData[2];
				switch (this->func) {
				case DRAW_COLOR:
					this->color = QColor(allData[3], allData[4], allData[5], allData[6]);
					break;
				case DRAW_IMG:
					//Ìí¼Ó»­Í¼Æ¬µÄ´úÂë


					//
					break;
				case CLOSE:
					isValid = true;
					return;
					break;
				default:
					break;
				}
			}
			catch (QException exp)
			{
				this->isValid = false;
				return;
			}
		}

	}
	isValid = true;
}

TransMessage::TransMessage(QColor color)
{
	this->func = DRAW_COLOR;
	this->color = color;
}

uchar * TransMessage::getAllData()
{
	uchar* allData;
	if (isValid) {
		switch (this->func)
		{
		case DRAW_COLOR:
			allData = new uchar[7];
			allData[0] = this->Head0;
			allData[1] = this->Head1;
			int r, g, b, a;
			this->color.getRgb(&r, &g, &b, &a);
			allData[2] = DRAW_COLOR;
			allData[3] = uchar(r);
			allData[4] = uchar(g);
			allData[5] = uchar(b);
			allData[6] = uchar(a);
			return allData;

			break;
		default:
			break;
		}
	}
	else

		return nullptr;
}

