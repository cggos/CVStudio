#include "SelColorReduceDivDlg.h"
#include "ui_SelColorReduceDivDlg.h"

SelColorReduceDivDlg::SelColorReduceDivDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelColorReduceDivDlg)
{
    ui->setupUi(this);
}

SelColorReduceDivDlg::~SelColorReduceDivDlg()
{
    delete ui;
}

void SelColorReduceDivDlg::on_buttonBox_accepted()
{
    divColorReduce = ui->cmbBoxDiv->currentText().toInt();
}
