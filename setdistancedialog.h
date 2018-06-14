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

    int getDistance() const;

    bool getHasValue() const;

public slots:
    void onBtnOkClicked();
protected:
    void accept();
private:
    Ui::SetDistanceDialog *ui;
    int distance;
    bool hasValue;
    void getDis();
};

#endif // SETDISTANCEDIALOG_H
