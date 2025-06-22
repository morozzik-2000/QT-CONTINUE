#include "mainwindow.h"
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QLinearGradient>
#include <QDateTime>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent) {
    setFixedSize(600, 500);
    setWindowTitle("🚀 Futuristic Serial Interface");
    setupUI();
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    comboPorts = new QComboBox;
    comboPorts->addItems({"COM1", "COM2", "COM3"});
    comboPorts->setStyleSheet(R"(
        QComboBox {
            background-color: rgba(0,0,0,150);
            border: 1px solid cyan;
            color: cyan;
            font-size: 16px;
            padding: 5px;
        })");

    btnConnect = new QPushButton("🔌 Connect");
    btnSend = new QPushButton("📤 Send");
    btnStartPoll = new QPushButton("▶ Start Poll");
    btnStopPoll = new QPushButton("⏹ Stop Poll");

    styleButton(btnConnect, "#00ffff");
    styleButton(btnSend, "#00ffaa");
    styleButton(btnStartPoll, "#00ff7f");
    styleButton(btnStopPoll, "#ff5555");

    logText = new QTextEdit;
    logText->setReadOnly(true);
    logText->setFont(QFont("Courier New", 11));
    logText->setStyleSheet("color: #00ffff; background-color: black;");

    layout->addWidget(comboPorts);
    layout->addWidget(btnConnect);
    layout->addWidget(btnSend);
    layout->addWidget(btnStartPoll);
    layout->addWidget(btnStopPoll);
    layout->addWidget(logText);

    setCentralWidget(central);

    connect(btnConnect, &QPushButton::clicked, this, &MainWindow::connectToPortImitation);
    connect(btnSend, &QPushButton::clicked, this, &MainWindow::sendDataImitation);
}

void MainWindow::styleButton(QPushButton* btn, const QString& colorHex) {
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background-color: transparent;
            border: 2px solid %1;
            color: %1;
            font-size: 18px;
            padding: 10px;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: rgba(255,255,255,30);
        })").arg(colorHex));

    QGraphicsDropShadowEffect* glow = new QGraphicsDropShadowEffect(this);
    glow->setColor(QColor(colorHex));
    glow->setBlurRadius(25);
    glow->setOffset(0);
    btn->setGraphicsEffect(glow);
}

void MainWindow::animateTextTyping(const QString& message) {
    static QString buffer;
    buffer += "\n" + message;
    logText->clear();

    static int index = 0;
    index = 0;

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() mutable {
        if (index < buffer.size()) {
            logText->setPlainText(buffer.left(index++));
        } else {
            timer->stop();
            timer->deleteLater();
        }
    });
    timer->start(5);
}

void MainWindow::connectToPortImitation() {
    animateTextTyping("🔌 Connecting to port...");
    QPropertyAnimation* anim = new QPropertyAnimation(btnConnect, "geometry");
    QRect start = btnConnect->geometry();
    anim->setDuration(600);
    anim->setStartValue(start);
    anim->setKeyValueAt(0.5, QRect(start.x() + 10, start.y(), start.width() - 20, start.height()));
    anim->setEndValue(start);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(1000, this, [=]() {
        animateTextTyping("✅ Port connected successfully!");
    });
}

void MainWindow::sendDataImitation() {
    animateTextTyping("📤 Sending data to serial port...");
    QGraphicsOpacityEffect* flash = new QGraphicsOpacityEffect(this);
    btnSend->setGraphicsEffect(flash);

    QPropertyAnimation* anim = new QPropertyAnimation(flash, "opacity");
    anim->setDuration(500);
    anim->setStartValue(1.0);
    anim->setKeyValueAt(0.5, 0.0);
    anim->setEndValue(1.0);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(600, this, [=]() {
        animateTextTyping("✅ Data sent successfully!");
    });
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor("#000010"));
    gradient.setColorAt(1, QColor("#001020"));
    painter.fillRect(rect(), gradient);

    static QVector<QPoint> stars;
    if (stars.isEmpty()) {
        qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
        for (int i = 0; i < 200; ++i)
            stars.append(QPoint(qrand() % width(), qrand() % height()));
    }

    painter.setPen(QPen(Qt::white));
    for (const QPoint& pt : stars)
        painter.drawPoint(pt);
}
