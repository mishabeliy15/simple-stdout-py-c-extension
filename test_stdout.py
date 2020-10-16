import sys
from addList import add
from io import StringIO


class MockStdOut:
    def __init__(self):
        self.src_stdout = None
        self.stdout = None

    def __enter__(self) -> StringIO:
        print("Change stdout")
        self.src_stdout, self.stdout = sys.stdout, StringIO()
        sys.stdout = self.stdout
        print("Start mocking")
        return self.stdout
    
    def __exit__(self, *exc_info):
        self.stdout.close()
        sys.stdout = self.src_stdout
        print("Returning stdout")


input_array = [1, 2, 3]
add(input_array)

with MockStdOut() as stdout:
    add(input_array)
    stdout.flush()
    stdout.seek(0)
    mock_strings = stdout.read()

print("StringIO:", mock_strings, sep="\n")
