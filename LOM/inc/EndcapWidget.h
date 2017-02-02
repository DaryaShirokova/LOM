#ifndef ENDCAPWIDGET_H
#define ENDCAPWIDGET_H

#define SECTOR_NUM 12

#include <QWidget>

class EndcapWidget : public QWidget
{
    Q_OBJECT


public:
    explicit EndcapWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) override;


signals:
    int coloredSector = -1;

public slots:
    void fillSector();
};

#endif // ENDCAPWIDGET_H
