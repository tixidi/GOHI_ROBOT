/********************************************************************************
** Form generated from reading UI file 'indicatewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDICATEWINDOW_H
#define UI_INDICATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IndicateWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *iwLbTitle;
    QLabel *iwLbIndicate;
    QHBoxLayout *horizontalLayout;
    QPushButton *iwBtnOk;
    QPushButton *iwBtnCancel;

    void setupUi(QWidget *IndicateWindow)
    {
        if (IndicateWindow->objectName().isEmpty())
            IndicateWindow->setObjectName(QStringLiteral("IndicateWindow"));
        IndicateWindow->resize(448, 201);
        verticalLayout = new QVBoxLayout(IndicateWindow);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        iwLbTitle = new QLabel(IndicateWindow);
        iwLbTitle->setObjectName(QStringLiteral("iwLbTitle"));
        iwLbTitle->setMinimumSize(QSize(0, 40));
        iwLbTitle->setMaximumSize(QSize(16777215, 40));
        iwLbTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(iwLbTitle);

        iwLbIndicate = new QLabel(IndicateWindow);
        iwLbIndicate->setObjectName(QStringLiteral("iwLbIndicate"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(iwLbIndicate->sizePolicy().hasHeightForWidth());
        iwLbIndicate->setSizePolicy(sizePolicy);
        iwLbIndicate->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(iwLbIndicate);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 13);
        iwBtnOk = new QPushButton(IndicateWindow);
        iwBtnOk->setObjectName(QStringLiteral("iwBtnOk"));
        iwBtnOk->setMinimumSize(QSize(80, 35));
        iwBtnOk->setMaximumSize(QSize(80, 35));

        horizontalLayout->addWidget(iwBtnOk);

        iwBtnCancel = new QPushButton(IndicateWindow);
        iwBtnCancel->setObjectName(QStringLiteral("iwBtnCancel"));
        iwBtnCancel->setMinimumSize(QSize(80, 35));
        iwBtnCancel->setMaximumSize(QSize(80, 35));

        horizontalLayout->addWidget(iwBtnCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(IndicateWindow);

        QMetaObject::connectSlotsByName(IndicateWindow);
    } // setupUi

    void retranslateUi(QWidget *IndicateWindow)
    {
        IndicateWindow->setWindowTitle(QApplication::translate("IndicateWindow", "IndicateWindow", nullptr));
        iwLbTitle->setText(QApplication::translate("IndicateWindow", "\346\217\220\347\244\272", nullptr));
        iwLbIndicate->setText(QApplication::translate("IndicateWindow", "\346\223\215\344\275\234\346\234\211\350\257\257\357\274\201", nullptr));
        iwBtnOk->setText(QApplication::translate("IndicateWindow", "\347\241\256\345\256\232", nullptr));
        iwBtnCancel->setText(QApplication::translate("IndicateWindow", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IndicateWindow: public Ui_IndicateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDICATEWINDOW_H
