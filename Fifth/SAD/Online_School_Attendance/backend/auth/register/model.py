from pydantic import BaseModel
from typing import Optional

class RegisterRequest(BaseModel):
    name: str
    email: str
    password: str
    class_id:int
    role: str  # "student" or "teacher"
    

class RegisterResponse(BaseModel):
    id:int
    respective_id:int
    name: str
    role: str
