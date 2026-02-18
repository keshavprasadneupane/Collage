
const role = sessionStorage.getItem("user_role");
if (role !== "teacher") {
    window.location.replace("/index.html");
}

function logout() {
    sessionStorage.clear();
    window.location.replace("/index.html");
}

let attendanceData;
let selectedSubjectId = null;
const updates = {};

async function loadAttendance() {
    const classId = 1;

    const response = await fetch(
        `http://localhost:8000/api/attendence/teacher?class_id=${classId}`
    );

    attendanceData = await response.json();

    const subjectSelect = document.getElementById('subject-select');
    subjectSelect.innerHTML = '';

    attendanceData.subjects.forEach(s => {
        const id = Object.keys(s)[0];
        const name = Object.values(s)[0];

        const option = document.createElement('option');
        option.value = id;
        option.textContent = name;
        subjectSelect.appendChild(option);
    });

    selectedSubjectId = Object.keys(attendanceData.subjects[0])[0];

    subjectSelect.onchange = (e) => {
        selectedSubjectId = e.target.value;
        renderTable();
    };

    renderTable();
}

function getStatusClass(status) {
    if (status === 'P') return 'present';
    if (status === 'A') return 'absent';
    return 'notset';
}

function renderTable() {

    const dates = attendanceData.dates;

    const studentEntries = Object.entries(
        attendanceData.student_ids.reduce((acc, s) => ({ ...acc, ...s }), {})
    );

    const thead = document.getElementById('table-head');
    thead.innerHTML = '';

    const headerRow = document.createElement('tr');
    headerRow.appendChild(document.createElement('th')).innerText = 'Student';

    dates.forEach(date => {
        const th = document.createElement('th');
        th.innerText = date;
        headerRow.appendChild(th);
    });

    thead.appendChild(headerRow);

    const tbody = document.getElementById('table-body');
    tbody.innerHTML = '';

    studentEntries.forEach(([studentId, studentName]) => {

        const tr = document.createElement('tr');
        tr.appendChild(document.createElement('td')).innerText = studentName;

        dates.forEach(date => {

            const td = document.createElement('td');

            const key = `${studentId},${selectedSubjectId},${date}`;
            const currentStatus =
                updates[key] ||
                attendanceData.data[key] ||
                'N';

            const select = document.createElement('select');
            select.className = 'status-select';
            select.innerHTML = `
                        <option value="P">P</option>
                        <option value="A">A</option>
                        <option value="N">N</option>
                    `;

            select.value = currentStatus;
            td.className = getStatusClass(currentStatus);

            select.addEventListener('change', () => {
                const newStatus = select.value;
                updates[key] = newStatus;
                td.className = getStatusClass(newStatus);
            });

            td.appendChild(select);
            tr.appendChild(td);
        });

        tbody.appendChild(tr);
    });
}

document.getElementById('submit-btn').onclick = async () => {

    const payload = [];

    for (const [key, status] of Object.entries(updates)) {
        const [studentId, subjectId, date] = key.split(',');

        if (subjectId === selectedSubjectId) {
            payload.push({
                student_id: parseInt(studentId),
                subject_id: parseInt(subjectId),
                date: date,
                status: status
            });
        }
    }

    if (payload.length === 0) {
        alert('No changes to submit.');
        return;
    }

    try {
        const response = await fetch(
            'http://localhost:8000/api/attendances',
            {
                method: 'PUT',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(payload)
            }
        );

        if (!response.ok) throw new Error();

        alert('Attendance updated successfully.');

        payload.forEach(p => {
            const key = `${p.student_id},${p.subject_id},${p.date}`;
            attendanceData.data[key] = p.status;
            delete updates[key];
        });

        renderTable();

    } catch {
        alert('Failed to update attendance.');
    }
};

loadAttendance();
