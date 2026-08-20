using EmployeeApi.Data;
using EmployeeApi.Models;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<AppDbContext>(options =>
	options.UseSqlite(builder.Configuration.GetConnectionString("DefaultConnection")));

var app = builder.Build();

using (var scope = app.Services.CreateScope())
{
	var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
	db.Database.EnsureCreated();
}

app.UseDefaultFiles();
app.UseStaticFiles();

app.UseHttpsRedirection();

// --- Endpoints ---

app.MapGet("/api/employees", async (AppDbContext db) =>
	await db.Employees.ToListAsync());

app.MapGet("/api/employees/{id:int}", async (int id, AppDbContext db) =>
	await db.Employees.FindAsync(id) is Employee emp
		? Results.Ok(emp)
		: Results.NotFound());

app.MapPost("/api/employees", async (Employee employee, AppDbContext db) =>
{
	db.Employees.Add(employee);
	await db.SaveChangesAsync();
	return Results.Created($"/api/employees/{employee.Id}", employee);
});

app.MapPut("/api/employees/{id:int}", async (int id, Employee updated, AppDbContext db) =>
{
	var employee = await db.Employees.FindAsync(id);
	if (employee is null) return Results.NotFound();

	employee.FirstName = updated.FirstName;
	employee.LastName = updated.LastName;
	employee.Email = updated.Email;
	employee.Department = updated.Department;

	await db.SaveChangesAsync();
	return Results.NoContent();
});

app.MapDelete("/api/employees/{id:int}", async (int id, AppDbContext db) =>
{
	var employee = await db.Employees.FindAsync(id);
	if (employee is null) return Results.NotFound();

	db.Employees.Remove(employee);
	await db.SaveChangesAsync();
	return Results.NoContent();
});

app.Run();