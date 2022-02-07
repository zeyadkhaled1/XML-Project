#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    QPixmap pix("Graph.png");
    ui->label->setPixmap(pix);
    ui->label->setScaledContents(true);


}

Graph::~Graph()
{
    delete ui;
}





