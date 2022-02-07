#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class Graph;
}

class Graph : public QDialog
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    ~Graph();
     Ui::Graph *ui;

};

#endif // GRAPH_H
