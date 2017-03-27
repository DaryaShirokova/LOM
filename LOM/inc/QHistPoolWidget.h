#ifndef QHISTPOOLWIDGET_H
#define QHISTPOOLWIDGET_H

#include <QWidget>
#include <QVector>

#include "inc/QHistPlot.h"

namespace Ui {
class QHistPoolWidget;
}

class QHistPoolWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief QHistPoolWidget   Constructor.
     * \param parent            parent.
     */
    explicit QHistPoolWidget(QWidget *parent = 0);

    /*!
     *  Destructor.
     */
    ~QHistPoolWidget();

    /*!
     * \brief SetModel  Set model.
     * \param histPool  set of histograms.
     */
    void SetModel(LOMHistograms* histPool);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void  keyPressEvent(QKeyEvent *event) override;

private:
    Ui::QHistPoolWidget *ui;    /*!< GUI. */
    QVector<QHistPlot*> plotsPool;  /*!< Set of plots. */
    LOMHistograms* histPool; /*!< Set of histograms. */
    QStringList activeHist; /*!< Hists which are currently drawn. */
    int curPage; /*!< The page which is currently drawn. */

    /*!
     * \brief GetFavorite   Get favorite histograms.
     * \return  favorite histograms.
     */
    QStringList GetFavorite();

    /*!
     * \brief GetPagesNumber    Get number of pages to show all histograms.
     * \return  number of pages.
     */
    int GetPagesNumber();

    /*!
     * \brief SetLabel  Set histogram label.
     */
    void SetLabel();

    /*!
     * \brief GetSortedKeys Sort the keys considering numbers. (1 2 10 11..)
     * \return  sorted keys.
     */
    QStringList GetSortedKeys();

public slots:
    /*!
     * \brief UpdateHists   Update histograms.
     */
    void UpdateHists();

    /*!
     * \brief ShowPrevious  Show previous page.
     */
    void ShowPrevious();

    /*!
     * \brief ShowNext      Show next page.
     */
    void ShowNext();

    /*!
     * \brief CheckFavotite Handle the event when hist is marked as favorite.
     */
    void CheckFavotite();

    /*!
     * \brief Save  Save button is clicked.
     */
    void Save();

    /*!
     * \brief Update  Update button is clicked.
     */
    void Update();

signals:
    /*!
     * \brief UpdateRequired    The update of histograms is needed.
     */
    void UpdateRequired();

    /*!
     * \brief SaveHist          Saving of the histograms is needed.
     */
    void SaveHist();
};

#endif // QHISTPOOLWIDGET_H
