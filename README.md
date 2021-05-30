# integrity_check_poc
POC of integrity check

## How this shit works
* make a table using VirtualAlloc() and fill them with encrypted original .text section's binaries.
* call check_text_section() to check if there is corrupted binaries

## TODO:
* VirtualAlloc() can fail and creating a separate page is vulnerable.
* You can reduce the size of the table.
