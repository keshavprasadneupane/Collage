using BagRegistry.Data;
using BagRegistry.Models;
using Microsoft.EntityFrameworkCore;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddDbContext<AppDbContext>(options =>
	options.UseSqlite("Data Source=bagstore.db"));

var app = builder.Build();

// Ensure DB exists and Seed initial records if empty
using (var scope = app.Services.CreateScope())
{
	var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
	db.Database.EnsureCreated();

	if (!db.Bags.Any())
	{
		db.Bags.AddRange(
			new Bag { Brand = "Gucci", Price = 1500, Date = new DateTime(2022, 5, 10) },
			new Bag { Brand = "Prada", Price = 450, Date = new DateTime(2022, 8, 15) },
			new Bag { Brand = "Vintage Leather", Price = 800, Date = new DateTime(1981, 3, 22) },
			new Bag { Brand = "Samsonite", Price = 300, Date = new DateTime(2020, 1, 1) }
		);
		db.SaveChanges();
	}
}

app.UseDefaultFiles();
app.UseStaticFiles();
app.UseHttpsRedirection();

// 1. Get All Bags
app.MapGet("/api/bags", async (AppDbContext db) =>
	await db.Bags.ToListAsync());

// 2. Add New Bag
app.MapPost("/api/bags", async (Bag bag, AppDbContext db) =>
{
	db.Bags.Add(bag);
	await db.SaveChangesAsync();
	return Results.Created($"/api/bags/{bag.Id}", bag);
});

// 3. Operation A: Update Price by Year
app.MapPut("/api/bags/update-price", async (int year, decimal newPrice, AppDbContext db) =>
{
	var bagsToUpdate = await db.Bags.Where(b => b.Date.Year == year).ToListAsync();
	if (!bagsToUpdate.Any()) return Results.NotFound(new { message = $"No bags found for year {year}." });

	foreach (var bag in bagsToUpdate)
	{
		bag.Price = newPrice;
	}

	await db.SaveChangesAsync();
	return Results.Ok(new { message = $"Updated {bagsToUpdate.Count} record(s) from year {year} to price ${newPrice}." });
});

// 4. Operation B: Delete Bags by Year
app.MapDelete("/api/bags/delete-by-year", async (int year, AppDbContext db) =>
{
	var bagsToDelete = await db.Bags.Where(b => b.Date.Year == year).ToListAsync();
	if (!bagsToDelete.Any()) return Results.NotFound(new { message = $"No bags found for year {year}." });

	db.Bags.RemoveRange(bagsToDelete);
	await db.SaveChangesAsync();
	return Results.Ok(new { message = $"Deleted {bagsToDelete.Count} record(s) from year {year}." });
});

// 5. Operation C: Retrieve Brands above Price Threshold
app.MapGet("/api/bags/brands-above-price", async (decimal minPrice, AppDbContext db) =>
{
	var brands = await db.Bags
		.Where(b => b.Price > minPrice)
		.Select(b => new { b.Brand, b.Price })
		.ToListAsync();

	return Results.Ok(brands);
});

app.Run();