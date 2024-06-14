#ifndef RESPONSEDIALOG_H
#define RESPONSEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>
#include <QVBoxLayout>

class ResponseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResponseDialog(QWidget *parent = 0);
    void setResponseText(const QString &responseText, const QString &bold = "");
    void setAdditionalText(const QString &responseText);
    void setResponseIcon(const QIcon &icon);
    void setCloseButtonText(const QString &text);
    void setCancelButtonText(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void loginSuccess();
    void loginError();
    void loginServerError();
    void saleSuccess();
    void saleError();

private slots:
    void emitLoginSuccessAndClose();
    void emitLoginErrorAndClose();
    void emitSaleErrorAndClose();
    void emitSaleSuccessAndClose();

private:
    QLabel *responseLabel;
    QLabel *additionalTextLabel;
    QLabel *iconLabel;
    QPushButton *closeButton;
    QPushButton *cancelButton;
};

#endif // RESPONSEDIALOG_H
