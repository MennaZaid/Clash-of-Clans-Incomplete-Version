#include "settings.h"
#include "ui_settings.h"
#include<QMediaPlayer>
#include"mainwindow.h"
#include<QDebug>
Settings::Settings(QWidget *parent, QMediaPlayer* click, float soundValue, float musicValue)
    : QDialog(parent)
    , ui(new Ui::Settings), itsClick(click)
{
    ui->setupUi(this);
    QPixmap background (":/Back/Background.jpeg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);


    ui->MusicButton->setChecked((musicValue == 0 ? Qt::Unchecked : Qt::Checked));
    ui->SoundButton->setChecked((soundValue == 0 ? Qt::Unchecked : Qt::Checked));

    ui->MusicGlider->setSliderPosition(musicValue);
    ui->MusicGlider->setValue(musicValue);
    ui->SoundGlider->setSliderDown(soundValue);
    ui->SoundGlider->setValue(soundValue);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_Back_clicked()
{
    itsClick->play();
    MainWindow* parent = static_cast<MainWindow*>(this->parent());
    parent->show();
    destroy(true);

}


void Settings::on_MusicButton_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->MusicGlider->setValue(100);
    }
    else
    {
        ui->MusicGlider->setValue(0);
    }
}


void Settings::on_SoundButton_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked)
    {
        ui->SoundGlider->setValue(100);
    }
    else
    {
        ui->SoundGlider->setValue(0);
    }
}


void Settings::on_MusicGlider_valueChanged(int value)
{
    MainWindow* parent = static_cast<MainWindow*>(this->parent());
    parent->setMusicVolume(value / 100);
}


void Settings::on_SoundGlider_valueChanged(int value)
{
    MainWindow* parent = static_cast<MainWindow*>(this->parent());
    parent->setSoundVolume(value / 100);
}
