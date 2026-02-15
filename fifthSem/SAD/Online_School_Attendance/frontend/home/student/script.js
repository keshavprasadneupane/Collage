
const id = sessionStorage.getItem("respective_id");
const role = sessionStorage.getItem("user_role");

if (!id || role !== "student")
    window.location.replace("/login/index.html");

function logout() {
    sessionStorage.clear();
    window.location.replace("/login/index.html");
}

fetch(`http://localhost:8000/api/attendance?student_id=${id}`)
    .then(r => r.json())
    .then(data => {
        document.getElementById("loading").style.display = "none";

        const headerRow = document.getElementById("headerRow");
        const tableBody = document.getElementById("tableBody");
        const attendance = data.data;

        const dates = Object.keys(attendance).sort();
        dates.forEach(d => {
            const th = document.createElement("th");
            th.textContent = d;
            headerRow.appendChild(th);
        });

        const subjectSet = new Set();
        for (const date in attendance)
            attendance[date].forEach(s => subjectSet.add(Object.keys(s)[0]));

        let present = 0, absent = 0;

        Array.from(subjectSet).forEach(subject => {
            const tr = document.createElement("tr");
            const tdSub = document.createElement("td");
            tdSub.textContent = subject;
            tr.appendChild(tdSub);

            dates.forEach(date => {
                const td = document.createElement("td");
                const subObj = attendance[date].find(s => Object.keys(s)[0] === subject);
                const status = subObj ? subObj[subject] : "-";
                td.textContent = status;

                if (status === "P") { td.classList.add("present"); present++; }
                if (status === "A") { td.classList.add("absent"); absent++; }

                tr.appendChild(td);
            });

            tableBody.appendChild(tr);
        });

        document.getElementById("summary").textContent =
            `Total Present: ${present} | Total Absent: ${absent} | Percentage Present: ${present ? (present / (present + absent) * 100).toFixed(2) : 0}%` || "No attendance records found.";
    });