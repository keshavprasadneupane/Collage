# simple_models.py
from enum import Enum
from sqlalchemy import Integer, String, ForeignKey, UniqueConstraint, sql
from sqlalchemy.orm import relationship, Mapped, mapped_column
from database import Base


# -------------------------
# Classes
# -------------------------
class Class(Base):
    __tablename__ = "classes"
    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    name: Mapped[str] = mapped_column(String, nullable=False)

    # relationships
    students: Mapped[list["Student"]] = relationship("Student", back_populates="student_class")
    teachers: Mapped[list["Teacher"]] = relationship("Teacher", back_populates="teacher_class")

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.name
        }

# -------------------------
# Subjects
# -------------------------
class Subject(Base):
    __tablename__ = "subjects"
    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    name: Mapped[str] = mapped_column(String, nullable=False)

    # relationship for attendance
    attendance: Mapped[list["Attendance"]] = relationship("Attendance", back_populates="subject")

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.name
        }

# -------------------------
# Users (Teacher or Student)
# -------------------------
class RoleEnum(Enum):
    STUDENT = "student"
    TEACHER = "teacher"

class User(Base):
    __tablename__ = "users"
    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    name: Mapped[str] = mapped_column(String, nullable=False)
    email: Mapped[str] = mapped_column(String, unique=True, nullable=False)
    password: Mapped[str] = mapped_column(String, nullable=False)
    role: Mapped[str] = mapped_column(String(10), nullable=False)  # "student" or "teacher"

    # relationships
    student: Mapped["Student"] = relationship("Student", back_populates="user", uselist=False)
    teacher: Mapped["Teacher"] = relationship("Teacher", back_populates="user", uselist=False)

    def to_dict(self)-> dict:
        return {
            "id": self.id,
            "name": self.name,
            "email": self.email,
            "role": self.role
        }

# -------------------------
# Student
# -------------------------
class Student(Base):
    __tablename__ = "students"
    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    user_id: Mapped[int] = mapped_column(Integer, ForeignKey("users.id"))
    class_id: Mapped[int] = mapped_column(Integer, ForeignKey("classes.id"))

    # relationships
    user: Mapped["User"] = relationship("User", back_populates="student")
    student_class: Mapped["Class"] = relationship("Class", back_populates="students")
    attendance: Mapped[list["Attendance"]] = relationship("Attendance", back_populates="student")

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.user.name,
            "email": self.user.email,
            "class_name": self.student_class.name if self.student_class else None
        }

# -------------------------
# Teacher
# -------------------------
class Teacher(Base):
    __tablename__ = "teachers"
    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    user_id: Mapped[int] = mapped_column(Integer, ForeignKey("users.id"))
    class_id: Mapped[int] = mapped_column(Integer, ForeignKey("classes.id"))

    # relationships
    user: Mapped["User"] = relationship("User", back_populates="teacher")
    teacher_class: Mapped["Class"] = relationship("Class", back_populates="teachers")

    def to_dict(self):
        return {
            "id": self.id,
            "name": self.user.name,
            "email": self.user.email,
            "class_name": self.teacher_class.name if self.teacher_class else None
        }

# -------------------------
# Attendance
# -------------------------
class AttendanceEnum(Enum):
    PRESENT = "P"
    ABSENT = "A"
    NOT_SET ="N"

class Attendance(Base):
    __tablename__ = "attendance"
    __table_args__ = (
        UniqueConstraint('student_id', 'subject_id', 'date', name='uq_student_subject_date'),
    )

    id: Mapped[int] = mapped_column(Integer, primary_key=True)
    student_id: Mapped[int] = mapped_column(Integer, ForeignKey("students.id"))
    subject_id: Mapped[int] = mapped_column(Integer, ForeignKey("subjects.id"))
    # YYYY-MM-DD format, stored as string for simplicity of SAD lab report, but ideally should be Date type
    # string so i can easily show to my professor without worrying about date formatting issues in the report, 
    # but in a real app, Date type would be better
    date: Mapped[str] = mapped_column(String(10), nullable=False) 
    status: Mapped[str] = mapped_column(String(1), nullable=False , server_default=sql.expression.text(f"'{AttendanceEnum.NOT_SET.value}'")) 
   

    # relationships
    student: Mapped["Student"] = relationship("Student", back_populates="attendance")
    subject: Mapped["Subject"] = relationship("Subject", back_populates="attendance")

    def to_dict(self):
        return {
            "id": self.id,
            "student_id": self.student_id,
            "subject_id": self.subject_id,
            "status": self.status,
            "date": self.date
        }