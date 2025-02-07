#include "interface.h"

void Interface::setupUi(QMainWindow *MainWindow){
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(900, 800);
    MainWindow->setMinimumSize(QSize(900, 800));
    MainWindow->setMaximumSize(QSize(900, 800));
    MainWindow->setBaseSize(QSize(900, 800));
    MainWindow->setAutoFillBackground(true);
    MainWindow->setStyleSheet(QString::fromUtf8(""));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
    centralwidget->setSizePolicy(sizePolicy);
    centralwidget->setMinimumSize(QSize(900, 800));
    centralwidget->setMaximumSize(QSize(900, 800));
    centralwidget->setBaseSize(QSize(900, 800));
    motionField = new QWidget(centralwidget);
    motionField->setObjectName(QString::fromUtf8("motionField"));
    motionField->setGeometry(QRect(0, 0, 600, 800));
    QFont font;
    font.setKerning(true);
    motionField->setFont(font);
    motionField->setStyleSheet(QString::fromUtf8("background-color: rgb(139, 146, 171);\n"
                                                 "\n"
                                                 "border-right: 2.5px solid #FFFFFF;\n"
                                                 "border-left: 2.5px solid #FFFFFF;\n"
                                                 "border-top: 2.5px solid #FFFFFF;\n"
                                                 "border-bottom: 2.5px solid #FFFFFF;"));
    menuField = new QWidget(centralwidget);
    menuField->setObjectName(QString::fromUtf8("menuField"));
    menuField->setGeometry(QRect(600, 0, 300, 800));
    menuField->setStyleSheet(QString::fromUtf8("background-color: rgb(77, 83, 150);\n"
                                               "\n"
                                               "border-right: 2.5px solid #FFFFFF;\n"
                                               "border-left: 1.25px solid #FFFFFF;\n"
                                               "border-top: 2.5px solid #FFFFFF;\n"
                                               "border-bottom: 2.5px solid #FFFFFF;"));
    angleLabel = new QLabel(menuField);
    angleLabel->setObjectName(QString::fromUtf8("angleLabel"));
    angleLabel->setGeometry(QRect(37, 375, 108, 35));
    angleLabel->setMinimumSize(QSize(108, 35));
    angleLabel->setMaximumSize(QSize(16777215, 35));
    angleLabel->setBaseSize(QSize(108, 35));
    angleLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                "color: #4D5396;                    \n"
                                                "font-family: ;    \n"
                                                "font: 9pt \"Bahnschrift Condensed\";\n"
                                                "font-size: 23px;                    \n"
                                                "text-align: center;                 \n"
                                                "border: 2px solid white;              \n"
                                                "border-radius: 10%;  "));
    angleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    startButton = new QPushButton(menuField);
    startButton->setObjectName(QString::fromUtf8("startButton"));
    startButton->setGeometry(QRect(37, 240, 108, 35));
    startButton->setMinimumSize(QSize(108, 35));
    startButton->setMaximumSize(QSize(16777215, 35));
    startButton->setBaseSize(QSize(108, 35));
    startButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    startButton->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                 "color: #4D5396;                    \n"
                                                 "font-family: ;    \n"
                                                 "font: 9pt \"Bahnschrift Condensed\";\n"
                                                 "font-size: 23px;                    \n"
                                                 "text-align: center;                 \n"
                                                 "border: 2px solid white;              \n"
                                                 "border-radius: 10%;  "));
    startButton->setAutoExclusive(false);
    speedLabel = new QLabel(menuField);
    speedLabel->setObjectName(QString::fromUtf8("speedLabel"));
    speedLabel->setGeometry(QRect(37, 330, 108, 35));
    speedLabel->setMinimumSize(QSize(108, 35));
    speedLabel->setMaximumSize(QSize(16777215, 35));
    speedLabel->setBaseSize(QSize(108, 35));
    speedLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                "color: #4D5396;                    \n"
                                                "font-family: ;    \n"
                                                "font: 9pt \"Bahnschrift Condensed\";\n"
                                                "font-size: 23px;                    \n"
                                                "text-align: center;                 \n"
                                                "border: 2px solid white;              \n"
                                                "border-radius: 10%;  "));
    speedLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    radiusLabel = new QLabel(menuField);
    radiusLabel->setObjectName(QString::fromUtf8("radiusLabel"));
    radiusLabel->setGeometry(QRect(37, 285, 108, 35));
    radiusLabel->setMinimumSize(QSize(108, 35));
    radiusLabel->setMaximumSize(QSize(16777215, 35));
    radiusLabel->setBaseSize(QSize(108, 35));
    radiusLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                 "color: #4D5396;                    \n"
                                                 "font-family: ;    \n"
                                                 "font: 9pt \"Bahnschrift Condensed\";\n"
                                                 "font-size: 23px;                    \n"
                                                 "text-align: center;                 \n"
                                                 "border: 2px solid white;              \n"
                                                 "border-radius: 10%;  "));
    radiusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    speedInput = new QLineEdit(menuField);
    speedInput->setObjectName(QString::fromUtf8("speedInput"));
    speedInput->setGeometry(QRect(155, 330, 108, 35));
    speedInput->setMinimumSize(QSize(108, 35));
    speedInput->setMaximumSize(QSize(16777215, 35));
    speedInput->setBaseSize(QSize(108, 35));
    speedInput->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                "color: #4D5396;                    \n"
                                                "font-family: ;    \n"
                                                "font: 9pt \"Bahnschrift Condensed\";\n"
                                                "font-size: 23px;                    \n"
                                                "text-align: center;                 \n"
                                                "border: 2px solid white;              \n"
                                                "border-radius: 10%;  "));
    speedInput->setAlignment(Qt::AlignmentFlag::AlignCenter);
    angleInput = new QLineEdit(menuField);
    angleInput->setObjectName(QString::fromUtf8("angleInput"));
    angleInput->setGeometry(QRect(155, 375, 108, 35));
    angleInput->setMinimumSize(QSize(108, 35));
    angleInput->setBaseSize(QSize(108, 35));
    angleInput->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                "color: #4D5396;                    \n"
                                                "font-family: ;    \n"
                                                "font: 9pt \"Bahnschrift Condensed\";\n"
                                                "font-size: 23px;                    \n"
                                                "text-align: center;                 \n"
                                                "border: 2px solid white;              \n"
                                                "border-radius: 10%;  "));
    angleInput->setAlignment(Qt::AlignmentFlag::AlignCenter);
    radiusInput = new QLineEdit(menuField);
    radiusInput->setObjectName(QString::fromUtf8("radiusInput"));
    radiusInput->setGeometry(QRect(155, 285, 108, 35));
    radiusInput->setMinimumSize(QSize(108, 35));
    radiusInput->setMaximumSize(QSize(16777215, 35));
    radiusInput->setBaseSize(QSize(108, 35));
    radiusInput->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                 "color: #4D5396;                    \n"
                                                 "font-family: ;    \n"
                                                 "font: 9pt \"Bahnschrift Condensed\";\n"
                                                 "font-size: 23px;                    \n"
                                                 "text-align: center;                 \n"
                                                 "border: 2px solid white;              \n"
                                                 "border-radius: 10%;  "));
    radiusInput->setAlignment(Qt::AlignmentFlag::AlignCenter);
    initialButton = new QPushButton(menuField);
    initialButton->setObjectName(QString::fromUtf8("initialButton"));
    initialButton->setGeometry(QRect(155, 240, 108, 35));
    initialButton->setMinimumSize(QSize(108, 35));
    initialButton->setMaximumSize(QSize(16777215, 35));
    initialButton->setBaseSize(QSize(108, 35));
    initialButton->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                   "color: #4D5396;                    \n"
                                                   "font-family: ;    \n"
                                                   "font: 9pt \"Bahnschrift Condensed\";\n"
                                                   "font-size: 23px;                    \n"
                                                   "text-align: center;                 \n"
                                                   "border: 2px solid white;              \n"
                                                   "border-radius: 10%;  "));
    limitAngleLabel = new QLabel(menuField);
    limitAngleLabel->setObjectName(QString::fromUtf8("limitAngleLabel"));
    limitAngleLabel->setGeometry(QRect(37, 525, 226, 35));
    limitAngleLabel->setMinimumSize(QSize(216, 35));
    limitAngleLabel->setMaximumSize(QSize(16777215, 35));
    limitAngleLabel->setBaseSize(QSize(108, 35));
    limitAngleLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                     "color: #4D5396;                    \n"
                                                     "font-family: ;    \n"
                                                     "font: 9pt \"Bahnschrift Condensed\";\n"
                                                     "font-size: 23px;                    \n"
                                                     "text-align: center;                 \n"
                                                     "border: 2px solid white;              \n"
                                                     "border-radius: 10%;  "));
    limitAngleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    limitSpeedLabel = new QLabel(menuField);
    limitSpeedLabel->setObjectName(QString::fromUtf8("limitSpeedLabel"));
    limitSpeedLabel->setGeometry(QRect(37, 480, 226, 35));
    limitSpeedLabel->setMinimumSize(QSize(216, 35));
    limitSpeedLabel->setMaximumSize(QSize(16777215, 35));
    limitSpeedLabel->setBaseSize(QSize(108, 35));
    limitSpeedLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                     "color: #4D5396;                    \n"
                                                     "font-family: ;    \n"
                                                     "font: 9pt \"Bahnschrift Condensed\";\n"
                                                     "font-size: 23px;                    \n"
                                                     "text-align: center;                 \n"
                                                     "border: 2px solid white;              \n"
                                                     "border-radius: 10%;  "));
    limitSpeedLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    limitRadiusLabel = new QLabel(menuField);
    limitRadiusLabel->setObjectName(QString::fromUtf8("limitRadiusLabel"));
    limitRadiusLabel->setGeometry(QRect(37, 435, 226, 35));
    limitRadiusLabel->setMinimumSize(QSize(216, 35));
    limitRadiusLabel->setMaximumSize(QSize(16777215, 35));
    limitRadiusLabel->setBaseSize(QSize(108, 35));
    limitRadiusLabel->setStyleSheet(QString::fromUtf8("background-color: white;             \n"
                                                      "color: #4D5396;                    \n"
                                                      "font-family: ;    \n"
                                                      "font: 9pt \"Bahnschrift Condensed\";\n"
                                                      "font-size: 23px;                    \n"
                                                      "text-align: center;                 \n"
                                                      "border: 2px solid white;              \n"
                                                      "border-radius: 10%;  "));
    limitRadiusLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    QMetaObject::connectSlotsByName(MainWindow);
}

void Interface::retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CourseWork", nullptr));
    angleLabel->setText(QCoreApplication::translate("MainWindow", "Angle", nullptr));
    startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
    speedLabel->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
    radiusLabel->setText(QCoreApplication::translate("MainWindow", "Radius", nullptr));
    initialButton->setText(QCoreApplication::translate("MainWindow", "Initial state", nullptr));
    limitAngleLabel->setText(QCoreApplication::translate("MainWindow", "0 <= Angle <= 360", nullptr));
    limitSpeedLabel->setText(QCoreApplication::translate("MainWindow", "0 < Speed < 500", nullptr));
    limitRadiusLabel->setText(QCoreApplication::translate("MainWindow", "0 < Radius < 290", nullptr));
}
