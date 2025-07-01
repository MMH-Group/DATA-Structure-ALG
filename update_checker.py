import os
import subprocess
import shutil # For removing directory tree if clone fails initially

# --- Configuration ---
# IMPORTANT: Replace this with the actual repository URL you want to track
# The user M-Mikran-Sandhu does not seem to have public repositories.
# Using a placeholder for demonstration.
GIT_REPO_URL = "https://github.com/octocat/Spoon-Knife.git"
# Path to clone the repository into
LOCAL_REPO_DIR = "cloned_repo"
# Script to regenerate HTML
HTML_GENERATOR_SCRIPT = "generate_html.py"

def run_command(command, cwd=None):
    """Runs a shell command and returns its output and error code."""
    print(f"Running command: {' '.join(command)} in {cwd or os.getcwd()}")
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, cwd=cwd)
    stdout, stderr = process.communicate()
    if process.returncode != 0:
        print(f"Error running command: {' '.join(command)}")
        print(f"STDOUT: {stdout}")
        print(f"STDERR: {stderr}")
    return stdout, stderr, process.returncode

def clone_repo():
    """Clones the repository if it doesn't exist."""
    if os.path.exists(LOCAL_REPO_DIR):
        print(f"Repository already exists at {LOCAL_REPO_DIR}.")
        return True

    print(f"Cloning repository {GIT_REPO_URL} into {LOCAL_REPO_DIR}...")
    # Ensure parent directory exists if LOCAL_REPO_DIR includes subdirectories e.g. "some_path/cloned_repo"
    # os.makedirs(os.path.dirname(LOCAL_REPO_DIR), exist_ok=True) # Not needed if LOCAL_REPO_DIR is simple

    stdout, stderr, returncode = run_command(["git", "clone", GIT_REPO_URL, LOCAL_REPO_DIR])
    if returncode == 0:
        print("Repository cloned successfully.")
        return True
    else:
        print(f"Failed to clone repository. Error: {stderr}")
        # Clean up potentially incomplete clone
        if os.path.exists(LOCAL_REPO_DIR):
            print(f"Cleaning up incomplete clone at {LOCAL_REPO_DIR}")
            try:
                shutil.rmtree(LOCAL_REPO_DIR)
            except OSError as e:
                print(f"Error removing directory {LOCAL_REPO_DIR}: {e}")
        return False

def pull_updates():
    """
    Pulls updates for the repository.
    Returns True if updates were fetched or no updates were needed, False on error.
    Returns a second boolean: True if changes were pulled, False otherwise.
    """
    if not os.path.exists(os.path.join(LOCAL_REPO_DIR, ".git")):
        print(f"Not a git repository: {LOCAL_REPO_DIR}. Attempting to clone again.")
        if not clone_repo():
            return False, False # Main operation failed, no changes
        # If clone was successful, it's up to date, so no "new" changes from this pull.
        return True, False

    print(f"Fetching updates for {LOCAL_REPO_DIR}...")

    # Get current HEAD commit hash before fetching/pulling
    stdout_hash_before, _, ret_hash_before = run_command(["git", "rev-parse", "HEAD"], cwd=LOCAL_REPO_DIR)
    if ret_hash_before != 0:
        print("Could not get current HEAD hash before pull.")
        # Proceed with pull, change detection might be less reliable
        current_hash_before = None
    else:
        current_hash_before = stdout_hash_before.strip()

    # Fetch changes
    _, _, ret_fetch = run_command(["git", "fetch"], cwd=LOCAL_REPO_DIR)
    if ret_fetch != 0:
        print("Failed to fetch updates.")
        return False, False

    # Check for changes by comparing local HEAD with remote HEAD
    # 'git status -uno' can also be useful but rev-parse is more direct for commit changes
    stdout_local_hash, _, _ = run_command(["git", "rev-parse", "HEAD"], cwd=LOCAL_REPO_DIR)
    stdout_remote_hash, _, _ = run_command(["git", "rev-parse", "origin/HEAD"], cwd=LOCAL_REPO_DIR) # Assumes default remote 'origin' and its default branch

    if stdout_local_hash.strip() == stdout_remote_hash.strip():
        print("Repository is already up-to-date.")
        return True, False # Operation successful, no changes

    print("Updates found. Pulling changes...")
    stdout_pull, stderr_pull, ret_pull = run_command(["git", "pull"], cwd=LOCAL_REPO_DIR)
    if ret_pull != 0:
        print(f"Failed to pull updates. Error: {stderr_pull}")
        # Handle potential merge conflicts here if necessary, though script assumes clean pulls.
        return False, False

    print("Updates pulled successfully.")

    # Confirm HEAD changed after pull
    stdout_hash_after, _, ret_hash_after = run_command(["git", "rev-parse", "HEAD"], cwd=LOCAL_REPO_DIR)
    if ret_hash_after != 0:
        print("Could not get current HEAD hash after pull.")
        return True, True # Assume changes if pull seemed successful but hash check failed

    new_hash_after = stdout_hash_after.strip()

    if current_hash_before and new_hash_after != current_hash_before:
        print(f"Repository updated. New HEAD: {new_hash_after}")
        return True, True # Operation successful, changes detected
    elif not current_hash_before: # If we couldn't get hash before, but pull succeeded
        print("Repository updated (unable to compare hashes directly).")
        return True, True # Assume changes
    else:
        # This case (pull succeeded but hash didn't change) should be rare if fetch indicated changes
        print("Pull completed, but no new commits detected (hash unchanged). This might happen with fast-forwards of branches not currently checked out.")
        return True, False


