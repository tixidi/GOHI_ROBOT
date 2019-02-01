#include "datatablewindow.h"
#include "ui_datatablewindow.h"


#include    <QDate>
#include    <QTableWidgetItem>
#include    <QComboBox>
#include    <QTextBlock>
#include    <QTextDocument>






datatablewindow::datatablewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::datatablewindow)
{
    ui->setupUi(this);
    //setCentralWidget(ui->splitterMain);
//    this->setMinimumSize(1024,600);
//    this->setMaximumSize(1024,600);
//    this->move(200,200);

    //状态栏初始化创建
    ui->labCellIndex->setText("当前单元格坐标：");
    ui->labCellIndex->setMinimumWidth(250);

    ui->labCellType->setText("当前单元格类型：");
    ui->labCellType->setMinimumWidth(200);

    ui->labStudID->setText("测试点ID：");
    ui->labStudID->setMinimumWidth(200);



    on_btnSetHeader_clicked();
    connect(ui->tableInfo->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT (sort(int)));



//

}

datatablewindow::~datatablewindow()
{
    delete ui;

}




void datatablewindow::on_btnSetHeader_clicked()
{ //设置表头
    QTableWidgetItem    *headerItem;
    QStringList headerText;
    headerText<<"序号"<<"X坐标"<<"Y坐标"<<"Z坐标";  //表头标题用QStringList来表示
//    ui->tableInfo->setHorizontalHeaderLabels(headerText);
    ui->tableInfo->setColumnCount(headerText.count());//列数设置为与 headerText的行数相等
    for (int i=0;i<ui->tableInfo->columnCount();i++)//列编号从0开始
    {
//       cellItem=ui->tableInfo->horizontalHeaderItem(i);
       headerItem=new QTableWidgetItem(headerText.at(i)); //新建一个QTableWidgetItem， headerText.at(i)获取headerText的i行字符串
       QFont font=headerItem->font();//获取原有字体设置
       font.setBold(true);//设置为粗体
       font.setPointSize(12);//字体大小
       headerItem->setTextColor(Qt::red);//字体颜色
       headerItem->setFont(font);//设置字体
       ui->tableInfo->setHorizontalHeaderItem(i,headerItem); //设置表头单元格的Item
    }

//    ui->tableInfo->setItemDelegateForColumn(colScore,&spinDelegate);//设置自定义代理组件
}

void datatablewindow::on_btnSetRows_clicked()
{ //设置行数,设置的行数为数据区的行数，不含表头
 //如设置10行，数据区有10行，但是访问行号为0~9
    ui->tableInfo->setRowCount(ui->spinRowCount->value());//设置数据区行数
    ui->tableInfo->setAlternatingRowColors(ui->chkBoxRowColor->isChecked()); //设置交替行背景颜色
}


void datatablewindow::changeRowDataList()
{
    delRowDataList.clear();
    rowDataList.clear();
    delRecord.clear();
    tableRowMax = pointNumber;
    RowData rowData;
    for(int i=0; i<tableRowMax; i++){
            rowData.tableRow = i+1;
            rowData.Pos_X = 0;
            rowData.Pos_Y = 0;
            rowData.Pos_Z = 0;
            rowDataList.append(rowData);

    }

    qDebug() << Q_FUNC_INFO << "tableRowMax: " << tableRowMax;

}

void datatablewindow::initTableData()
{
    tableRow = tableRowMax;
    ui->tableInfo->clearContents();
    ui->tableInfo->setRowCount(tableRowMax);

    qDebug() << Q_FUNC_INFO << rowDataList.count();
    //依次给第一到第七列添加数据
    QString str;
    for(int i=0; i<tableRowMax; i++){

         createItemsARow(i,rowDataList.at(i).Pos_X,rowDataList.at(i).Pos_Y,rowDataList.at(i).Pos_Z);

    }

}

void datatablewindow::on_btnIniData_clicked()
{ //初始化表格内容
    pointNumber=ui->spinRowCount->value();
    changeRowDataList();
    initTableData();
}

