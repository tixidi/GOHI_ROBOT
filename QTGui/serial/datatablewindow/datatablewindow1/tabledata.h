#ifndef TABLEDATA
#define TABLEDATA

//tableview记录
typedef struct tagRowData
{
    mutable int tableRow;     //记录行
    mutable int Pos_X;   //P+
    mutable int Pos_Y;   //P-
    mutable int Pos_Z;      //脉冲电压
}RowData;

Q_DECLARE_METATYPE(RowData);

#endif // TABLEDATA
