from pydantic import BaseModel
from typing import Dict, List

class AttendanceUpdate(BaseModel):
    status: str

class AttendenceUpdateResponse(BaseModel):
    student_id: int
    subject_id: int
    date: str
    status: str


class AttendenceBulkUpdate(BaseModel):
    student_id: int
    subject_id: int
    date: str
    status: str


class TeacherAttendanceResponse(BaseModel):
    class_id: int
    subjects:list[dict[int,str]] #  subject_id subject name
    student_ids : list[dict[int,str]] # student_id  student name
    dates: list[str]
    data: Dict[tuple[int,int,str], str] # key is (student_id, subject_id, date) and value is status




class AttendanceResponse(BaseModel):
    """
    Example: <br/>
    { <br/>
        "student_id": 1, <br/>
        "data": {  <br/>
            "2023-01-01": [ <br/>
                {"Mathematics": "present"}, <br/>
                {"Physics": "absent"} <br/>
            ], <br/>
            "2023-01-02": [ <br/>
                {"Mathematics": "present"}, <br/>
                {"Physics": "present"} <br/>
            ] <br/>
        } <br/>
    } <br/>
    """
    student_id: int
    data: Dict[str, List[Dict[str, str]]]