void datatablewindow::on_chkBoxTabEditable_clicked(bool checked)
{ //设置编辑模式
    if (checked)
//双击或获取焦点后单击，进入编辑状态
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers); //不允许编辑
}

void datatablewindow::on_chkBoxHeaderH_clicked(bool checked)
{//是否显示水平表头
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}

void datatablewindow::on_chkBoxHeaderV_clicked(bool checked)
{//是否显示垂直表头
    ui->tableInfo->verticalHeader()->setVisible(checked);
}

void datatablewindow::on_chkBoxRowColor_clicked(bool checked)
{ //行的底色交替采用不同颜色
    ui->tableInfo->setAlternatingRowColors(checked);

//    int i,j;
//    QTableWidgetItem    *cellItem;

//    for (i=0;i<ui->tableInfo->rowCount();i++)
//       for (j=0;j<ui->tableInfo->columnCount();j++)
//    {
//        cellItem=ui->tableInfo->item(i,j); //获取单元格的Item
//        if ((checked) && ((i%2)==1)) //交替显示，且是奇数行
//            cellItem->setBackgroundColor(Qt::yellow);//Qt::green  lightGray  yellow
//        else
//            cellItem->setBackgroundColor(Qt::white);//设置单元格底色
//    }
}

void datatablewindow::on_rBtnSelectItem_clicked()
{//选择行为：单元格选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void datatablewindow::on_rBtnSelectRow_clicked()
{//选择行为：行选择
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}




void datatablewindow::on_btnReadToEdit_clicked()
{//将 QTableWidget的所有行的内容提取字符串，显示在QPlainTextEdit里
    QString str;
    QTableWidgetItem    *cellItem;

    ui->textEdit->clear(); //文本编辑器清空
    for (int i=0;i<ui->tableInfo->rowCount();i++) //逐行处理
    {
        str=QString::asprintf("第 %d 行： ",i+1);
       for (int j=0;j<ui->tableInfo->columnCount();j++) //逐列处理，但最后一列是check型，单独处理
        {
            cellItem=ui->tableInfo->item(i,j); //获取单元格的item
            str=str+cellItem->text()+"   "; //字符串连接
        }

       ui->textEdit->appendPlainText(str); //添加到编辑框作为一行
    }
}




void datatablewindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{//当前选择单元格发生变化时的响应
   Q_UNUSED(previousRow);
   Q_UNUSED(previousColumn);

    QTableWidgetItem* item=ui->tableInfo->item(currentRow,currentColumn); //获取单元格的 Item
    if  (item==NULL)
        return;


    ui->labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列",currentRow,currentColumn));

    int cellType=item->type();//获取单元格的类型
    ui->labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));

    item=ui->tableInfo->item(currentRow,datatablewindow::colName); //取当前行第1列的单元格的 item
    int ID=item->data(Qt::UserRole).toInt();//读取用户自定义数据
    ui->labStudID->setText(QString::asprintf("测试点ID：%d",ID));//学生ID
}


void datatablewindow::on_btnInsertRow_clicked()
{ //插入一行
//    int curRow;
    int curRow=ui->tableInfo->currentRow();//当前行号

    ui->tableInfo->insertRow(curRow); //插入一行，但不会自动为单元格创建item
    createItemsARow(curRow,2,2,2 ); //为某一行创建items
}

void datatablewindow::on_btnAppendRow_clicked()
{ //添加一行
//    int curRow;
    int curRow=ui->tableInfo->rowCount();//当前行号
    ui->tableInfo->insertRow(curRow);//在表格尾部添加一行
    createItemsARow(curRow, 1,1,1 ); //为某一行创建items
}

void datatablewindow::on_btnDelCurRow_clicked()
{//删除当前行及其items
//    int curRow;
    int curRow=ui->tableInfo->currentRow();//当前行号
    ui->tableInfo->removeRow(curRow); //删除当前行及其items
}

