#ifndef SELCOLORREDUCEDIVDLG_H
#define SELCOLORREDUCEDIVDLG_H

#include <QDialog>

namespace Ui {
class SelColorReduceDivDlg;
}

class SelColorReduceDivDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelColorReduceDivDlg(QWidget *parent = 0);
    ~SelColorReduceDivDlg();

public:
    int divColorReduce;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelColorReduceDivDlg *ui;
};

#endif // SELCOLORREDUCEDIVDLG_H
