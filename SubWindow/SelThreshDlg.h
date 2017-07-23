#ifndef SELTHRESHDLG_H
#define SELTHRESHDLG_H

#include <QDialog>

namespace Ui {
class SelThreshDlg;
}

class SelThreshDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelThreshDlg(QWidget *parent = 0);
    ~SelThreshDlg();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_buttonBox_accepted();

public:
    double threshValue;

private:
    Ui::SelThreshDlg *ui;
};

#endif // SELTHRESHDLG_H
