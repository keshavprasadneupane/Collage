using Microsoft.EntityFrameworkCore;
using BagRegistry.Models;

namespace BagRegistry.Data
{
	public class AppDbContext : DbContext
	{
		public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) { }

		public DbSet<Bag> Bags => Set<Bag>();
	}
}