#ifndef SELFLIPTYPEDLG_H
#define SELFLIPTYPEDLG_H

#include <QDialog>

namespace Ui {
class SelFlipTypeDlg;
}

class SelFlipTypeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelFlipTypeDlg(QWidget *parent = 0);
    ~SelFlipTypeDlg();

public:
    int typeFlip;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelFlipTypeDlg *ui;
};

#endif // SELFLIPTYPEDLG_H
