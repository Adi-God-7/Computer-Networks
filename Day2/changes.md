# Changes

- Kept the original headers and socket structure.
- Uses `scanf("%s", ...)` so each turn contains one message.
- Added a null terminator after every `read()`.
- Sent only the actual message length with `strlen()` instead of 256 bytes.
- Added checks for disconnects and failed writes.
- Added socket cleanup when the chat ends.

The client and server exchange one message at a time. Messages containing
spaces are not supported; enter one message word per turn.
