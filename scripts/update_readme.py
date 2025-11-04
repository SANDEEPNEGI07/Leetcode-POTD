import os
import re
import subprocess
from datetime import datetime

ROOT = "."
README = "README.md"
EXTENSIONS = {".py", ".cpp", ".c", ".cc", ".java", ".js", ".ts", ".cs", ".hpp", ".h"}


def slugify(title: str) -> str:
    """Create a leetcode-style slug from a title string.

    Examples:
    - '2125. Number of Laser Beams in a Bank' -> 'number-of-laser-beams-in-a-bank'
    - 'Group_Anagrams' -> 'group-anagrams'
    """
    s = title.lower()
    # remove leading numbering like '2125.'
    s = re.sub(r"^\s*\d+\.\s*", "", s)
    # remove the word 'leetcode' (optional)
    s = re.sub(r"\bleetcode\b", "", s, flags=re.I)
    # replace non-alnum with hyphens
    s = re.sub(r"[^a-z0-9]+", "-", s)
    s = re.sub(r"-+", "-", s).strip("-")
    return s


def extract_title(path: str) -> str:
    """Try to extract a human-friendly title from the file's top comments.

    Fallbacks to filename (without extension) when no title is found.
    """
    try:
        with open(path, "r", encoding="utf-8", errors="ignore") as f:
            for _ in range(6):
                line = f.readline()
                if not line:
                    break
                # look for patterns like '2125. Title...' or '# 2125. Title' or '// Title'
                m = re.search(r"\d+\.\s*(.+)", line)
                if m:
                    return m.group(1).strip()
                # comment lines starting with // or # or /*
                m2 = re.search(r"^[\s#/*]*([A-Za-z0-9][^\n\r]+)$", line)
                if m2:
                    txt = m2.group(1).strip()
                    # avoid returning a short one-letter token
                    if len(txt) > 2:
                        # strip leading digits + dot if present
                        txt = re.sub(r"^\d+\.\s*", "", txt)
                        return txt
    except Exception:
        pass

    return os.path.splitext(os.path.basename(path))[0]


def git_date_for_file(path: str) -> str:
    """Return last commit date for a file in DD-MM-YYYY format.

    Falls back to file modification time if git is not available or file not committed.
    """
    try:
        res = subprocess.run(["git", "log", "-1", "--format=%ad", "--date=short", "--", path],
                             capture_output=True, text=True, check=True)
        date = res.stdout.strip()
        if date:
            # git returns YYYY-MM-DD with --date=short; reformat to DD-MM-YYYY
            try:
                dt = datetime.strptime(date, "%Y-%m-%d")
                return dt.strftime("%d-%m-%Y")
            except Exception:
                return date
    except Exception:
        pass

    ts = os.path.getmtime(path)
    return datetime.utcfromtimestamp(ts).strftime("%d-%m-%Y")


def should_include(path: str) -> bool:
    name = os.path.basename(path)
    # skip hidden and repo directories
    if name.startswith("."):
        return False
    if os.path.isdir(path):
        return False
    if name.upper() == "README.MD":
        return False
    ext = os.path.splitext(name)[1].lower()
    return ext in EXTENSIONS


def get_files_changed_today() -> list:
    """Return list of code files changed today (based on git log --since=date).

    Uses UTC date (YYYY-MM-DD) as the day boundary. Falls back to the last commit when git fails.
    """
    today = datetime.utcnow().strftime("%Y-%m-%d")
    try:
        out = subprocess.check_output(["git", "log", f"--since={today}", "--name-only", "--pretty=format:"], stderr=subprocess.DEVNULL)
        files = [f.strip() for f in out.decode().splitlines() if f.strip()]
    except Exception:
        # fallback: use files changed in last commit
        try:
            out = subprocess.check_output(["git", "diff", "--name-only", "HEAD~1", "HEAD"], stderr=subprocess.DEVNULL)
            files = [f.strip() for f in out.decode().splitlines() if f.strip()]
        except Exception:
            files = []

    # filter and dedupe
    seen = set()
    results = []
    for f in files:
        if should_include(f) and f not in seen:
            seen.add(f)
            results.append(f)
    return results


def append_today_entries(entries: list):
    """Insert entries immediately after the README table header separator without changing existing rows.

    Each entry is a dict with keys: date,title,link,path.
    """
    if not os.path.exists(README):
        # create minimal header
        header = "# 🧩 Leetcode Problem of the Day Tracker\n\n"
        header += "| Date (DD-MM-YYYY) | Problem Name | LeetCode Link | Solution |\n"
        header += "|-------------------|--------------|---------------|----------|\n"
        with open(README, "w", encoding="utf-8") as f:
            f.write(header)

    with open(README, "r", encoding="utf-8") as f:
        lines = f.readlines()

    # find the table separator line (the line with |---)
    insert_idx = None
    for i, line in enumerate(lines):
        if line.strip().startswith("|-") and "Date" in (lines[i-1] if i-1 >= 0 else ""):
            insert_idx = i + 1
            break
    # fallback: find first separator-looking line
    if insert_idx is None:
        for i, line in enumerate(lines):
            if line.strip().startswith("|-"):
                insert_idx = i + 1
                break
    if insert_idx is None:
        insert_idx = len(lines)

    existing_text = "\n".join(lines)

    new_rows = []
    for ent in entries:
        title = ent.get("title", "").replace("_", " ")
        link = ent.get("link", "")
        date = ent.get("date") or datetime.utcnow().strftime("%d-%m-%Y")
        path = ent.get("path", "")

        # skip duplicates by title or link
        if (link and link in existing_text) or (title and title in existing_text):
            print(f"ℹ️ Skipping already-listed problem: {title}")
            continue

        row = f"| `{date}` | {title} | [🔗 Link]({link}) | [View]({path}) |\n"
        new_rows.append(row)

    if not new_rows:
        print("ℹ️ No new entries to add for today.")
        return

    # insert at top of table
    for idx, r in enumerate(new_rows):
        lines.insert(insert_idx + idx, r)

    with open(README, "w", encoding="utf-8") as f:
        f.writelines(lines)

    print(f"✅ Added {len(new_rows)} new row(s) for today to README.md")


def main():
    entries = []

    # Instead of regenerating the whole README, only add today's changed files.
    files_today = get_files_changed_today()
    if not files_today:
        print("ℹ️ No files changed today to add to README.")
        return

    entries = []
    today_str = datetime.utcnow().strftime("%d-%m-%Y")
    for item in files_today:
        title = extract_title(item)
        slug = slugify(title)
        link = f"https://leetcode.com/problems/{slug}/" if slug else ""
        relpath = f"./{item}"
        entries.append({"date": today_str, "title": title, "link": link, "path": relpath})

    append_today_entries(entries)


if __name__ == "__main__":
    main()
