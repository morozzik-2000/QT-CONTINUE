#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPushButton* btnConnect;
    QPushButton* btnSend;
    QPushButton* btnStartPoll;
    QPushButton* btnStopPoll;
    QTextEdit* logText;
    QComboBox* comboPorts;

    void setupUI();
    void styleButton(QPushButton* btn, const QString& colorHex);
    void animateTextTyping(const QString& message);

private slots:
    void connectToPortImitation();
    void sendDataImitation();
};

#endif // MAINWINDOW_H
