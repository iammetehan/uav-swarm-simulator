#ifndef SELECTMAP_H
#define SELECTMAP_H

#include <QDialog>
#include "Definitions.h"

namespace Ui {
class SelectMapDialog;
}

class SelectMapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectMapDialog(QWidget *parent = nullptr);
    ~SelectMapDialog();

public:
    Data::Map Map() const;

private slots:
    void SelectImage();

private:
    Ui::SelectMapDialog *ui;
};

#endif // SELECTMAP_H
