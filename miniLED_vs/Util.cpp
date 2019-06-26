#include "Util.h"

bool PointInRect(QPoint point, QRect rect) {
	return point.x() >= rect.x() && point.y() >= rect.y() && point.x() <= rect.right() && point.y() <= rect.bottom();
}