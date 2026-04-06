# NES ROM Loading Patterns in Emulators
1. Read the Entire ROM File Into Memory
    - Use standard file I/O to read the ROM file as a binary blob.
    - Store the data in a `std::vector<uint8_t>`,`std::unique_ptr<uint8_t[]>`, or a raw buffer.
2. Parse the Header
    - Extract the first 16 bytes (iNES header) to determine PRG/CHR sizes, mapper, mirroring, etc.
    - Validate the header signature ("NES\x1A").
3. Allocate PRG ROM, CHR ROM/RAM, and PRG RAM
    - Based on header info, allocate memory for PRG ROM, CHR ROM (or RAM if CHR size is 0), and PRG RAM (for battery-backed saves).
4. Copy Data Into Emulator Structures
    - Copy PRG and CHR data from the file buffer into emulator memory.
    - Keep ROM data as read-only (often as const or in a container that isn’t modified).
    - RAM is a separate, writable buffer.
5. Free the File Buffer
    - If a temporary buffer was used, free it after copying data into emulator structures.
 
## Examples from Real Emulators
- FCEUX (C/C++):
Reads the file into a buffer, parses the header, then copies PRG/CHR data into internal arrays. Uses uint8 types for all memory.
- Nestopia (C++):
Uses std::vector<uint8_t> for ROM data, parses header, and manages PRG/CHR/RAM as separate vectors.
- Mesen (C#):
Uses byte[] arrays, parses the header, and separates PRG/CHR/RAM into different fields.
 
## Best Practices
- Use `std::vector<uint8_t>` or similar for automatic memory management.
- Keep ROM and RAM separate.
- Make ROM data read-only after loading.
- Validate the header before using the data.
 
| Step                | Typical Implementation                | 
|---------------------|---------------------------------------| 
| File read           | std::vector<uint8_t> or byte[]    | 
| Header parse        | Extract first 16 bytes                | 
| PRG/CHR/RAM alloc   | Separate containers for each          | 
| ROM data            | Read-only, not modified after load    | 
| RAM data            | Writable, separate from ROM           |
 
## Gotcha:
Never treat ROM as writable memory. Always validate the header to avoid crashes or security issues.
