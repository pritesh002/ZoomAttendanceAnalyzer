#include <iostream>
#include "attendanceanalyzer.h"
#include "zoomstudentsdetails.h"

AttendanceAnalyzer::AttendanceAnalyzer(QWidget *parent) : QWidget(parent) {
    importAttendanceCSV = new QLabel(tr("IMPORT ATTENDANCE CSV"));
    importTotalStudentsCSV = new QLabel(tr("IMPORT TOTALSTUDENTS CSV"));
    resultLabel = new QLabel(tr(""));
    durationLabel = new QLabel(tr("SELECT SESSION DURATION"));
    checkAttendance = new QLabel(tr("CHECK ATTENDANCE"));
    status = new QLabel(tr("Status:"));

    radioButton1 = new QRadioButton("1 HR");
    radioButton2 = new QRadioButton("2 HR");

    radioButton1->setChecked(true);

    selectStudent = new QComboBox;
    selectStudent->setEditable(true);

    uploadButton1 = new QPushButton(tr("CHOOSE FILE"));
    uploadButton2 = new QPushButton(tr("CHOOSE FILE"));
    analyzeButton = new QPushButton(tr("EXPORT RESULT CSV"));
    analyzeButton->setDisabled(true);
    clear = new QPushButton(tr("RESET"));

    fileDialog = new QFileDialog();
    fileDialog->setDirectory("C:\\Users");
    file = new QFile;

    importAttendanceCSV->setBuddy(uploadButton1);
    importTotalStudentsCSV->setBuddy(uploadButton2);

    QObject::connect(uploadButton1,SIGNAL(clicked()),this,SLOT(uploadButtonClicked1()));
    QObject::connect(uploadButton2,SIGNAL(clicked()),this,SLOT(uploadButtonClicked2()));
    QObject::connect(selectStudent,SIGNAL(activated(int)),this,SLOT(result(int)));
    QObject::connect(analyzeButton,SIGNAL(clicked()),this,SLOT(exportResult()));
    QObject::connect(radioButton1,SIGNAL(clicked()),this,SLOT(selectDuration()));
    QObject::connect(radioButton2,SIGNAL(clicked()),this,SLOT(selectDuration()));
    QObject::connect(clear,SIGNAL(clicked()),this,SLOT(resetApplication()));


    layout1 = new QHBoxLayout;
    layout1->addWidget(importTotalStudentsCSV);
    layout1->addWidget(uploadButton1);

    layout2 = new QHBoxLayout;
    layout2->addWidget(importAttendanceCSV);
    layout2->addWidget(uploadButton2);

    layout3 = new QVBoxLayout;
    layout3->insertSpacing(0,20);
    layout3->addWidget(durationLabel);
    layout3->addWidget(radioButton1);
    layout3->addWidget(radioButton2);
    layout3->addSpacing(20);

    layout4 = new QHBoxLayout;
    layout4->addWidget(status);
    layout4->addWidget(resultLabel);

    layout5 = new QVBoxLayout;
    layout5->addWidget(checkAttendance);
    layout5->addWidget(selectStudent);
    layout5->addLayout(layout4);
    layout5->addSpacing(20);

    leftLayout = new QVBoxLayout;
    leftLayout->addLayout(layout1);
    leftLayout->addLayout(layout2);
    leftLayout->addLayout(layout3);
    leftLayout->addLayout(layout5);
    leftLayout->addWidget(analyzeButton);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(clear);

    setLayout(mainLayout);
    setWindowTitle(tr("ZoomAttendanceAnalyzer"));
    setMinimumWidth(400);

}

void AttendanceAnalyzer::uploadButtonClicked1()
{
    QObject::disconnect(fileDialog,SIGNAL(fileSelected(QString)),nullptr,nullptr);
    QObject::connect(fileDialog,SIGNAL(fileSelected(QString)),this,SLOT(getTotalStudentsFile(QString)));
    fileDialog->open();
}

