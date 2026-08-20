new


# .NET CLI Essentials Cheatsheet

Your quick reference for managing .NET applications directly from the terminal.

---

## 1. Project Lifecycle & Execution

| Command | Description |
| :--- | :--- |
| `dotnet new <template> -o <name>` | Creates a new project in a folder named `<name>`. |
| `dotnet build` | Compiles the project into binaries (`.dll`/`.exe`). |
| `dotnet run` | Compiles and immediately executes the application. |
| `dotnet clean` | Cleans the build output directories (`bin/` and `obj/`). |
| `dotnet watch` | Runs the app and automatically reloads when files change (Hot Reload). |

*Example of a fast dev loop:*
```bash
dotnet watch run

```

---

## 2. Common Project Templates (`dotnet new`)

Pass these short names into the `dotnet new` command to instantiate different project types:

* `console` ── Standard Console Application
* `classlib` ── Class Library (reusable code, compiled to `.dll`)
* `webapi` ── ASP.NET Core Web API (REST backends)
* `webapp` ── ASP.NET Core Razor Pages Web App
* `mstest` / `nunit` / `xunit` ── Unit Testing projects

---

## 3. Package Management (NuGet)

Manage external open-source libraries without touching the project file manually.

```bash
# Add a package to the current project
dotnet add package <PackageName>

# Add a specific version of a package
dotnet add package <PackageName> --version 1.2.3

# Remove a package
dotnet remove package <PackageName>

# List all installed packages in the project
dotnet list package

```

---

## 4. Multi-Project Solutions (`.sln`)

When your codebase grows beyond a single project, use a solution file to group them together.

```bash
# 1. Create a blank solution file in the current directory
dotnet new sln -n MyBigSolution

# 2. Add an existing project to the solution
dotnet sln add path/to/YourProject.csproj

# 3. Reference one project inside another (Dependency)
dotnet add path/to/MainProject.csproj reference path/to/ClassLib.csproj

# 4. Remove a project from the solution
dotnet sln remove path/to/YourProject.csproj

```

---

## 5. Diagnostic & Environment Tools

```bash
# Show installed SDKs and Runtimes
dotnet --info

# List all available project templates on your machine
dotnet new list

# Search the internet/NuGet for a template you don't have installed
dotnet new search <keyword>

```
