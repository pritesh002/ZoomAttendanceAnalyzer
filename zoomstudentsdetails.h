#ifndef ZOOMSTUDENTSDETAILS_H
#define ZOOMSTUDENTSDETAILS_H


#include <QString>
#include <QFile>


class ZoomStudentsDetails
{
private:
    QString name;
    QString email;
    QString joinTime;
    QString leaveTime;
    int duration;
    QString guest;
    QString recDisclaimerResponse;
    QString inWaitingRoom;
public:
    ZoomStudentsDetails(QString s_name,
                        QString s_email,
                        QString s_joinTime,
                        QString s_leaveTime,
                        int s_duration,
                        QString s_guest,
                        QString s_recDisclaimerResponse,
                        QString s_inWaitingRoom);
    QString getName();
    QString getEmail();
    QString getJoinTime();
    QString getLeaveTime();
    int getDuration();
    QString getGuestStatus();
    QString getRecDisclaimerResponse();
    QString getInWatingRoomStatus();
};

#endif // ZOOMSTUDENTSDETAILS_H
