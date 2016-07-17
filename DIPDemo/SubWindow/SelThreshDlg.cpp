#include "SelThreshDlg.h"
#include "ui_SelThreshDlg.h"

SelThreshDlg::SelThreshDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelThreshDlg)
{
    ui->setupUi(this);
}

SelThreshDlg::~SelThreshDlg()
{
    delete ui;
}

void SelThreshDlg::on_horizontalSlider_valueChanged(int value)
{
    ui->labelThreshValue->setText(QString::number(value));
}

void SelThreshDlg::on_buttonBox_accepted()
{
    threshValue = (double)(ui->horizontalSlider->value());
}
