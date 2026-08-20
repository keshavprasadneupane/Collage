namespace IostFacultyApi.Models
{
	public class Faculty
	{
		public string CourseID { get; set; } = string.Empty;
		public string Course_Name { get; set; } = string.Empty;
		public int No_of_Semester { get; set; }
		public decimal Fee { get; set; }
	}
}