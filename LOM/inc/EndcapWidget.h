#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#define SECTOR_NUM 16//12

#include <QWidget>
#include <QPoint>
#include <QString>

class EndcapWidget : public QWidget
{
    Q_OBJECT


public:
    explicit EndcapWidget(QWidget *parent = 0);
    ~EndcapWidget() {}

    void SetSectorColor(QString color) { this->sectorColor = color; }
    void SetFilledSector(unsigned int sector) {
        if (sector > SECTOR_NUM || sector < 1)
            return;
        this->filledSector = sector;
    }

protected:
    void paintEvent(QPaintEvent *event) override;

private:

    int filledSector;
    QPoint GetRayCircleIntersection(int x0, int y0, int r, double alpha);
    QString sectorColor;

//QObject::connect(pushButton, SIGNAL(clicked()), LOMView, SLOT(show()));
signals:
    void SectorChanged();

public slots:
    void FillSector();
};

#endif // ENDCAPWIDGET_H
