#!/usr/bin/env python3
import getch

def get_password(prompt="Enter password:"):
    print(prompt, end=" ", flush=True)
    password = ""
    s = getch.getch()
    while s not in {"\r", "\n"}:
        password += s
        s = getch.getch()
    return password.rstrip()
print("getch example")
print("\n", getch.getch(), sep='')
print('\ngetche example')
print("\n", getch.getche(), sep='')
s = get_password()
print()
print(s)
