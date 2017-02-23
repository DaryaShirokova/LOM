#ifndef QCOLORBAR_H
#define QCOLORBAR_H

#include <QWidget>
#include <QColor>

//! Color bar widget.

class QColorBar : public QWidget
{
    Q_OBJECT

public:
    //! Constuctor.
    explicit QColorBar(QWidget *parent = 0);

    //! Destructor.
    ~QColorBar() {}

    /*!
     * \brief GetColor  get color by parameter (0 - 1).
     * \param val   the value between 0 and 1.
     * \return
     */
    static QColor GetColor(double val);

protected:
    //! Paint event.
    void paintEvent(QPaintEvent *event) override;

private:
    const int shadesNumber = 40; /* The number of gradations.*/

};

#endif // QCOLORBAR_H