void AttendanceAnalyzer::uploadButtonClicked2()
{
    QObject::disconnect(fileDialog,SIGNAL(fileSelected(QString)),nullptr,nullptr);
    QObject::connect(fileDialog,SIGNAL(fileSelected(QString)),this,SLOT(getAttendanceFile(QString)));
    fileDialog->open();
}

void AttendanceAnalyzer::getTotalStudentsFile(const QString& str)
{
    file->setFileName(str);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Failed to open file" << std::endl;
        return;
    }

    QTextStream in(file);
    while(!in.atEnd())
    {
        QString data = in.readLine();
        studentList << data;
        selectStudent->addItem(data);
    }
    file->close();

    uploadButton1->setDisabled(true);
}

void AttendanceAnalyzer::getAttendanceFile(const QString& str)
{
    file->setFileName(str);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout << "Failed to open file" << std::endl;
        return;
    }

    QTextStream in(file);
    static QRegularExpression re("(\\d{3}|R_\\d{2})_[A-Z][a-zA-Z]*_[A-Z][a-zA-Z]*");

    while(!in.atEnd())
    {
        QString data = in.readLine();
        QStringList detailsList = data.split(',');
        if(detailsList[0].contains(re))
        {
            attendanceInfoList << ZoomStudentsDetails(detailsList[0],
                                                      detailsList[1],
                                                      detailsList[2],
                                                      detailsList[3],
                                                      detailsList[4].toInt(),
                                                      detailsList[5],
                                                      detailsList[6],
                                                      detailsList[7]);
        }
        else
        {
            blackListedStudents << detailsList[0];
        }
    }

    blackListedStudents.removeDuplicates();
    blackListedStudents.pop_front();

    file->close();

    uploadButton2->setDisabled(true);
    analyzeButton->setDisabled(false);
}

void AttendanceAnalyzer::selectDuration()
{
    resultLabel->setText("");
    if(radioButton1->isChecked())
    {
        minDuration = 75;
    }
    else
    {
        minDuration = 135;
    }
}


void AttendanceAnalyzer::result(int index)
{
    QList<ZoomStudentsDetails>::iterator iter = attendanceInfoList.begin();
    int totalDuration = 0;
    while(iter!=attendanceInfoList.end())
    {
        if((*iter).getName().contains(studentList.at(index)) && (*iter).getInWatingRoomStatus().contains("No"))
        {
            totalDuration += (*iter).getDuration();
        }
        ++iter;
    }
    resultLabel->setText(totalDuration < minDuration ?"Absent":"Present");
}

void AttendanceAnalyzer::exportResult()
{
    file->setFileName("..\\..\\Result.csv");
    if (!file->open(QIODevice::WriteOnly))
    {
        std::cout << "Failed to open file" << std::endl;
        return;
    }

    QTextStream out(file);

    out << "Name,Attendance\n";

    QStringList::Iterator iter;
    iter = studentList.begin();
    while(iter!=studentList.end())
    {
        int totalDuration = 0;
        QList<ZoomStudentsDetails>::iterator iter2 = attendanceInfoList.begin();
        while(iter2!=attendanceInfoList.end())
        {
            if((*iter2).getName().contains(*iter) && (*iter2).getInWatingRoomStatus().contains("No"))
            {
                totalDuration += (*iter2).getDuration();
            }
            iter2++;
        }
        out << *iter <<","<< (totalDuration < minDuration ? "Absent" : "Present") << "\n";
        iter++;
    }

    out<<"\n";
    out << "Blacklisted Students Name\n" ;
    iter = blackListedStudents.begin()+3;
    while(iter!=blackListedStudents.end())
    {
        out<<(*iter)<<"\n";
        iter++;
    }
    file->close();
}

void AttendanceAnalyzer::resetApplication()
{
    //reset button
    uploadButton1->setDisabled(false);
    uploadButton2->setDisabled(false);
    analyzeButton->setDisabled(true);
    selectStudent->clear();

    //empty list
    studentList.remove(0,studentList.size());
    attendanceInfoList.remove(0,attendanceInfoList.size());
    blackListedStudents.remove(0,blackListedStudents.size());

    //reset label
    resultLabel->setText("");

}
