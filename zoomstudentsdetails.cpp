#include "zoomstudentsdetails.h"

ZoomStudentsDetails::ZoomStudentsDetails(QString s_name,
                                         QString s_email,
                                         QString s_joinTime,
                                         QString s_leaveTime,
                                         int s_duration,
                                         QString s_guest,
                                         QString s_recDisclaimerResponse,
                                         QString s_inWaitingRoom ) :
                                        name(s_name),
                                        email(s_email),
                                        joinTime(s_joinTime),
                                        leaveTime(s_leaveTime),
                                        duration(s_duration),
                                        guest(s_guest),
                                        recDisclaimerResponse(s_recDisclaimerResponse),
                                        inWaitingRoom(s_inWaitingRoom)
{

}

QString ZoomStudentsDetails::getName()
{
    return this->name;
}

QString ZoomStudentsDetails::getEmail()
{
    return this->email;
}

QString ZoomStudentsDetails::getJoinTime()
{
    return this->joinTime;
}

QString ZoomStudentsDetails::getLeaveTime()
{
    return this->leaveTime;
}


int ZoomStudentsDetails::getDuration()
{
    return this->duration;
}

QString ZoomStudentsDetails::getGuestStatus()
{
    return this->guest;
}

QString ZoomStudentsDetails::getRecDisclaimerResponse()
{
    return this->recDisclaimerResponse;
}


QString ZoomStudentsDetails::getInWatingRoomStatus()
{
    return this->inWaitingRoom;
}
