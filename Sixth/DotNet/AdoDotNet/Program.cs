using IostFacultyApi.Data;
using IostFacultyApi.Models;
using Microsoft.Data.Sqlite;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

DbInitializer.Initialize();

app.UseDefaultFiles();
app.UseStaticFiles();
app.UseHttpsRedirection();

const string ConnectionString = "Data Source=IOST.db";

// 1. GET ALL RECORDS
app.MapGet("/api/faculty", () =>
{
	var list = new List<Faculty>();
	using var conn = new SqliteConnection(ConnectionString);
	conn.Open();

	using var cmd = conn.CreateCommand();
	cmd.CommandText = "SELECT CourseID, Course_Name, No_of_Semester, fee FROM FACULTY;";

	using var reader = cmd.ExecuteReader();
	while (reader.Read())
	{
		list.Add(new Faculty
		{
			CourseID = reader.GetString(0),
			Course_Name = reader.GetString(1),
			No_of_Semester = reader.GetInt32(2),
			Fee = Convert.ToDecimal(reader.GetDouble(3))
		});
	}

	return Results.Ok(list);
});

// 2. RETRIEVE FEE BY COURSE ID
app.MapGet("/api/faculty/fee/{courseId}", (string courseId) =>
{
	using var conn = new SqliteConnection(ConnectionString);
	conn.Open();

	using var cmd = conn.CreateCommand();
	cmd.CommandText = "SELECT CourseID, Course_Name, fee FROM FACULTY WHERE CourseID = @id;";
	cmd.Parameters.AddWithValue("@id", courseId);

	using var reader = cmd.ExecuteReader();
	if (reader.Read())
	{
		var result = new
		{
			CourseID = reader.GetString(0),
			Course_Name = reader.GetString(1),
			Fee = Convert.ToDecimal(reader.GetDouble(2))
		};
		return Results.Ok(result);
	}

	return Results.NotFound(new { message = $"No course found with ID '{courseId}'." });
});

// 3. INSERT RECORD
app.MapPost("/api/faculty", (Faculty faculty) =>
{
	using var conn = new SqliteConnection(ConnectionString);
	conn.Open();

	using var cmd = conn.CreateCommand();
	cmd.CommandText = @"
        INSERT INTO FACULTY (CourseID, Course_Name, No_of_Semester, fee) 
        VALUES (@id, @name, @semesters, @fee);";

	cmd.Parameters.AddWithValue("@id", faculty.CourseID);
	cmd.Parameters.AddWithValue("@name", faculty.Course_Name);
	cmd.Parameters.AddWithValue("@semesters", faculty.No_of_Semester);
	cmd.Parameters.AddWithValue("@fee", faculty.Fee);

	try
	{
		cmd.ExecuteNonQuery();
		return Results.Created($"/api/faculty/{faculty.CourseID}", faculty);
	}
	catch (SqliteException)
	{
		return Results.BadRequest("CourseID already exists or invalid data.");
	}
});

app.Run();