from pydantic import BaseModel
from typing import Optional 

class UserResponse(BaseModel):
    id: int
    name: str
    email: str
    role: str

class StudentResponse(BaseModel):
    id: int
    name: str
    email: str
    class_name: Optional[str] = None

class TeacherResponse(BaseModel):
    id: int
    name: str
    email: str
    class_name: Optional[str] = None