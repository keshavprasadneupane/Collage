

const role = sessionStorage.getItem("user_role");
if (role !== "teacher") {
    window.location.replace("/login.html");
}

function logout() {
    sessionStorage.clear();
    window.location.replace("/login.html");
}

let attendanceData;
let currentDateIndex = 0;
const updates = {};

async function loadAttendance() {
    const classId = 1;
    const response = await fetch(`http://localhost:8000/api/attendence/teacher?class_id=${classId}`);
    attendanceData = await response.json();
    renderTable();
}

function renderTable() {

    const subjects = attendanceData.subjects.map(s => Object.values(s)[0]);
    const subjectIds = attendanceData.subjects.map(s => Object.keys(s)[0]);
    const studentEntries = Object.entries(
        attendanceData.student_ids.reduce((acc, s) => ({ ...acc, ...s }), {})
    );

    const date = attendanceData.dates[currentDateIndex];
    document.getElementById('current-date').innerText = date;

    const thead = document.getElementById('table-head');
    thead.innerHTML = '';
    const headerRow = document.createElement('tr');
    headerRow.appendChild(document.createElement('th')).innerText = 'Student';
    subjects.forEach(sub => {
        const th = document.createElement('th');
        th.innerText = sub;
        headerRow.appendChild(th);
    });
    thead.appendChild(headerRow);

    const tbody = document.getElementById('table-body');
    tbody.innerHTML = '';

    studentEntries.forEach(([studentId, studentName]) => {

        const tr = document.createElement('tr');
        tr.appendChild(document.createElement('td')).innerText = studentName;

        subjectIds.forEach(subjectId => {

            const td = document.createElement('td');
            const key = `${studentId},${subjectId},${date}`;
            const status = updates[key] || attendanceData.data[key] || '-';

            td.innerText = status;
            td.className = status === 'P' ? 'present' :
                status === 'A' ? 'absent' : '';

            td.addEventListener('click', () => {
                const newStatus = td.innerText === 'P' ? 'A' : 'P';
                td.innerText = newStatus;
                td.className = newStatus === 'P' ? 'present' : 'absent';
                updates[key] = newStatus;
            });

            tr.appendChild(td);
        });

        tbody.appendChild(tr);
    });
}

document.getElementById('prev-day').onclick = () => {
    if (currentDateIndex > 0) {
        currentDateIndex--;
        renderTable();
    }
};

document.getElementById('next-day').onclick = () => {
    if (currentDateIndex < attendanceData.dates.length - 1) {
        currentDateIndex++;
        renderTable();
    }
};

document.getElementById('submit-btn').onclick = async () => {

    const date = attendanceData.dates[currentDateIndex];
    const payload = [];

    for (const [key, status] of Object.entries(updates)) {
        const [studentId, subjectId, updateDate] = key.split(',');
        if (updateDate === date) {
            payload.push({
                student_id: parseInt(studentId),
                subject_id: parseInt(subjectId),
                date: updateDate,
                status: status
            });
        }
    }

    if (payload.length === 0) {
        alert('No changes to submit.');
        return;
    }

    try {
        const response = await fetch('http://localhost:8000/api/attendances', {
            method: 'PUT',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload)
        });

        if (!response.ok) throw new Error();

        alert('Attendance updated successfully.');

        payload.forEach(p => {
            attendanceData.data[`${p.student_id},${p.subject_id},${p.date}`] = p.status;
            delete updates[`${p.student_id},${p.subject_id},${p.date}`];
        });

        renderTable();

    } catch {
        alert('Failed to update attendance.');
    }
};

loadAttendance();
