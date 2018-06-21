#ifndef SETCAPACITYANDCOSTDIALOG_H
#define SETCAPACITYANDCOSTDIALOG_H

#include <QDialog>

namespace Ui {
class SetCapacityAndCostDialog;
}

class SetCapacityAndCostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetCapacityAndCostDialog(QWidget *parent = 0);
    ~SetCapacityAndCostDialog();

private:
    Ui::SetCapacityAndCostDialog *ui;
};

#endif // SETCAPACITYANDCOSTDIALOG_H