def trigger_html_regeneration():
    """Calls the HTML generator script."""
    print(f"Triggering HTML regeneration using {HTML_GENERATOR_SCRIPT}...")
    # This assumes generate_html.py knows where to find the cloned repo
    # or we pass it as an argument.
    # For now, we need to modify generate_html.py to accept LOCAL_REPO_DIR.

    # Simplest way: modify generate_html.py to use an environment variable or a fixed path
    # that update_checker.py also knows.
    # Or, pass as command line argument.

    # Let's assume generate_html.py is modified to use LOCAL_REPO_DIR
    # We can modify generate_html.py to take LOCAL_REPO_DIR as a parameter.
    # For now, I'll call it and it will use its own configured path.
    # This will require an update to generate_html.py.

    # We need to ensure generate_html.py operates on the files within LOCAL_REPO_DIR.
    # And that its output (generated_index.html) is at the top level.

    # Let's pass the repo path and output path to generate_html.py
    # python generate_html.py <repo_source_path> <output_html_file> <repo_name_override> <repo_desc_override> <repo_url_override>
    # This makes generate_html.py more flexible.

    repo_name_from_url = GIT_REPO_URL.split('/')[-1].replace('.git', '')

    command = [
        "python", HTML_GENERATOR_SCRIPT,
        LOCAL_REPO_DIR, # input path for files
        "generated_index.html", # output html file name
        repo_name_from_url, # repo name
        f"Content of {repo_name_from_url}", # repo description
        GIT_REPO_URL # repo url
    ]

    stdout, stderr, returncode = run_command(command, cwd=os.getcwd()) # Run from script's dir

    if returncode == 0:
        print("HTML regeneration script completed successfully.")
    else:
        print(f"HTML regeneration script failed. Error: {stderr}")

def main():
    print("--- Starting Repository Update Check ---")
    if not clone_repo(): # Clones if not exists
        print("Exiting due to cloning issues.")
        return

    success, has_changes = pull_updates()
    if not success:
        print("Exiting due to issues pulling updates.")
        return

    if has_changes:
        print("Repository has new changes. Regenerating HTML.")
        trigger_html_regeneration()
    else:
        print("No new changes in repository. HTML regeneration not required.")

    print("--- Repository Update Check Finished ---")

if __name__ == "__main__":
    # For now, just run once. Scheduling will be added later.
    main()
