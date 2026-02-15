from fastapi import status, HTTPException
from .model import LoginRequest, LoginResponse
from dmodels import User
from database import DB
from auth.router import auth



@auth.post("/login", status_code=status.HTTP_200_OK, response_model=LoginResponse)
def login(db:DB, login_request: LoginRequest):
    """
   curl  -X POST "http://localhost:8000/auth/login" \
      -H "Content-Type: application/json" -d '{
        "email": "student@test.com",
        "password": "Test1234!"
    }'
    """

    user: User = db.query(User).filter(User.email == login_request.email.strip()).first()
    if not user or user.password.strip() != login_request.password.strip():
        raise HTTPException(status_code=status.HTTP_401_UNAUTHORIZED, detail="Invalid email or password")
    
    return LoginResponse(
        id=user.id,
        respective_id= user.student.id if user.role == "student" else user.teacher.id,
        name=user.name,
        role=user.role
    )