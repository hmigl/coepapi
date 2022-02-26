# API_CLI
A [CLI](https://en.wikipedia.org/wiki/Command-line_interface)
program to consume, process and filter
[coepapi](https://github.com/42sp/42labs-selection-process-v2-hmigl#readme) logs

## Features
- Minimal
- Fast
- Possibilitate useful request analysis
- Malleable - accepts different flags

## Usage
```bash
./api_cli [OPTION]
```
**api_cli only works with flags.** Each one of then leads to a diffent behavior

---

## Flags
- With `--help`: displays program usage information

- `-a` (or) `--all`: displays all log content

- Using `-d` (or) `--date` prints only the timestamps of the requests

- With `-r[METHOD]`: will delivery all [METHOD] requests made to an URI
	- METHOD can be: GET, POST, PUT, PATCH, DELETE (all uppercase)

- Finally, `--live` option is going to give you live updates (each 3 seconds),
which may be really useful to catch some unexpected behavior
