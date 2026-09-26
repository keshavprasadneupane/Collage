# populate.py
from random import Random
from sqlalchemy.orm import Session
from database import Base, engine
from dmodels import Class, Subject, User, Student, Teacher, Attendance,AttendanceEnum



# change this seed to get different attendance patterns for the same student
seed = 1
rng = Random( seed)
SUBJECTS = ["Mathematics", "Physics", "Chemistry", "Biology", "Computer Science"]
CLASSES = ["Class 1"] 

def add_classes(db: Session):
    for cc in CLASSES:
        new_class = Class(name=cc)
        db.add(new_class)
        db.flush() 
        print(f"Added class: {new_class.name} with ID: {new_class.id}")
    db.commit()

def add_subjects(db: Session):
    for ss in SUBJECTS:
        new_subject = Subject(name=ss)
        db.add(new_subject)
        db.flush()
        print(f"Added subject: {new_subject.name} with ID: {new_subject.id}")
    db.commit()

def add_users(db: Session):
    # Create sample users
    class_ins = db.query(Class).first()  # Get the first class to assign to teacher and student
    if not class_ins:
        print("No classes found. Please add classes before adding users.")
        return (None,None)

    password = "Test1234!"
    user1 = User(name="teacher", email="teacher@test.com", password=password, role="teacher")
    user2 = User(name="student", email="student@test.com", password=password, role="student")
    db.add(user1)
    db.add(user2)
    db.flush() 

    teacher = Teacher(user_id=user1.id, class_id=class_ins.id)
    student = Student(user_id=user2.id, class_id=class_ins.id)
    db.add(teacher)
    db.add(student)
    db.flush()
    print(f"Added teacher: {user1.name} with ID: {user1.id} assigned to class ID: {teacher.class_id}")
    print(f"Added student: {user2.name} with ID: {user2.id} assigned to class ID: {student.class_id}")
    db.commit()
    return (teacher,student)



def add_attendance(db: Session , student_id):
    # for 1 week of attendance for the student in all subjects, with random attendance status (P or A) with a bias towards P
    DATE = ["2024-06-01","2024-06-02","2024-06-03","2024-06-04","2024-06-05","2024-06-06","2024-06-07"]

    subjects = db.query(Subject).all()
    for subject in subjects:
        for d in DATE:
            attendance_record = Attendance(
                student_id=student_id, 
                subject_id=subject.id, 
                # Randomly assign attendance status with a bias towards PRESENT
                status= rng.choice([AttendanceEnum.PRESENT.value, AttendanceEnum.ABSENT.value, AttendanceEnum.PRESENT.value, AttendanceEnum.PRESENT.value, AttendanceEnum.ABSENT.value]),
                date=d)
            db.add(attendance_record)
            db.flush()
            print(f"Added attendance for student ID: {student_id} in subject ID: {subject.id} with status: {attendance_record.status} on date: {d}")
    db.commit()
    pass


def main():
    # Drop & create tables
    Base.metadata.drop_all(bind=engine)
    Base.metadata.create_all(bind=engine)

    # Use Session directly
    with Session(engine) as db:
        add_classes(db)
        add_subjects(db)
        teacher,student= add_users(db)
        if not student:
            print("No student created, skipping attendance")
            return
        if not teacher:
            print("No teacher created, skipping attendance")
            return
        add_attendance(db, student_id=student.id)
    print("Tables created successfully.")

if __name__ == "__main__":
    main()
