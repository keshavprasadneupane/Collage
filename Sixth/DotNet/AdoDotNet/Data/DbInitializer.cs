using Microsoft.Data.Sqlite;

namespace IostFacultyApi.Data
{
	public static class DbInitializer
	{
		private const string ConnectionString = "Data Source=IOST.db";

		public static void Initialize()
		{
			using var conn = new SqliteConnection(ConnectionString);
			conn.Open();

			var tableCmd = conn.CreateCommand();
			tableCmd.CommandText = @"
            CREATE TABLE IF NOT EXISTS FACULTY (
                CourseID TEXT PRIMARY KEY,
                Course_Name TEXT NOT NULL,
                No_of_Semester INTEGER NOT NULL,
                fee REAL NOT NULL
            );";
			tableCmd.ExecuteNonQuery();
		}
	}
}