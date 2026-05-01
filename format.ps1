<#
.SYNOPSIS
    Normalizes indentation in all C++/CLI source and header files under
    src/ and include/.

.DESCRIPTION
    For each .cpp and .h file found under src/ and include/:
      - Converts leading tabs to 4 spaces (per indent level)
      - Strips trailing whitespace from every line
      - Ensures the file ends with a single newline
      - Writes files only when changes are needed (avoids unnecessary
        git diffs)

    The dependencies/ directory is never touched.

.PARAMETER DryRun
    Print which files would be changed without writing anything.

.EXAMPLE
    .\format.ps1
    .\format.ps1 -DryRun
#>
param(
    [switch]$DryRun
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$root = $PSScriptRoot
$dirs = @(
    Join-Path $root 'src'
    Join-Path $root 'include'
)

$changed = 0
$unchanged = 0

foreach ($dir in $dirs) {
    if (-not (Test-Path $dir)) { continue }

    Get-ChildItem -Path $dir -Recurse -Include '*.cpp', '*.h' | ForEach-Object {
        $file = $_.FullName

        # Read as raw text to preserve line endings during analysis
        $raw = [System.IO.File]::ReadAllText($file)

        # Normalise CRLF -> LF for processing, then restore at the end
        $lines = $raw -replace "`r`n", "`n" -replace "`r", "`n" -split "`n"

        $newLines = $lines | ForEach-Object {
            $line = $_

            # Expand leading tabs: replace each tab with 4 spaces
            # (handles mixed indent correctly by expanding one tab at a time)
            while ($line -match "^( *)`t") {
                $line = $line -replace "^( *)`t", ('$1' + '    ')
            }

            # Strip trailing whitespace
            $line.TrimEnd()
        }

        # Ensure single trailing newline
        $newContent = ($newLines -join "`r`n").TrimEnd() + "`r`n"

        if ($newContent -ne $raw) {
            if ($DryRun) {
                Write-Host "Would format: $($_.Name)"
            } else {
                [System.IO.File]::WriteAllText($file, $newContent, [System.Text.Encoding]::UTF8)
                Write-Host "Formatted:    $($_.Name)"
            }
            $changed++
        } else {
            $unchanged++
        }
    }
}

$action = if ($DryRun) { 'Would change' } else { 'Changed' }
Write-Host ""
Write-Host "$action $changed file(s), $unchanged already clean."