void datatablewindow::createItemsARow(int rowNo,int P_X,int P_Y,int P_Z)
{ //为一行的单元格创建 Items
    QTableWidgetItem    *item;
    QString str;
    uint StudID=201605000; //学号基数

    str.setNum(rowNo);
    item=new  QTableWidgetItem(str,datatablewindow::ctName);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
//    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    StudID  +=rowNo; //学号=基数+ 行号
    item->setData(Qt::UserRole,QVariant(StudID));  //设置studID为data
    ui->tableInfo->setItem(rowNo,datatablewindow::colName,item);//为单元格设置Item
    item->setFlags(item->flags() & (~Qt::ItemIsEditable));//设置单元格不可编辑






//    str.setNum(P_X);
//    item=new  QTableWidgetItem(str,datatablewindow::ct_X);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
//    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    item =new QTableWidgetItem();
    item->setData(Qt::DisplayRole,QVariant(P_X));
    ui->tableInfo->setItem(rowNo,datatablewindow::col_X,item);//为单元格设置Item

//    str.setNum(P_Y);
//    item=new  QTableWidgetItem(str,datatablewindow::ct_Y);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
//    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    item =new QTableWidgetItem();
    item->setData(Qt::DisplayRole,QVariant(P_Y));
    ui->tableInfo->setItem(rowNo,datatablewindow::col_Y,item);//为单元格设置Item


//    str.setNum(P_Z);
//    item=new  QTableWidgetItem(str,datatablewindow::ct_Z);//新建一个Item，设置单元格type为自定义的 MainWindow::ctPartyM
//    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//文本对齐格式
    item =new QTableWidgetItem();
    item->setData(Qt::DisplayRole,QVariant(P_Z));
    ui->tableInfo->setItem(rowNo,datatablewindow::col_Z,item);//为单元格设置Item

}



void datatablewindow::slotGetPoint(MainWindow *biPoint)
{
    mainW = biPoint;
}




void datatablewindow::on_btnAutoHeght_clicked()
{
    ui->tableInfo->resizeRowsToContents();
}

void datatablewindow::on_btnAutoWidth_clicked()
{
    ui->tableInfo->resizeColumnsToContents();
}

//
void datatablewindow::PointNum(QList<int> num)
{
    //设置行数,设置的行数为数据区的行数，不含表头
     //如设置10行，数据区有10行，但是访问行号为0~9

    testPointCounts=num;

    int count = 0;
    for(int i=0; i<num.count(); i++){
        if(testPointCounts.at(i) == num.at(i))
            count++;
    }

    if(count==1) pointNumber=testPointCounts.at(0);
    qDebug()<<pointNumber;
    ui->tableInfo->setRowCount(pointNumber);//设置数据区行数
    ui->tableInfo->setAlternatingRowColors(ui->chkBoxRowColor->isChecked()); //设置交替行背景颜色
}

void datatablewindow::sort(int col)
{
    if (col != 1)
        {
            //不是我们想要的那一列
            ui->tableInfo->horizontalHeader()->setSortIndicatorShown(false);
            return;
        }

        static bool bSortAsc = true;

        Qt::SortOrder order = bSortAsc ? (Qt::AscendingOrder) : (Qt::DescendingOrder);
        ui->tableInfo->horizontalHeader()->setSortIndicatorShown(true);
        ui->tableInfo->horizontalHeader()->setSortIndicator(col, order);
        ui->tableInfo->sortItems(col, order);


        QString strSort = bSortAsc ? "asc" : "desc";
        qDebug()<<strSort;

        bSortAsc = !bSortAsc;

}


void datatablewindow::PointValue(QList<RowData> P_value)
{
    delRowDataList.clear();
    rowDataList.clear();
    delRecord.clear();
    tableRowMax = pointNumber;
    for(int i=0; i<tableRowMax; i++){

            rowDataList.append(P_value.at(i));

    }
    initTableData();
}






