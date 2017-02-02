#ifndef LOMVIEW_H
#define LOMVIEW_H

#include <QMainWindow>

namespace Ui {
class LOMView;
}

class LOMView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LOMView(QWidget *parent = 0);
    ~LOMView();

private:
    Ui::LOMView *ui;
};

#endif // LOMVIEW_H
