let teacherData = { dates: [], subjects: [], student_ids: [], data: {} };
let currentDateIndex = 0;
const classId = 1; // Change if needed

// --- Fetch attendance data ---
function fetchData() {
    fetch(`http://localhost:8000/api/attendence/teacher?class_id=${classId}`)
        .then(res => {
            if (!res.ok) throw new Error("Failed to fetch attendance");
            return res.json();
        })
        .then(data => {
            teacherData = data;

            // Sort dates properly
            teacherData.dates.sort((a, b) => new Date(a) - new Date(b));

            if (teacherData.dates.length === 0) {
                document.getElementById("currentDate").textContent = "No Data";
                return;
            }

            currentDateIndex = 0;
            renderTable();
        })
        .catch(err => {
            console.error("Error loading data:", err);
            document.getElementById("currentDate").textContent = "Error loading data";
        });
}

// --- Render table for the current date ---
function renderTable() {
    const tableHeaderRow = document.getElementById("tableHeaderRow");
    const tableBody = document.getElementById("tableBody");

    tableHeaderRow.innerHTML = "";
    tableBody.innerHTML = "";

    const date = teacherData.dates[currentDateIndex];
    document.getElementById("currentDate").textContent = date;

    // Header: first column = "Student Name", then subjects
    const thName = document.createElement("th");
    thName.textContent = "Student Name";
    tableHeaderRow.appendChild(thName);

    teacherData.subjects.forEach(([subId, subName]) => {
        const th = document.createElement("th");
        th.textContent = subName;
        tableHeaderRow.appendChild(th);
    });

    // Body: one row per student
    teacherData.student_ids.forEach(([stuId, stuName]) => {
        const tr = document.createElement("tr");

        // Name cell
        const tdName = document.createElement("td");
        tdName.textContent = stuName;
        tr.appendChild(tdName);

        // Attendance per subject
        teacherData.subjects.forEach(([subId, subName]) => {
            const td = document.createElement("td");
            const select = document.createElement("select");

            ["P", "A"].forEach(status => {
                const option = document.createElement("option");
                option.value = status;
                option.textContent = status === "P" ? "Present" : "Absent";

                const key = `(${stuId}, ${subId}, '${date}')`;
                if (teacherData.data[key] === status) option.selected = true;

                select.appendChild(option);
            });

            select.onchange = () => {
                const key = `(${stuId}, ${subId}, '${date}')`;
                teacherData.data[key] = select.value;
            };

            td.appendChild(select);
            tr.appendChild(td);
        });

        tableBody.appendChild(tr);
    });
}

// --- Navigation ---
document.getElementById("prevDay").onclick = () => {
    if (currentDateIndex > 0) {
        currentDateIndex--;
        renderTable();
    }
};
document.getElementById("nextDay").onclick = () => {
    if (currentDateIndex < teacherData.dates.length - 1) {
        currentDateIndex++;
        renderTable();
    }
};

// --- Submit Attendance ---
document.getElementById("submitAttendance").onclick = () => {
    if (teacherData.dates.length === 0) return alert("No data to submit");

    const date = teacherData.dates[currentDateIndex];
    const payload = [];

    teacherData.student_ids.forEach(([stuId]) => {
        teacherData.subjects.forEach(([subId]) => {
            const key = `(${stuId}, ${subId}, '${date}')`;
            payload.push({
                student_id: stuId,
                subject_id: subId,
                date: date,
                status: teacherData.data[key] || "A"
            });
        });
    });

    fetch("http://localhost:8000/api/attendances", {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(payload)
    })
        .then(res => res.ok ? alert("Attendance Updated!") : alert("Update Failed"))
        .catch(err => alert("Server Error"));
};

// --- Initialize ---
fetchData();