#ifndef ATTENDANCEANALYZER_H
#define ATTENDANCEANALYZER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include <QStringList>
#include <QComboBox>
#include <QRadioButton>
#include "zoomstudentsdetails.h"

class AttendanceAnalyzer : public QWidget
{
    Q_OBJECT

private:
    QLabel* importAttendanceCSV;
    QLabel* importTotalStudentsCSV;
    QLabel* resultLabel;
    QLabel* durationLabel;
    QLabel* checkAttendance;
    QLabel* status;

    QRadioButton* radioButton1;
    QRadioButton* radioButton2;

    QComboBox* selectStudent;

    QPushButton* uploadButton1;
    QPushButton* uploadButton2;
    QPushButton* analyzeButton;
    QPushButton* clear;

    QFileDialog* fileDialog;
    QFile* file;

    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    QVBoxLayout* layout3;
    QHBoxLayout* layout4;
    QVBoxLayout* layout5;
    QVBoxLayout* leftLayout;
    QHBoxLayout* mainLayout;

    QList<ZoomStudentsDetails> attendanceInfoList;
    QStringList studentList;
    QStringList blackListedStudents;

    QString durationType;
    int minDuration;

public slots:
    void getTotalStudentsFile(const QString&);
    void getAttendanceFile(const QString&);
    void result(int);
    void uploadButtonClicked1();
    void uploadButtonClicked2();
    void exportResult();
    void selectDuration();
    void resetApplication();
public:
    AttendanceAnalyzer(QWidget *parent = 0);
};

#endif // ATTENDANCEANALYZER_H
