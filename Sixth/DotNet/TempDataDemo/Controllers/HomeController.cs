using Microsoft.AspNetCore.Mvc;

namespace TempDataDemo.Controllers;

public class HomeController : Controller
{
	[HttpGet]
	public IActionResult Index()
	{
		return View();
	}

	[HttpPost]
	public IActionResult SubmitName(string name)
	{
		TempData["Message"] = $"Hello, {name}! This came from TempData after a redirect.";
		return RedirectToAction("Result");
	}

	public IActionResult Result()
	{
		return View();
	}
}