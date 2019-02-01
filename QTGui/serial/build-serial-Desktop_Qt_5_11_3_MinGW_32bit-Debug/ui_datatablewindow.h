/********************************************************************************
** Form generated from reading UI file 'datatablewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATATABLEWINDOW_H
#define UI_DATATABLEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_datatablewindow
{
public:
    QLabel *labCellIndex;
    QLabel *labCellType;
    QLabel *labStudID;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QSplitter *splitterMain;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QPushButton *btnSetHeader;
    QCheckBox *chkBoxHeaderH;
    QPushButton *btnAutoHeght;
    QCheckBox *chkBoxTabEditable;
    QCheckBox *chkBoxRowColor;
    QPushButton *btnInsertRow;
    QPushButton *btnIniData;
    QPushButton *btnAppendRow;
    QPushButton *btnDelCurRow;
    QSpinBox *spinRowCount;
    QRadioButton *rBtnSelectRow;
    QPushButton *btnSetRows;
    QRadioButton *rBtnSelectItem;
    QCheckBox *chkBoxHeaderV;
    QPushButton *btnReadToEdit;
    QPushButton *btnAutoWidth;
    QSplitter *splitter;
    QTableWidget *tableInfo;
    QPlainTextEdit *textEdit;
    QPushButton *btnDel;
    QPushButton *btnAdd;
    QPushButton *dataTableForwardPushButton;
    QPushButton *dataTableNextPushButton;

    void setupUi(QWidget *datatablewindow)
    {
        if (datatablewindow->objectName().isEmpty())
            datatablewindow->setObjectName(QStringLiteral("datatablewindow"));
        datatablewindow->resize(946, 616);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(datatablewindow->sizePolicy().hasHeightForWidth());
        datatablewindow->setSizePolicy(sizePolicy);
        labCellIndex = new QLabel(datatablewindow);
        labCellIndex->setObjectName(QStringLiteral("labCellIndex"));
        labCellIndex->setGeometry(QRect(30, 560, 72, 15));
        labCellType = new QLabel(datatablewindow);
        labCellType->setObjectName(QStringLiteral("labCellType"));
        labCellType->setGeometry(QRect(300, 560, 72, 15));
        labStudID = new QLabel(datatablewindow);
        labStudID->setObjectName(QStringLiteral("labStudID"));
        labStudID->setGeometry(QRect(630, 560, 72, 15));
        gridLayoutWidget = new QWidget(datatablewindow);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 761, 491));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        splitterMain = new QSplitter(gridLayoutWidget);
        splitterMain->setObjectName(QStringLiteral("splitterMain"));
        splitterMain->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitterMain);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMaximumSize(QSize(300, 16777215));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        btnSetHeader = new QPushButton(groupBox);
        btnSetHeader->setObjectName(QStringLiteral("btnSetHeader"));
        btnSetHeader->setMinimumSize(QSize(0, 25));

        gridLayout_5->addWidget(btnSetHeader, 0, 0, 1, 2);

        chkBoxHeaderH = new QCheckBox(groupBox);
        chkBoxHeaderH->setObjectName(QStringLiteral("chkBoxHeaderH"));
        chkBoxHeaderH->setChecked(true);

        gridLayout_5->addWidget(chkBoxHeaderH, 10, 0, 1, 1);

        btnAutoHeght = new QPushButton(groupBox);
        btnAutoHeght->setObjectName(QStringLiteral("btnAutoHeght"));

        gridLayout_5->addWidget(btnAutoHeght, 5, 0, 1, 1);

        chkBoxTabEditable = new QCheckBox(groupBox);
        chkBoxTabEditable->setObjectName(QStringLiteral("chkBoxTabEditable"));
        chkBoxTabEditable->setChecked(true);

        gridLayout_5->addWidget(chkBoxTabEditable, 9, 0, 1, 1);

        chkBoxRowColor = new QCheckBox(groupBox);
        chkBoxRowColor->setObjectName(QStringLiteral("chkBoxRowColor"));
        chkBoxRowColor->setChecked(true);

        gridLayout_5->addWidget(chkBoxRowColor, 9, 1, 1, 1);

        btnInsertRow = new QPushButton(groupBox);
        btnInsertRow->setObjectName(QStringLiteral("btnInsertRow"));

        gridLayout_5->addWidget(btnInsertRow, 3, 0, 1, 1);

        btnIniData = new QPushButton(groupBox);
        btnIniData->setObjectName(QStringLiteral("btnIniData"));
        btnIniData->setMinimumSize(QSize(0, 25));

        gridLayout_5->addWidget(btnIniData, 2, 0, 1, 2);

        btnAppendRow = new QPushButton(groupBox);
        btnAppendRow->setObjectName(QStringLiteral("btnAppendRow"));

        gridLayout_5->addWidget(btnAppendRow, 3, 1, 1, 1);

        btnDelCurRow = new QPushButton(groupBox);
        btnDelCurRow->setObjectName(QStringLiteral("btnDelCurRow"));

        gridLayout_5->addWidget(btnDelCurRow, 4, 0, 1, 2);

        spinRowCount = new QSpinBox(groupBox);
        spinRowCount->setObjectName(QStringLiteral("spinRowCount"));
        spinRowCount->setMinimum(2);
        spinRowCount->setValue(10);

        gridLayout_5->addWidget(spinRowCount, 1, 1, 1, 1);

        rBtnSelectRow = new QRadioButton(groupBox);
        rBtnSelectRow->setObjectName(QStringLiteral("rBtnSelectRow"));
        rBtnSelectRow->setChecked(false);

        gridLayout_5->addWidget(rBtnSelectRow, 11, 0, 1, 1);

        btnSetRows = new QPushButton(groupBox);
        btnSetRows->setObjectName(QStringLiteral("btnSetRows"));
        btnSetRows->setMinimumSize(QSize(0, 25));

        gridLayout_5->addWidget(btnSetRows, 1, 0, 1, 1);

        rBtnSelectItem = new QRadioButton(groupBox);
        rBtnSelectItem->setObjectName(QStringLiteral("rBtnSelectItem"));
        rBtnSelectItem->setChecked(true);

        gridLayout_5->addWidget(rBtnSelectItem, 11, 1, 1, 1);

        chkBoxHeaderV = new QCheckBox(groupBox);
        chkBoxHeaderV->setObjectName(QStringLiteral("chkBoxHeaderV"));
        chkBoxHeaderV->setChecked(true);

        gridLayout_5->addWidget(chkBoxHeaderV, 10, 1, 1, 1);

        btnReadToEdit = new QPushButton(groupBox);
        btnReadToEdit->setObjectName(QStringLiteral("btnReadToEdit"));
        btnReadToEdit->setMinimumSize(QSize(0, 25));

        gridLayout_5->addWidget(btnReadToEdit, 8, 0, 1, 2);

        btnAutoWidth = new QPushButton(groupBox);
        btnAutoWidth->setObjectName(QStringLiteral("btnAutoWidth"));

        gridLayout_5->addWidget(btnAutoWidth, 5, 1, 1, 1);

        splitterMain->addWidget(groupBox);
        splitter = new QSplitter(splitterMain);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setFrameShadow(QFrame::Plain);
        splitter->setLineWidth(2);
        splitter->setOrientation(Qt::Vertical);
        tableInfo = new QTableWidget(splitter);
        if (tableInfo->columnCount() < 4)
            tableInfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tableInfo->rowCount() < 6)
            tableInfo->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableInfo->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableInfo->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableInfo->setItem(1, 0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableInfo->setItem(2, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableInfo->setItem(5, 0, __qtablewidgetitem7);
        tableInfo->setObjectName(QStringLiteral("tableInfo"));
        tableInfo->setAlternatingRowColors(false);
        tableInfo->setRowCount(6);
        tableInfo->setColumnCount(4);
        splitter->addWidget(tableInfo);
        tableInfo->horizontalHeader()->setDefaultSectionSize(100);
        textEdit = new QPlainTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        splitter->addWidget(textEdit);
        btnDel = new QPushButton(splitter);
        btnDel->setObjectName(QStringLiteral("btnDel"));
        splitter->addWidget(btnDel);
        btnAdd = new QPushButton(splitter);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        splitter->addWidget(btnAdd);
        splitterMain->addWidget(splitter);

        gridLayout->addWidget(splitterMain, 0, 0, 1, 1);

        dataTableForwardPushButton = new QPushButton(datatablewindow);
        dataTableForwardPushButton->setObjectName(QStringLiteral("dataTableForwardPushButton"));
        dataTableForwardPushButton->setGeometry(QRect(830, 140, 93, 61));
        dataTableNextPushButton = new QPushButton(datatablewindow);
        dataTableNextPushButton->setObjectName(QStringLiteral("dataTableNextPushButton"));
        dataTableNextPushButton->setGeometry(QRect(830, 340, 93, 61));

        retranslateUi(datatablewindow);

        QMetaObject::connectSlotsByName(datatablewindow);
    } // setupUi

    void retranslateUi(QWidget *datatablewindow)
    {
        datatablewindow->setWindowTitle(QApplication::translate("datatablewindow", "datatablewindow", nullptr));
        labCellIndex->setText(QApplication::translate("datatablewindow", "TextLabel", nullptr));
        labCellType->setText(QApplication::translate("datatablewindow", "TextLabel", nullptr));
        labStudID->setText(QApplication::translate("datatablewindow", "TextLabel", nullptr));
        groupBox->setTitle(QString());
        btnSetHeader->setText(QApplication::translate("datatablewindow", "\350\256\276\347\275\256\350\241\250\345\244\264", nullptr));
        chkBoxHeaderH->setText(QApplication::translate("datatablewindow", "\346\230\276\347\244\272\350\241\214\350\241\250\345\244\264", nullptr));
        btnAutoHeght->setText(QApplication::translate("datatablewindow", "\350\207\252\345\212\250\350\260\203\350\212\202\350\241\214\351\253\230", nullptr));
        chkBoxTabEditable->setText(QApplication::translate("datatablewindow", "\350\241\250\346\240\274\345\217\257\347\274\226\350\276\221", nullptr));
        chkBoxRowColor->setText(QApplication::translate("datatablewindow", "\351\227\264\351\232\224\350\241\214\345\272\225\350\211\262", nullptr));
        btnInsertRow->setText(QApplication::translate("datatablewindow", "\346\217\222\345\205\245\350\241\214", nullptr));
        btnIniData->setText(QApplication::translate("datatablewindow", "\345\210\235\345\247\213\345\214\226\350\241\250\346\240\274\346\225\260\346\215\256", nullptr));
        btnAppendRow->setText(QApplication::translate("datatablewindow", "\346\267\273\345\212\240\350\241\214", nullptr));
        btnDelCurRow->setText(QApplication::translate("datatablewindow", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", nullptr));
        rBtnSelectRow->setText(QApplication::translate("datatablewindow", "\350\241\214\351\200\211\346\213\251", nullptr));
        btnSetRows->setText(QApplication::translate("datatablewindow", "\350\256\276\347\275\256\350\241\214\346\225\260", nullptr));
        rBtnSelectItem->setText(QApplication::translate("datatablewindow", "\345\215\225\345\205\203\346\240\274\351\200\211\346\213\251", nullptr));
        chkBoxHeaderV->setText(QApplication::translate("datatablewindow", "\346\230\276\347\244\272\345\210\227\350\241\250\345\244\264", nullptr));
        btnReadToEdit->setText(QApplication::translate("datatablewindow", "\350\257\273\345\217\226\350\241\250\346\240\274\345\206\205\345\256\271\345\210\260\346\226\207\346\234\254\346\241\206", nullptr));
        btnAutoWidth->setText(QApplication::translate("datatablewindow", "\350\207\252\345\212\250\350\260\203\350\212\202\345\210\227\345\256\275", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("datatablewindow", "\345\210\2271", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("datatablewindow", "\345\210\2272", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("datatablewindow", "\345\210\2273", nullptr));

        const bool __sortingEnabled = tableInfo->isSortingEnabled();
        tableInfo->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableInfo->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("datatablewindow", "0\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableInfo->item(0, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("datatablewindow", "0\350\241\214\357\274\2141\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableInfo->item(1, 0);
        ___qtablewidgetitem5->setText(QApplication::translate("datatablewindow", "1\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableInfo->item(2, 0);
        ___qtablewidgetitem6->setText(QApplication::translate("datatablewindow", "2\350\241\214\357\274\2140\345\210\227", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableInfo->item(5, 0);
        ___qtablewidgetitem7->setText(QApplication::translate("datatablewindow", "5\350\241\214\357\274\2140\345\210\227", nullptr));
        tableInfo->setSortingEnabled(__sortingEnabled);

        btnDel->setText(QApplication::translate("datatablewindow", "\345\210\240\351\231\244", nullptr));
        btnAdd->setText(QApplication::translate("datatablewindow", "\346\222\244\351\224\200", nullptr));
        dataTableForwardPushButton->setText(QApplication::translate("datatablewindow", "\344\270\212\344\270\200\346\255\245", nullptr));
        dataTableNextPushButton->setText(QApplication::translate("datatablewindow", "\344\270\213\344\270\200\346\255\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class datatablewindow: public Ui_datatablewindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATATABLEWINDOW_H
