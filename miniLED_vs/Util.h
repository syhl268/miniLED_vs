#pragma once

#include <QRect>
#include <QPoint>

enum FacKind {
	K = 0, B,
};
enum FacRGB {
	FACRK = 0, FACRB, FACGK, FACGB, FACBK, FACBB,
};
enum PhotoRGB {
	R1, R2, G1, G2, B1, B2
};
bool PointInRect(QPoint point, QRect rect);

