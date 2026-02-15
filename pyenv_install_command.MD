Python Environment Setup Guide (Fish Shell)
This guide covers everything from installing pyenv to setting up a virtual environment and installing packages.

1. Configure Pyenv for Fish
First, ensure your Fish shell knows where pyenv is and how to use it. Run these commands once to update your configuration:

Code snippet
# Set the root directory for pyenv
set -Ux PYENV_ROOT $HOME/.pyenv

# Add pyenv to your PATH
fish_add_path $PYENV_ROOT/bin

# Enable shell integration (adds shims to your path)
echo 'pyenv init - fish | source' >> ~/.config/fish/config.fish

# Reload the config to apply changes
source ~/.config/fish/config.fish
2. Install a Python Version
Install the specific version of Python you need for your project.

Code snippet
# List all available versions (optional)
# pyenv install --list

# Install Python 3.12.2
pyenv install 3.12.2

# Verify it is installed
pyenv versions
3. Project-Level Setup
Navigate to your project folder and lock it to the version you just installed.

Code snippet
# Go to your project directory
cd /mnt/Development/Programming/Collage/fifthSem/SAD/Online_School_Attendance/backend

# Set the local version (creates a .python-version file)
pyenv local 3.12.2

# Verify the version changed
python --version
4. Virtual Environment (venv)
Always use a venv inside your project to keep your pyenv installation clean and manage project-specific dependencies.

Code snippet
# Create the virtual environment named 'venv'
python -m venv venv

# Activate the environment (Specific to Fish shell)
source venv/bin/activate.fish

# Confirm you are inside the venv (usually shows '(venv)' in prompt)
which python
5. Install Packages
Once the venv is active, you can install your requirements safely.

Code snippet
# It's good practice to upgrade pip first
pip install --upgrade pip

# Install individual packages
pip install fastapi uvicorn sqlalchemy

# OR install from a file if you have one
pip install -r requirements.txt

# To save your current setup to a file later:
pip freeze > requirements.txt