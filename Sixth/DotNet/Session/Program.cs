var builder = WebApplication.CreateBuilder(args);

// 1. Add Distributed In-Memory Cache & Session Services
builder.Services.AddDistributedMemoryCache();
builder.Services.AddSession(options =>
{
	options.IdleTimeout = TimeSpan.FromMinutes(20); // Session expiration time
	options.Cookie.HttpOnly = true;                 // Protect against XSS
	options.Cookie.IsEssential = true;             // Mark cookie as required
});

var app = builder.Build();

app.UseDefaultFiles();
app.UseStaticFiles();

// 2. Enable Session Middleware
app.UseSession();

app.UseHttpsRedirection();

// --- Session Endpoints ---

// Set or Update Session User Data
app.MapPost("/api/session/login", (UserLogin login, HttpContext context) =>
{
	if (string.IsNullOrWhiteSpace(login.Username))
	{
		return Results.BadRequest(new { message = "Username cannot be empty." });
	}

	// Store data inside Session
	context.Session.SetString("Username", login.Username);
	context.Session.SetString("Role", login.Role ?? "User");
	context.Session.SetString("LoginTime", DateTime.Now.ToString("g"));

	return Results.Ok(new { message = $"Session created for '{login.Username}'." });
});

// Retrieve Current Session Data
app.MapGet("/api/session/user", (HttpContext context) =>
{
	var username = context.Session.GetString("Username");
	var role = context.Session.GetString("Role");
	var loginTime = context.Session.GetString("LoginTime");

	if (string.IsNullOrEmpty(username))
	{
		return Results.Unauthorized();
	}

	return Results.Ok(new
	{
		Username = username,
		Role = role,
		LoginTime = loginTime,
		SessionId = context.Session.Id
	});
});

// Clear/Destroy Session (Logout)
app.MapPost("/api/session/logout", (HttpContext context) =>
{
	context.Session.Clear(); // Clears all session keys
	return Results.Ok(new { message = "Session destroyed successfully." });
});

app.Run();

// DTO
public record UserLogin(string Username, string Role);