from fastapi import status, HTTPException
from .model import RegisterRequest, RegisterResponse
from dmodels import Class, Student, Teacher, User,RoleEnum
from database import DB
from auth.router import auth



@auth.post("/register", status_code=status.HTTP_200_OK, response_model=RegisterResponse)
def register(db:DB, register_request: RegisterRequest):
    """
    curl -X POST "http://localhost:8000/auth/register" -H "Content-Type: application/json" -d '{
     "name": "John Doe",
        "email": "Jonh1@test.com",
        "password": "password123",
        "class_id": 1,
        "role": "student"
    }' 
    """
    try:
        user: User = db.query(User).filter(User.email == register_request.email.strip()).first()
        if user:
            raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Email already registered")
        
        # Validate class existence
        class_:Class = db.query(Class).filter(Class.id == register_request.class_id).first()
        if not class_:
            raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Class not found")

        # Validate role
        if register_request.role.strip() not in [role.value for role in RoleEnum]:
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail=f"Invalid role. Must be one of {[role.value for role in RoleEnum]}"
            )

        new_user: User = User(
            name=register_request.name.strip(),
            email=register_request.email.strip(),
            password=register_request.password.strip(),
            role=register_request.role.strip()
        )
        db.add(new_user)
        db.flush()  # Flush to get the new user's ID
        db.refresh(new_user) 

        if new_user.role == RoleEnum.STUDENT.value:
            new_std = Student(
                user_id=new_user.id,
                class_id=register_request.class_id
            )
            db.add(new_std)
            db.flush()  

            respective_id = new_user.student.id
        elif new_user.role == RoleEnum.TEACHER.value:
            new_techer = Teacher(
                user_id=new_user.id,
                class_id=register_request.class_id
            )
            db.add(new_techer)
            db.flush()  # Flush to get the new teacher's ID
            respective_id = new_user.teacher.id
        else: # extra check, should not reach here due to earlier validation
            raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST, detail="Invalid role")

        # when everything is fine, commit the transaction
        db.commit()
        return RegisterResponse(
            id=new_user.id,
            respective_id= respective_id,
            name=new_user.name,
            role=new_user.role
        )
    except Exception as e:
        db.rollback()  # Rollback the transaction on error
        raise HTTPException(
            status_code=status.HTTP_500_INTERNAL_SERVER_ERROR,
            detail=f"An error occurred during registration: {str(e)}"
        )