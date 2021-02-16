while True:
    height = int(input("Pyramid height: "))
    if height >= 1 and height <= 8:
        break
for i in range(height):
    print(" " * (height - i - 1), end = "")
    print("#" * i, end = "")
    print("  ", end = "")
    print("#" * i)
