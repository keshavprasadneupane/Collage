namespace BagRegistry.Models
{
	public class Bag
	{
		public int Id { get; set; }
		public string Brand { get; set; } = string.Empty;
		public decimal Price { get; set; }
		public DateTime Date { get; set; }
	}
}