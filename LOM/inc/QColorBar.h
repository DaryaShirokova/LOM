#ifndef QCOLORBAR_H
#define QCOLORBAR_H

#include <QWidget>
#include <QColor>

class QColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit QColorBar(QWidget *parent = 0);
    ~QColorBar() {}
    static QColor GetColor(double val);
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    const int shadesNumber = 40;

signals:

public slots:
};

#endif // QCOLORBAR_H
