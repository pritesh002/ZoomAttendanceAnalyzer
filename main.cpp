#include <QApplication>
#include "attendanceanalyzer.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    AttendanceAnalyzer* pAttendanceAnalyzer = new AttendanceAnalyzer();
    pAttendanceAnalyzer->show();

    return app.exec();
}
