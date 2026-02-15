from typing import Dict, List
from fastapi import APIRouter, status, HTTPException
from api.router import api
from .model import AttendanceResponse, AttendanceUpdate, AttendenceBulkUpdate, AttendenceUpdateResponse, TeacherAttendanceResponse
from dmodels import Attendance, Class, Class
from database import DB

@api.get("/attendance", status_code=status.HTTP_200_OK, response_model=AttendanceResponse)
def get_attendance(db: DB, student_id: int):
    """
    curl -X GET "http://localhost:8000/api/attendance?student_id=123" -H "accept: application/json"
    """
    try:
        attendances: List[Attendance] = db.query(Attendance).filter(Attendance.student_id == student_id).all()

        data: Dict[str, List[Dict[str, str]]] = {}
        for attendance in attendances:
            if attendance.date not in data:
                data[attendance.date] = []
            data[attendance.date].append({attendance.subject.name: attendance.status})

        return AttendanceResponse(student_id=student_id, data=data)
    except Exception as e:
            raise HTTPException(
                status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                detail=f"An error occurred while fetching attendance: {str(e)}"
            )




@api.get("/attendence/teacher",status_code=status.HTTP_200_OK, response_model=TeacherAttendanceResponse)
def get_attendence_by_teacher(db:DB, class_id: int):
    """
    curl -X GET "http://localhost:8000/api/attendence/teacher?class_id=1" -H "accept: application/json"
    """

    class_info = db.query(Class).filter(Class.id == class_id).first()
    if not class_info:
        raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Class not found")
    
    attendences = db.query(Attendance).join(Attendance.student).filter(Attendance.student.has(class_id=class_id)).all()
    
    # Extract unique subjects and student names for the class
    subjects = {}
    student_names = {}
    dates = []
    data: Dict[tuple[int,int,str], str] = {}

    for attendence in attendences:
        subjects[attendence.subject_id] = attendence.subject.name
        student_names[attendence.student_id] = attendence.student.user.name
        if attendence.date not in dates:
            dates.append(attendence.date)
        data[(attendence.student_id, attendence.subject_id, attendence.date)] = attendence.status

    return TeacherAttendanceResponse(
        class_id=class_id,
        subjects=[{k: v} for k, v in subjects.items()],
        student_ids=[{k: v} for k, v in student_names.items()],
        dates=list(dates),
        data=data
    )





@api.put("/attendance", status_code=status.HTTP_200_OK, response_model=AttendenceUpdateResponse)
def update_attendance(db: DB, student_id: int, subject_id: int, date: str, attendance_update: AttendanceUpdate):
    """
    curl -X PUT "http://localhost:8000/api/attendance?student_id=1&subject_id=1&date=2023-01-01" \
        -H "accept: application/json" \
        -H "Content-Type: application/json" \
        -d '{"status": "P"}'
    """
    try:
        attendance = db.query(Attendance).filter(
            Attendance.student_id == student_id,
            Attendance.date == date.strip('"'),  # remove quotes from date string if present
            Attendance.subject_id == subject_id
        ).first()
        if not attendance:
            raise HTTPException(
                status_code=status.HTTP_404_NOT_FOUND,
                detail="Attendance record not found"
            )

        attendance.status = attendance_update.status
        db.commit()
        return AttendenceUpdateResponse(
            student_id=student_id,
            subject_id=subject_id,
            date=date.strip('"'),
            status=attendance_update.status
        )
    except Exception as e:
        db.rollback()  # rollback in case of any error during the update process
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"An error occurred while updating attendance: {str(e)}"
        )




@api.put("/attendances", status_code=status.HTTP_200_OK , response_model=List[AttendenceUpdateResponse])
def update_attendances(db: DB, attendance_updates: list[AttendenceBulkUpdate]):
    """
    Update multiple attendance records for students.

    Example cURL request:
    curl -X PUT "http://localhost:8000/api/attendances" \
        -H "accept: application/json" \
        -H "Content-Type: application/json" \
        -d '[{
              "student_id": 1,
              "subject_id": 1,
              "date": "2023-01-01",
              "status": "P"
            }]'

    The request body is a JSON array of AttendenceBulkUpdate objects.
    Each object must contain:
        - student_id
        - subject_id
        - date (YYYY-MM-DD)
        - status ("P" for present, "A" for absent)
    """
    try:
        for attendance_update in attendance_updates:
            attendance = db.query(Attendance).filter(
                Attendance.student_id == attendance_update.student_id,
                Attendance.date == attendance_update.date,
                Attendance.subject_id == attendance_update.subject_id
            ).first()
            if not attendance:
                raise HTTPException(
                    status_code=status.HTTP_404_NOT_FOUND,
                    detail="Attendance record not found"
                )

            attendance.status = attendance_update.status
            db.flush()  # flush to update the record in the session before committing
        db.commit()
        return [
            AttendenceUpdateResponse(
                student_id=update.student_id,
                subject_id=update.subject_id,
                date=update.date,
                status=update.status
            ) for update in attendance_updates
        ]
    except Exception as e:
            db.rollback()  # rollback in case of any error during the update process
            raise HTTPException(
                status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
                detail=f"An error occurred while updating attendances: {str(e)}"
            )


