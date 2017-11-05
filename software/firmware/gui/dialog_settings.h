#ifndef DIALOG_SETTINGS_H
#define DIALOG_SETTINGS_H

#include <QWidget>

namespace Ui {
  class dialog_settings;
}

class dialog_settings : public QWidget
{
  Q_OBJECT

public:
  explicit dialog_settings(QWidget *parent = 0);
  ~dialog_settings();

private slots:
  void on_pushButton_clicked();

private:
  Ui::dialog_settings *ui;
};

#endif // DIALOG_SEETINGS_H
