#ifndef SELCHANNELDLG_H
#define SELCHANNELDLG_H

#include <QDialog>

namespace Ui {
class SelChannelDlg;
}

class SelChannelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SelChannelDlg(QWidget *parent,int countChannel);
    ~SelChannelDlg();

public:
    int indexChannel;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SelChannelDlg *ui;
};

#endif // SELCHANNELDLG_H
