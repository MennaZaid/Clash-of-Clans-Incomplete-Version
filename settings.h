#ifndef SETTINGS_H
#define SETTINGS_H
#include<Qmediaplayer>
#include <QDialog>
#include<QAudioOutput>
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr, QMediaPlayer* = nullptr, float = 100, float = 100);
    ~Settings();

private slots:
    void on_Back_clicked();

    void on_MusicButton_stateChanged(int arg1);

    void on_SoundButton_stateChanged(int arg1);

    void on_MusicGlider_valueChanged(int value);

    void on_SoundGlider_valueChanged(int value);

private:
    Ui::Settings *ui;
    QMediaPlayer *itsClick;
};

#endif // SETTINGS_H
