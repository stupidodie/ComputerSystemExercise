import sys

try:
    while True:
        for line in sys.stdin.read(1):
            if line > "0" and line <= "9":
                for _ in range(int(line)):
                    sys.stdout.buffer.write(b"\x07")
                sys.stdout.buffer.flush()
except KeyboardInterrupt:
    pass