////需要修改
//void MainWindow::addRowData()
//{
//    if(delRecord.isEmpty()) return;
//    int row = ui->tableWidget->currentRow();
//    QStringList strList;
//    if(delRowDataList.isEmpty()) return;
//    RowData rowData = delRowDataList.takeLast();
//    strList.append(QString::number(rowData.P_positive));
//    strList.append(QString::number(rowData.P_negative));
//    strList.append(QString::number(rowData.voltage));
//    strList.append(QString::number(rowData.pulseNumber));
//    strList.append(QString::number(rowData.intensity));
//    strList.append(QString::number(rowData.span));
//    strList.append(QString::number(rowData.depth));
////    rowDataList.insert(lastDelRow,rowData);
//    ui->tableWidget->insertRow(row);
//    for(int i=0; i<7; i++){
//        ui->tableWidget->setItem(row,i,new QTableWidgetItem(strList.at(i)));
//    }
//}

void datatablewindow::on_dataTableForwardPushButton_clicked()
{
  mainW->show();
  this->hide();
}

void datatablewindow::on_dataTableNextPushButton_clicked()
{
    myOpengl *poglwindow= new myOpengl();
    poglwindow->show();
    connect(this,SIGNAL(fixPointValue(QList<RowData>)),poglwindow,SLOT(meshPointValue(QList<RowData>)));
    emit fixPointValue(rowDataList);
}


bool datatablewindow::slotGetBtn(bool ok)
{
    this->ok = ok;
    qDebug() << Q_FUNC_INFO << this->ok;
    return this->ok;
}


void datatablewindow::on_btnDel_clicked()
{

        ok = false;
        IndicateWindow *indicatewindow = new IndicateWindow();
        connect(indicatewindow,SIGNAL(sigOKBtnClicked(bool)),this,SLOT(slotGetBtn(bool)));
        indicatewindow->setTitle("提示");
        indicatewindow->setIndicate("是否删除一行！");
        indicatewindow->exec();
        if(!ok) return;
        ui->btnAdd->setEnabled(true);
        int row = ui->tableInfo->currentRow();
        qDebug() << Q_FUNC_INFO << row;
        ui->tableInfo->removeRow(row);
        delRowDataList.append(rowDataList.takeAt(row));
        tableRow = tableRow - 1;
        //    ui->psBtnDel->setEnabled(false);
        if(tableRow == 1){
            ui->btnDel->setEnabled(false);
            return;
        }
}

void datatablewindow::on_btnAdd_clicked()
{
    ok = false;
    IndicateWindow *indicatewindow = new IndicateWindow();
    connect(indicatewindow,SIGNAL(sigOKBtnClicked(bool)),this,SLOT(slotGetBtn(bool)));
    indicatewindow->setTitle("提示");
    indicatewindow->setIndicate("是否撤销所有删除项！");
    indicatewindow->exec();
    if(!ok) return;

    ui->btnAdd->setEnabled(false);
    delRecord.clear();
    for(int i=0; i<delRowDataList.count(); i++){
        rowDataList.append(delRowDataList.at(i));
    }
    RowData data;
    for(int i=1; i<rowDataList.count(); i++){
        for(int j=rowDataList.count()-1; j>=i; j--){
            if(rowDataList.at(j).tableRow < rowDataList.at(j-1).tableRow){
                data = rowDataList[j-1];
                rowDataList[j-1] = rowDataList[j];
                rowDataList[j] = data;
            }
        }
    }
    delRowDataList.clear();
    initTableData();
////    ui->psBtnDel->setEnabled(true);
//    qDebug() << Q_FUNC_INFO << tableRow;
////    int row = ui->psTableWidget->currentRow();
//    addRowData();
//    tableRow++;
//    if(tableRow >= tableRowMax){
//        tableRow = tableRowMax;
//        ui->psBtnAdd->setEnabled(false);
//        return;
//    }else{
//        ui->psBtnAdd->setEnabled(true);
//    }
}

