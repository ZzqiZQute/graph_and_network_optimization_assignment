#ifndef SETDISTANCEDIALOG_H
#define SETDISTANCEDIALOG_H

#include <QDialog>

namespace Ui {
class SetDistanceDialog;
}

class SetDistanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetDistanceDialog(QWidget *parent = 0);
    ~SetDistanceDialog();

    double getDistance() const;

    bool getHasValue() const;

    bool getOk() const;


public slots:
    void onBtnOkClicked();
protected:
    void accept();
private:
    Ui::SetDistanceDialog *ui;
    double distance;
    void getDis();
    bool ok;
};

#endif // SETDISTANCEDIALOG_H
