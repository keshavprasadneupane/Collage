document.getElementById("loginForm").addEventListener("submit", async function (event) {
    event.preventDefault();

    const email = document.getElementById("email").value.trim();
    const password = document.getElementById("password").value.trim();

    const response = await fetch("http://localhost:8000/auth/login", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ email, password })
    });

    const data = await response.json();

    if (!response.ok) {
        alert(data.detail || "Login failed");
        return;
    }

    sessionStorage.setItem("user_id", data.id);
    sessionStorage.setItem("user_role", data.role);
    sessionStorage.setItem("respective_id", data.respective_id);

    if (data.role === "teacher")
        window.location.replace("/home/teacher/index.html");
    else
        window.location.replace("/home/student/index.html");
});
