#include "SelFlipTypeDlg.h"
#include "ui_SelFlipTypeDlg.h"

SelFlipTypeDlg::SelFlipTypeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelFlipTypeDlg)
{
    ui->setupUi(this);
}

SelFlipTypeDlg::~SelFlipTypeDlg()
{
    delete ui;
}

void SelFlipTypeDlg::on_buttonBox_accepted()
{
    typeFlip = ui->cmbBoxFlipType->currentIndex();
}
